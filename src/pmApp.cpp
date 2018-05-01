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
    animationFrag = false;
    timer = 0;
    
    recipe.load("Image/recipe.jpg");//レシピ

    int x = (ofGetWidth() - recipe.getWidth()) * 0.5;       // center on screen.
    int y = (ofGetHeight() - recipe.getHeight()) * 0.5;     // center on screen.
    int w = recipe.getWidth();
    int h = recipe.getHeight();
    
    
    recipeFbo.allocate(w, h);
    for(int i=0;i<5;i++){
        sprintf(filename, "Image/message%d.jpg",i);
        message[i].load(filename);//メッセージ
        messageFbo[i].allocate(w, h);
        alpha[i]=255;
    }
    recipePos = ofVec2f(0,0);
    recipeVerocity = ofVec2f(15,15);
    recipeSize = ofVec2f(w,h);
    goalPos = ofVec2f(1000,500);
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
    if(animationFrag){
        //アニメーションの動作
        timer++;
        recipeVerocity+=2;
        if(goalPos.x > recipePos.x || goalPos.y > recipePos.y){
            recipePos.x += recipeVerocity.x*0.3;
            recipePos.y += recipeVerocity.y;
        }
        if(recipeSize.x > 0 || recipeSize.y > 0){
            recipeSize /= 1.2;
        }
    }
    if(ofGetFrameNum()){
        return;
    }
}

void pmApp::draw(){
    for(int i = 0;i<50;i++){
        ofSetColor(255, 190, 125, 1+5*i);
        ofDrawEllipse(550, 500, 800-5*i, 500-5*i);
    }
    ofSetColor(255);
    //======================== fboに描画
    
    recipeFbo.begin();
    recipe.draw(0, 0);
    recipeFbo.end();
    
    for(int i=0;i<5;i++){
        messageFbo[i].begin();
        message[i].draw(0,0);
        messageFbo[i].end();
    }
    
    ofMatrix4x4 mat = warper.getMatrix();
    ofPushMatrix();
    ofMultMatrix(mat);
    if(animationFrag){
        //アニメーション
        if(timer > 2*60){ //レシピを順番に表示
            if(timer < 5*60){
                messageFbo[0].draw(0,0);
                ofSetColor(0, 0, 0,alpha[0]);
                ofDrawRectangle(0, 0, message[0].getWidth(), message[0].getHeight());
                alpha[0]-=5;
                if(timer > 3.5*60){
                    alpha[0]+=10;
                }
            }else
            if(timer < 8*60){
                messageFbo[1].draw(0,0);
                ofSetColor(0, 0, 0,alpha[1]);
                ofDrawRectangle(0, 0, message[1].getWidth(), message[1].getHeight());
                alpha[1]-=5;
                if(timer > 6.5*60){
                    alpha[1]+=10;
                }
            }else
            if(timer < 11*60){
                messageFbo[2].draw(0,0);
                ofSetColor(0, 0, 0,alpha[2]);
                ofDrawRectangle(0, 0, message[2].getWidth(), message[2].getHeight());
                alpha[2]-=5;
                if(timer > 9.5*60){
                    alpha[2]+=10;
                }
            }else
            if(timer < 14*60){
                messageFbo[3].draw(0,0);
                ofSetColor(0, 0, 0,alpha[3]);
                ofDrawRectangle(0, 0, message[3].getWidth(), message[3].getHeight());
                alpha[3]-=6;
                if(timer > 12.5*60){
                    alpha[3]+=12;
                }
            }else
            {
                messageFbo[4].draw(0,0);
                ofSetColor(0, 0, 0,alpha[4]);
                ofDrawRectangle(0, 0, message[4].getWidth(), message[4].getHeight());
                alpha[4]-=6;
            }
        }else{
            recipeFbo.draw(recipePos.x,recipePos.y,recipeSize.x,recipeSize.y); //吸い込まれ中
        }
    }else{
        recipeFbo.draw(0, 0);//平常時
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
        animationFrag = true;
    }
}
void pmApp::resetPM(){
    animationFrag = false;
    recipePos = ofVec2f(0,0);
    recipeVerocity = ofVec2f(15,15);
    recipeSize = ofVec2f(recipe.getWidth(),recipe.getHeight());
    timer = 0;
    for(int i=0;i<5;i++){
        alpha[i] = 255;
    }
}
