#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "hough_circle.h"

#include "ofMain.h"
#include "ofxMidi.h"
#include "soundMidi.h"

//プロジェクションマッピング用ウィンドウ
#include "pmApp.hpp"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    hough_circle hCircle;
    soundMidi sMidi;
    
    int state; //状態 (0:ドーナツ作り中、1:ドーナツ完成)
    
    //プロジェクションマッピングウィンドウとのデータ送受信用
    shared_ptr<pmApp> pm;
    
};
