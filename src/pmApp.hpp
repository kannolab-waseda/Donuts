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

class ofApp;
class pmApp: public ofBaseApp {
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    
    ofxQuadWarp warper;
    
    ofImage recipe, recipeText[2];
    bool showRecipeText;//後から出す画像のきっかけ
    ofFbo fbo;
    ofPoint points[10];
    bool expand;
    int recipeX,recipeY;
    int recipeSizeX,recipeSizeY;
    int goalX,goalY;
    
    shared_ptr<ofApp> of;
    
    int movingPoint;//移動テスト用
};


#endif /* pmApp_hpp */
