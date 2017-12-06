#ifndef OBJFEATURE_H
#define OBJFEATURE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "opencv.hpp"

#define TRUSTTHRES  4
#define MAXOBJNUM   5
#define MOVENUM     6
#define LEASTLKPOINTS  20
#define LEASTMOVE  0.2
#define LEASTTRACKPOINTS 10
#define NOMATCHINDEX 50
#define NOMATCHTIMES 100
#define MAXTRUSTTIMES  20

typedef struct object_Feature
{
    int objID;
    int trustedValue;
    int trustCount;
    int notmoveCount;
    bool isCurrentObj;
    int noMatch;

   //for correspondent Rect from vibe
    int rectIndex;
    int screenIndex;  //overlap with a screenRange, -1 not overlaped
    //points for mediantrack
    std::vector<cv::Point2f> points[2];
    std::vector<cv::Point2f> initial;

    //data of tracking result
    int trackedPointNum;
    int lkMatchedNum;

    cv::Rect rect;
    cv::Rect initialRect;
   // cv::Point2f center;
    cv::Rect lkRect;
    int mvIndex;
    double objMvX[MOVENUM];
    double objMvY[MOVENUM];
    double moveX;    //filted objMvX
    double moveY;    //filted objMvY
}object_Feature_t;

void object_Feature_Init(object_Feature_t &);
bool isMatchedRect(cv::Rect &,cv::Rect &);
bool isMatchedRectLK(cv::Rect &,cv::Rect &);
bool isMatchedNotMove(cv::Rect &,cv::Rect &);
bool isSameRect(cv::Rect &,cv::Rect &);
cv::Rect getRect(std::vector<cv::Point2f> &);
void BubbleSort(std::vector<cv::Rect> &, int );

#endif // OBJFEATURE_H
