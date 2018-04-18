//
//  pmApp.hpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#ifndef pmApp_hpp
#define pmApp_hpp

#include "ofMain.h"
#include "hough_circle.h"
#include "ofApp.h"
#include "ofxQuadWarp.h"

class ofApp;
class pmApp: public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    ofxQuadWarp warper;
    
    ofImage recipe;
    ofImage text[4];
    ofFbo fbo;
    ofPoint points[10];
    int textWidth[4];
    int textHeight;
    shared_ptr<ofApp> of;
};


#endif /* pmApp_hpp */
