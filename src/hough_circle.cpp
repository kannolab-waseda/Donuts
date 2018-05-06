//
//  hough_circle.cpp
//  Donuts
//
//  Created by kannolab on 2018/03/13.
//

#include "hough_circle.h"
//--------------------------------------------------------------
void hough_circle::setup(){
    cameraDeviceId = 1;//コンソールのDeviceを見て、idを指定
    cameraWidth = 640;
    cameraHeight = 480;

    camera.setDeviceID(cameraDeviceId); //カメラデバイスの設定
    camera.setVerbose(true);
    camera.listDevices();//コンソールに認識されているカメラDeviceを表示
    camera.setup(cameraWidth, cameraHeight);

    cap = cvCreateCameraCapture(cameraDeviceId);//setDeviceIDの引数と同じ
    
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_WIDTH,cameraWidth);
    cvSetCaptureProperty(cap, CV_CAP_PROP_FRAME_HEIGHT, cameraHeight);
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
//    cvSmooth(gray_img, gray_img, CV_GAUSSIAN, 3, 3, 0,0);
    circles = cvHoughCircles(gray_img, storage, CV_HOUGH_GRADIENT, 2, 150, 50, 62, 12,15);
    
    int resetTime = 2000;//ms
    int dMax = 800;  //dMax[ms]以上円が検出されないとタイマーリセット
    int sMin = 300;  //sMin[ms]以上断続的に円が検出され続けるとスイッチをオンにする
    if (cSwitch == false) {
        int now = ofGetElapsedTimeMillis();
        if(circles->total == 1){
            if (now - cTimer > resetTime) {
                cTimer = ofGetElapsedTimeMillis();
            }else if(now-cTimer>=sMin){
                cSwitch = true;
                cTimer = 0;
            }
         }else{
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
        std::cout << "diameter: " << p[2] << std::endl;
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

