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
    cSwitch = false;
}

//--------------------------------------------------------------
void hough_circle::update(){
    camera.update();
    src_img = cvQueryFrame(cap);
    gray_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 1);
    cvCvtColor(src_img, gray_img,CV_BGR2GRAY);
    cvSmooth(gray_img, gray_img, CV_GAUSSIAN, 11, 11, 0,0);
    storage = cvCreateMemStorage (0);
    circles = cvHoughCircles(gray_img, storage, CV_HOUGH_GRADIENT, 2, 150, 30, 80, 20,25);
    
    int sMax = 5;  //sMax秒以上円が検出されないとタイマーリセット
    int sMin = 3;  //sMin秒以上断続的に円が検出され続けるとスイッチをオンにする
    if (cSwitch == false) {
    if(circles->total == 1){
        int now = ofGetElapsedTimef();
        if (now - cTimer >= sMax) {
            cTimer = ofGetElapsedTimef();
        }else if(now - cTimer < sMax && now-cTimer>=sMin){
            cSwitch = true;
            cTimer = 0;
        }
        
    }else{
        int now = ofGetElapsedTimef();
        if (now-cTimer >=sMax) {
            cTimer = ofGetElapsedTimef();
        }
    }
    }
    
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
    
    if(cSwitch == true){
        printf("circle is founded \n");
    }
   // printf("%d \n",circles->total);

    ofPopStyle();

}

