#ifndef STUDENT_H
#define STUDENT_H
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "opencv.hpp"

#define YMOVE  15
#define MAXSTUDENTNUM   20
#define MAXRECTNUM   10
#define XGAP 5
#define YGAP 5
typedef struct student_Feature
{
    int objID;
    int trustedValue;
    int notmoveCount;
    int seatPosition;  //前后分级 4级；
    bool isCurrentObj;
    bool isStandup;

   //for correspondent Rect from vibe
   // int rectIndex;
    //points for lk
    std::vector<cv::Point2f> points[2];
    //initial points
    std::vector<cv::Point2f> initial;

    //data of tracking result
    int trackedPointNum;
    int rectIndex;
    cv::Rect rect;
 //   cv::Point2f center;

    double moveX;
    double moveY;
}student_Feature_t;

void Student_Feature_Init(student_Feature_t &);
void SetRawPoints(std::vector<cv::Point2f> &, int, int);
void SetPoints(std::vector<cv::Point2f> &, std::vector<cv::Point2f> &,cv::Rect &);
void FindLKObj(std::vector<cv::Point2f> &, std::vector<cv::Point2f> &, int &);
bool isMatched(cv::Rect &,cv::Rect &);

//bool isSameRect(cv::Rect &,cv::Rect &);
//cv::Rect getRect(std::vector<cv::Point2f> &);
//void BubbleSort(std::vector<cv::Rect> &, int );
#endif // STUDENT_H
