#include "student.h"


void Student_Feature_Init(student_Feature_t &obj)
{
  /* Model structure alloc. */
 // object_Feature_t *obj = NULL;
 // obj = (object_Feature_t *)calloc(1, sizeof(*obj));

  /* Default parameters values. */
  obj.trustedValue       = -1;
  obj.notmoveCount    = 0;
  obj.isCurrentObj    = false;
  obj.isStandup=false;

  //

  obj.rect=cv::Rect(0,0,0,0);

  obj.points[0].clear();
  obj.points[1].clear();
  obj.initial.clear();
  obj.trackedPointNum=0;
  obj.moveX=0;
  obj.moveY=0;
  return;
}

void SetRawPoints(std::vector<cv::Point2f> &rawpoints, int width, int height, int *start,int *end) {
    int i,j;
    cv::Point2f p;

    rawpoints.clear();
    for (j = 0; j < height; j+=YGAP){
        for (i = 0; i < width; i+=XGAP){
            if(i>=start[j] && i<end[j])
            {
                p.x=(float)i;
                p.y=(float)j;
                rawpoints.push_back(p);
            }
        }
    }
}
void SetPoints(std::vector<cv::Point2f> &points, std::vector<cv::Point2f> &initial, cv::Rect &rect)
{
    int i,j;
    cv::Point2f p;
    int left=rect.x;
    int top=rect.y;
    int xgap=rect.width/10;
    int ygap=rect.height/20;


    points.clear();
    initial.clear();
    for (i = 0; i < 10; i++){
        for (j = 0; j < 20; j++){
            p.x=(float)(left+i*xgap);
            p.y=(float)(top+j*ygap);
            points.push_back(p);
            initial.push_back(p);
        }
    }
}

void FindLKObj(std::vector<cv::Point2f> &point , std::vector<cv::Point2f> &Center,int &objNum)
{
   // int T = 10;

    int xxx=10;
    int yyy=4;
    int xGap=64;
    int yGap=90;
    int xxGap=xGap/2;
    int yyGap=yGap/2;

    int round_1_Num=0;
    int round_2_Num=0;
    int round_3_Num=0;
    int xmiddle[xxx];

    int y_1_Num=0;
    int y_2_Num=0;
    int y_3_Num=0;
    int ymiddle[yyy];

    int Num[xxx];
    int SumY[yyy];
    int SumX[xxx];
    int lastMiddle;
    int thresHold1=5;
    int thresHold2=5;
    std::vector<cv::Point2f> xclassPoints[xxx],yclassPoints[yyy];
    cv::Point2f p;

    int i,j,k;
    memset(Num,0,sizeof(Num));
    memset(SumX,0,sizeof(SumX));
    objNum=0;
    Center.clear();

    int recleft[10],recright[10],rectop[10],recbottom[10];

   // std::cout<<"pointnum="<<point.size()<<std::endl;
    for(i = 0;i < point.size();i++)
    {
        k=(int)point[i].x/xGap;
        //   std::cout<<" x:"<<point[i].x<<" k:"<<k;
        Num[k]++;
        SumX[k]+=point[i].x;
    }
    for(k=0; k<xxx; k++){
        if(Num[k]>0)
        {
            xmiddle[round_1_Num]=SumX[k]/Num[k];
            round_1_Num++;
        }
    }
   // std::cout<<"  round_1_Num:"<<round_3_Num<<std::endl;
    memset(Num,0,sizeof(Num));
    memset(SumX,0,sizeof(SumX));
    for(i = 0;i < point.size();i++)
    {
        for(k=0; k<round_1_Num; k++){
            if(point[i].x>=(xmiddle[k]-xxGap) && point[i].x<(xmiddle[k]+xxGap)){
                Num[k]++;
                SumX[k]+=point[i].x;
               // xclassPoints[k].push_back(point[i]);
            }
        }
    }
    for(k=0; k<round_1_Num; k++){
        if(Num[k]>=thresHold1){
            xmiddle[round_2_Num]=SumX[k]/Num[k];
            //     xclassPoints[round_2_Num]=xclassPoints[k];
            round_2_Num++;
        }
    }

  //  std::cout<<"  round_2_Num:"<<round_2_Num<<std::endl;

    //  近的类合并
     lastMiddle=-30;
     for(k=0; k<round_2_Num; k++){
         if((xmiddle[k]-lastMiddle)<20){
             lastMiddle=xmiddle[k];
             xmiddle[k]=0;
         }
         else{
             lastMiddle=xmiddle[k];
         }
     }
     for(k=0; k<round_2_Num; k++){
         if(xmiddle[k]>0){
             xmiddle[round_3_Num]=xmiddle[k];
             round_3_Num++;
         }
     }
     memset(Num,0,sizeof(Num));
     memset(SumX,0,sizeof(SumX));
     for(i = 0;i < point.size();i++)
     {
         for(k=0; k<round_3_Num; k++){
             if(point[i].x>=(xmiddle[k]-xxGap) && point[i].x<(xmiddle[k]+xxGap)){
                 Num[k]++;
                 SumX[k]+=point[i].x;
                 xclassPoints[k].push_back(point[i]);
              }
         }
     }
     for(k=0; k<round_3_Num; k++){
         xmiddle[k]=SumX[k]/Num[k];
         std::cout<<" xmiddle="<<xmiddle[k];
     }
  //    std::cout<<"  round_3_Num:"<<round_3_Num<<std::endl;
    //end of classify at x dimension

   //start to do y dimension classify

    for(j=0; j<round_3_Num; j++){
        memset(Num,0,sizeof(Num));
        memset(SumY,0,sizeof(SumY));
        y_1_Num=0;
        y_2_Num=0;
        y_3_Num=0;
        for(k=0; k<yyy; k++)
            yclassPoints[k].clear();

        //first round y
        for(i = 0;i < xclassPoints[j].size();i++)
        {
            k=(int)xclassPoints[j][i].y/yGap;
            Num[k]++;
            SumY[k]+=xclassPoints[j][i].y;
        }
        for(k=0; k<yyy; k++){
            if(Num[k]!=0)
            {
                ymiddle[y_1_Num]=SumY[k]/Num[k];
                y_1_Num++;
            }
        }
        //second round y
        memset(Num,0,sizeof(Num));
        memset(SumY,0,sizeof(SumY));
        for(i = 0;i < xclassPoints[j].size();i++)
        {
            for(k=0; k<y_1_Num; k++){
                if(xclassPoints[j][i].y>=(ymiddle[k]-yyGap)
                        && xclassPoints[j][i].y<(ymiddle[k]+yyGap)){
                    Num[k]++;
                    SumY[k]+=xclassPoints[j][i].y;
          //          yclassPoints[k].push_back(xclassPoints[j][i]);
                }
            }
        }
        for(k=0; k<y_1_Num; k++){
            if(Num[k]>=thresHold2){
                ymiddle[y_2_Num]=SumY[k]/Num[k];
                y_2_Num++;
            }
        }
        //  近的类合并
        lastMiddle=-40;
        for(k=0; k<y_2_Num; k++){
            if((ymiddle[k]-lastMiddle)<30){
                lastMiddle=ymiddle[k];
                ymiddle[k]=0;
            }
            else{
                lastMiddle=ymiddle[k];
            }
        }

        //get a obj in this column
        memset(Num,0,sizeof(Num));
        memset(SumY,0,sizeof(SumY));
        memset(SumX,0,sizeof(SumX));
        for(i = 0;i < xclassPoints[j].size();i++)
        {
            for(k=0; k<y_2_Num; k++){
                if(ymiddle[k]>0){
                    if(xclassPoints[j][i].y>=(ymiddle[k]-yyGap)
                            && xclassPoints[j][i].y<(ymiddle[k]+yyGap)){
                        Num[k]++;
                        SumY[k]+=xclassPoints[j][i].y;
                        SumX[k]+=xclassPoints[j][i].x;
                      }
                }
            }
        }
        for(k=0; k<y_2_Num; k++){
            if(Num[k]>0){
                p.x=SumX[k]/Num[k];
                p.y=SumY[k]/Num[k];
                Center.push_back(p);
                objNum++;
            }
        }

    }//end of loop for y dimension classify

    return;
}
bool isMatched(cv::Rect &rect1,cv::Rect &rect2)
{
    cv::Rect rect=rect1 & rect2;
    return (rect.area()> 20);
}


