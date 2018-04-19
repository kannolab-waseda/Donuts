//
//  pmApp.cpp
//  Donuts
//
//  Created by 634.nakajima on 2018/03/19.
//

#include "pmApp.hpp"

void pmApp::setup(){
    ofSetWindowPosition(1441, 0);
    ofBackground(255, 255, 255);
    ofSetFrameRate( 60 );
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    showRecipeText = false;
    movingPoint = 0;
    
    recipe.load("Image/recipe.jpg");//背景
    recipeText[0].load("Image/text0.png");//後から出すテキスト
    recipeText[1].load("Image/text1.png");//後から出すテキスト

    int x = (ofGetWidth() - recipe.getWidth()) * 0.5;       // center on screen.
    int y = (ofGetHeight() - recipe.getHeight()) * 0.5;     // center on screen.
    int w = recipe.getWidth();
    int h = recipe.getHeight();
    
    fbo.allocate(w, h);
    
    warper.setSourceRect(ofRectangle(0, 0, w, h));
    warper.setTopLeftCornerPosition(ofPoint(x, y));
    warper.setTopRightCornerPosition(ofPoint(x + w, y));
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h));
    warper.setup();
    
}

void pmApp::update(){
    if(showRecipeText){
        movingPoint++;
    }
    if(ofGetFrameNum()){
        return;
    }
}

void pmApp::draw(){
    ofSetColor(255);
    
    //======================== fboに描画
    
    fbo.begin();
    recipe.draw(0, 0);
    if(showRecipeText){
    //    std::cout << movingPoint << std::endl;
        recipeText[0].draw(movingPoint, 0);
        recipeText[1].draw(0, movingPoint);
    }
    fbo.end();
    
    ofMatrix4x4 mat = warper.getMatrix();
    
    ofPushMatrix();
    ofMultMatrix(mat);
    if(!expand){
    fbo.draw(0, 0);
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

//--------------------------------------------------------------
void pmApp::keyPressed(int key){
   
    if(key == 's') {
        warper.toggleShow();
    }
    if(key == 'z'){
        if(!expand){
        expand = true;
        }else{
            expand=false;
        }
    }
    if(key == 'l') {
        //後から出す画像のトリガー
        showRecipeText = true;
    }

}
