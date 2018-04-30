//
//  pmApp.cpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#include "pmApp.hpp"

void pmApp::setup(){
    ofSetWindowPosition(1441, 0);
    ofBackground(0, 0, 0);
    ofSetFrameRate( 60 );
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    alpha=255;
    showRecipeText = false;
    timer = 0;
    
    recipe.load("Image/recipe.jpg");//レシピ
    message.load("Image/message.jpg");//メッセージ

    int x = (ofGetWidth() - recipe.getWidth()) * 0.5;       // center on screen.
    int y = (ofGetHeight() - recipe.getHeight()) * 0.5;     // center on screen.
    int w = recipe.getWidth();
    int h = recipe.getHeight();
    
    
    recipeFbo.allocate(w, h);
    messageFbo.allocate(w, h);
    recipePos = ofVec2f(0,0);
    recipeVerocity = ofVec2f(4,4);
    recipeSize = ofVec2f(w,h);
    goalPos = ofVec2f(800,500);
    //goalPos = ofVec2f(cvRound(hCircle.p[0]),cvRound(hCircle.p[1]));
    
    warper.setSourceRect(ofRectangle(0, 0, w, h));
    warper.setTopLeftCornerPosition(ofPoint(x, y));
    warper.setTopRightCornerPosition(ofPoint(x + w, y));
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h));
    warper.setup();
    warper.load();
}

void pmApp::update(){
    if(hCircle.cSwitch||showRecipeText){
        timer++;
        recipeVerocity+=0.6;
        if(goalPos.x > recipePos.x && goalPos.y > recipePos.y){
            recipePos += recipeVerocity;
        }
        if(recipeSize.x > 0 || recipeSize.y > 0){
            recipeSize /= 1.15;
        }
    }
    if(ofGetFrameNum()){
        return;
    }
}

void pmApp::draw(){
    for(int i = 0;i<50;i++){
        ofSetColor(255, 190, 125, 1+5*i);
        ofDrawEllipse(800, 500, 800-5*i, 500-5*i);
    }
    ofSetColor(255);
    //======================== fboに描画
    
    recipeFbo.begin();
    recipe.draw(0, 0);
    recipeFbo.end();
    
    messageFbo.begin();
    message.draw(0,0);
    messageFbo.end();
    
    ofMatrix4x4 mat = warper.getMatrix();
    ofPushMatrix();
    ofMultMatrix(mat);
    if(hCircle.cSwitch||showRecipeText){
        if(timer > 3*60){
            messageFbo.draw(0,0);
            ofSetColor(255, 255, 255,alpha);
            ofDrawRectangle(0, 0, message.getWidth(), message.getHeight());
            alpha-=5;
        }else{
            recipeFbo.draw(recipePos.x,recipePos.y,recipeSize.x,recipeSize.y);
        }
    }else{
        recipeFbo.draw(0, 0);
    }
    ofPopMatrix();
    
    //======================== use the matrix to transform points.
    
    ofSetLineWidth(2);
    ofSetColor(ofColor::cyan);
    
    for(int i=0; i<9; i++) {
        int j = i + 1;
        
        ofVec3f p1 = mat.preMult(ofVec3f(points[i].x, points[i].y, 0));
        ofVec3f p2 = mat.preMult(ofVec3f(points[j].x, points[j].y, 0));
        
        ofDrawLine(p1.x, p1.y, p2.x, p2.y);
    }

    //======================== draw quad warp ui.
    
    ofSetColor(ofColor::magenta);
    warper.drawQuadOutline();
    
    ofSetColor(ofColor::yellow);
    warper.drawCorners();
    
    ofSetColor(ofColor::magenta);
    warper.drawHighlightedCorner();
    
    ofSetColor(ofColor::red);
    warper.drawSelectedCorner();

}
void pmApp::exit(){
    warper.save();
}

//--------------------------------------------------------------
void pmApp::keyPressed(int key){
    if(key == 's') {
        warper.toggleShow();
        warper.save();
    }
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    if(key == 'l') {
        //後から出す画像のトリガー
        showRecipeText = true;
    }
}
