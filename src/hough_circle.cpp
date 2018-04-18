//
//  hough_circle.cpp
//  Donuts
//
//  Created by kannolab on 2018/03/13.
//

#include "hough_circle.h"
//--------------------------------------------------------------
void hough_circle::setup(){
    camera.setDeviceID(0);  //カメラデバイスの設定　内蔵カメラを使用するときは0，USBカメラなどを外部機器使うときは1
    camera.setVerbose(true);
    w = 640;
    h = 480;
    camera.setup(w, h);
    cap = cvCreateCameraCapture(0);//setDeviceIDの引数と同じ
    
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH,w);
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT, h);
    cTimer = 0;
    dTimer = 0;
    cSwitch = false;
    storage = cvCreateMemStorage (0);
}

//--------------------------------------------------------------
void hough_circle::update(){
    camera.update();
    IplImage *src_img = cvQueryFrame(cap);
    IplImage *gray_img = cvCreateImage(cvGetSize(cvQueryFrame(cap)), IPL_DEPTH_8U, 1);
    cvCvtColor(src_img, gray_img,CV_BGR2GRAY);
    cvSmooth(gray_img, gray_img, CV_GAUSSIAN, 11, 11, 0,0);
    circles = cvHoughCircles(gray_img, storage, CV_HOUGH_GRADIENT, 2, 150, 30, 80, 20,25);
    
    int resetTime = 5;
    int dMax = 2;  //dMax秒以上円が検出されないとタイマーリセット
    int sMin = 3;  //sMin秒以上断続的に円が検出され続けるとスイッチをオンにする
    if (cSwitch == false) {
     if(circles->total == 1){
        int now = ofGetElapsedTimef();
        if (now - cTimer > resetTime) {
            cTimer = ofGetElapsedTimef();
        }else if(now-cTimer>=sMin){
            cSwitch = true;
            cTimer = 0;
        }
        
     }else{
        int now = ofGetElapsedTimef();
        if (now-cTimer > dMax) {
            cTimer = 0;
        }
      
     }
    }
    cvReleaseImage(&gray_img);
}

//--------------------------------------------------------------
void hough_circle::draw(){
    
    camera.draw(0, 0); //カメラからのキャプチャ画像の描画
    ofPushStyle();
    ofSetColor(255);
    for(int i = 0; i< circles->total; i++){
        ofSetColor(0, 255, 0);
        p = (float*) cvGetSeqElem(circles, i);
        ofDrawCircle(cvRound(p[0]), cvRound(p[1]), 5);
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawCircle(cvRound(p[0]), cvRound(p[1]), cvRound(p[2]));
    }
   // printf("%d \n",circles->total);

    ofPopStyle();
    ofPushStyle();
    if(cSwitch == true){
        // printf("circle is founded \n");
        ofSetColor(0, 0, 255);
        ofDrawCircle(10,500, 10);
    }
    ofPopStyle();

}

//-------------------------------------------------------------
void hough_circle::resetHough(){
    cSwitch = false;
    dTimer = 0;
    cTimer = 0;
}

