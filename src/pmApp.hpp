//
//  pmApp.hpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#ifndef pmApp_hpp
#define pmApp_hpp

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "hough_circle.h"
#include "ofxCv.h"

class ofApp;
class pmApp: public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void resetPM();
    void showMessage(int messageNum);
    void hideMessage(int messageNum);
    void exit();
    
    
    ofxQuadWarp warper;
    char filename[255];
    ofImage recipe, message[6];
    bool animationFrag;//後から出す画像のきっかけ
    ofFbo recipeFbo;
    ofFbo messageFbo[6];
    ofPoint points[10];
    ofVec2f recipePos;
    ofVec2f recipeVerocity;
    ofVec2f recipeSize;
    ofVec2f goalPos;
    float alpha[6];
    float timer;
    
    
    //shared_ptr<ofApp> of;
};


#endif /* pmApp_hpp */
