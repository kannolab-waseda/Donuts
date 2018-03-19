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

class ofApp;
class pmApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    //ここにプロジェクションマッピング用変数，関数を追加
    shared_ptr<ofApp> of;
    
};


#endif /* pmApp_hpp */
