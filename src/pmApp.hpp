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
    //void keyReleased(int key);
    //void mouseMoved(int x, int y );
    //void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    //void mouseReleased(int x, int y, int button);
    //void windowResized(int w, int h);
    //void dragEvent(ofDragInfo dragInfo);
    //void gotMessage(ofMessage msg);
    
    bool display;
    bool drawLine;
    ofImage recipe;
    ofImage text[4];
    char fileName[255];
    float posX[4];
    float posY[4];
    float textWidth[4];
    float textHeight[4];
    float distanceX[4];
    float distanceY[4];
    float goalX;
    float goalY;
    bool detected;
    vector<ofImage *> img;
    vector<ofFbo *> fbo;
    vector<ofxQuadWarp *> warper;
    
    vector<int> lx;
    vector<int> ly;
    vector<int> ww;
    vector<int> hh;
    int mouseCount;
    //ここにプロジェクションマッピング用変数，関数を追加
    shared_ptr<ofApp> of;
    
};


#endif /* pmApp_hpp */
