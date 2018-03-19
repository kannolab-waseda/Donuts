//
//  pmApp.cpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#include "pmApp.h"

void pmApp::setup(){
    //ofSetWindowPosition(1441, 0);
    ofBackground(255, 255, 255);
    //ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    ofEnableSmoothing();
    
    detected=false;
    display = false;
    drawLine = true;
    recipe.loadImage("Image/recipeNoWord.jpg");
    for(int i=0;i<4;i++){
        sprintf(fileName, "Image/text%d.png",i);
        text[i].loadImage(fileName);
    }
    for(int i=0;i<4;i++){
        posX[i]=380;
        posY[i]=335+88*i;
        textHeight[i]=40;
    }
    textWidth[0]=346;
    textWidth[1]=468;
    textWidth[2]=436;
    textWidth[3]=485;
    
}

void pmApp::update(){
    if(ofGetFrameNum()){
        return;
    }
}

void pmApp::draw(){
    //この中にマッピングされる側のコードを書く
    ofBackground(255);
    recipe.draw(100,100);
    ofEnableAlphaBlending();
    for(int i=0;i<4;i++){
        if(detected){
            if(posX[i]!=goalX){
                posX[i]+=distanceX[i]*0.01;
            }
            if(posY[i]!=goalY){
                posY[i]+=distanceY[i]*0.01;
            }
            if(textWidth[i]>0){
                textWidth[i]-=5;
            }
            if(textHeight[i]>0){
                textHeight[i]-=0.5;
            }
        }
        text[i].draw(posX[i],posY[i],textWidth[i],textHeight[i]);
    }
    ofDisableAlphaBlending();
    //ここまで
    ofSetColor(100);
    ofNoFill();
    
    for (int i=0; i<img.size(); i++) {
        img[i]->grabScreen(lx[i], ly[i], ww[i], hh[i]);
        if(drawLine){
            ofRect(lx[i], ly[i], ww[i], hh[i]);
        }
    }
    
    ofSetColor(255, 255, 255);
    ofFill();
    
    if (display) {
        ofBackground(255, 255, 255);
        
        for (int i=0; i<img.size(); i++) {
            
            fbo[i]->begin();{
                img[i]->draw(0, 0);
            }
            fbo[i]->end();
            
            ofMatrix4x4 mat = warper[i]->getMatrix();
            
            glPushMatrix();
            glMultMatrixf(mat.getPtr());
            {
                fbo[i]->draw(0, 0);
            }
            glPopMatrix();
            
            ofSetColor(100, 100, 100);
            ofSetLineWidth(2);
            warper[i]->draw();
            
            ofSetColor(255);
            
        }
    }
}

//--------------------------------------------------------------
void pmApp::keyPressed(int key){
    if(!detected && key == 'q'){
        detected = true;
        for(int i=0;i<4;i++){
            goalX=1000;
            goalY=500;
            distanceX[i] = goalX-posX[i];
            distanceY[i] = goalY-posY[i];
        }
    }
    if( key == 'a' ){
        if (display) {
            display = false;
        }else{
            display = true;
        }
        
    }
    
    if( key == 's' ){
        for (int i=0; i<img.size(); i++) {
            warper[i]->toggleShow();
        }
        
        if (drawLine) {
            drawLine = false;
        }else{
            drawLine = true;
        }
    }
    
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    
    if(key == 'd'){
        lx.pop_back();
        ly.pop_back();
        ww.pop_back();
        hh.pop_back();
        delete img[img.size()-1];
        img.pop_back();
        delete fbo[fbo.size()-1];
        fbo.pop_back();
        delete warper[warper.size()-1];
        warper.pop_back();
        
        mouseCount -= 3;
    }
    
    if (key == 'e') {
        lx.clear();
        ly.clear();
        ww.clear();
        hh.clear();
        for (int i=0; i<img.size(); i++) {
            delete img[i];
            delete fbo[i];
            delete warper[i];
        }
        img.clear();
        fbo.clear();
        warper.clear();
        
        mouseCount = 0;
    }
    
}


//--------------------------------------------------------------
void pmApp::mousePressed(int x, int y, int button){
    
    if (!display) {
        if (mouseCount % 3 == 0) {
            lx.push_back(mouseX);
            ly.push_back(mouseY);
            ww.push_back(0);
            hh.push_back(0);
        }else if(mouseCount % 3 == 1){
            ww[mouseCount/3] = mouseX - lx[mouseCount/3];
            if (mouseX - lx[mouseCount/3] < 0) {
                lx[mouseCount/3] += ww[mouseCount/3];
                ww[mouseCount/3] *= -1;
            }
        }else{
            hh[mouseCount/3] = mouseY - ly[mouseCount/3];
            if (mouseY - ly[mouseCount/3] < 0) {
                ly[mouseCount/3] += hh[mouseCount/3];
                hh[mouseCount/3] *= -1;
            }
            
            img.push_back(new ofImage);
            img[mouseCount/3]->grabScreen(lx[mouseCount/3], ly[mouseCount/3], ww[mouseCount/3], hh[mouseCount/3]);
            
            
            ofxQuadWarp kariWarper;
            warper.push_back(new ofxQuadWarp);
            
            ofFbo kariFbo;
            fbo.push_back(new ofFbo);
            
            fbo[mouseCount/3]->allocate(ww[mouseCount/3], hh[mouseCount/3]);
            warper[mouseCount/3]->setSourceRect(ofRectangle(0, 0, ww[mouseCount/3], hh[mouseCount/3]));
            warper[mouseCount/3]->setTopLeftCornerPosition(ofPoint(lx[mouseCount/3], ly[mouseCount/3]));
            warper[mouseCount/3]->setTopRightCornerPosition(ofPoint(lx[mouseCount/3] + ww[mouseCount/3], ly[mouseCount/3]));
            warper[mouseCount/3]->setBottomLeftCornerPosition(ofPoint(lx[mouseCount/3], ly[mouseCount/3] + hh[mouseCount/3]));
            warper[mouseCount/3]->setBottomRightCornerPosition(ofPoint(lx[mouseCount/3] + ww[mouseCount/3], ly[mouseCount/3] + hh[mouseCount/3]));
            warper[mouseCount/3]->setup();
            
        }
        mouseCount++;
    }
}

