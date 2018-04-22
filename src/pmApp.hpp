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

class ofApp;
class pmApp: public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    ofxQuadWarp warper;
    
    ofImage recipe, message,recipeText[2];
    bool showRecipeText;//後から出す画像のきっかけ
    ofFbo recipeFbo;
    ofFbo messageFbo;
    ofPoint points[10];
    hough_circle hCircle;
    int recipeX,recipeY;
    int recipeSizeX,recipeSizeY;
    int goalX,goalY;
    float alpha;
    
    shared_ptr<ofApp> of;
    
    int movingPoint;//移動テスト用
};


#endif /* pmApp_hpp */
