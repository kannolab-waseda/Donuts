//
//  hough_circle.hpp
//  Donuts
//
//  Created by kannolab on 2018/03/13.
//

#ifndef hough_circle_h
#define hough_circle_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class hough_circle{
    
public:
    void setup();
    void update();
    void draw();
    void resetHough();
    
    int i;
    float *p;
    double w, h;
    //IplImage *src_img = 0, *gray_img = 0;
    ofVideoGrabber camera;
    ofTexture tex;
    unsigned char *pix;
    CvCapture *cap;
    CvSize cvSize;
    IplImage *src_img =0, *gray_img = 0;
    CvMemStorage *storage;
    CvSeq *circles = 0;
    CvSeq *precircles = 0;
    int cTimer ,dTimer;
    bool cSwitch; //円検出のスイッチ。他のクラスやメインのプログラムで使いたいときはhCircle.cSwitchで呼び出す
    
};

#endif /* hough_circle_hpp */

