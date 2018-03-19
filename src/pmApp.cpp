//
//  pmApp.cpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#include "pmApp.hpp"

void pmApp::setup(){
}

void pmApp::update(){
    
}

void pmApp::draw(){
    //"of->hCircle.cSwitch"で穴が空いているかをチェック
    if(of->hCircle.cSwitch)
        ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
}
