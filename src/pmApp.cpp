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
    for(int i=0;i<6;i++){
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
        timer += ofGetLastFrameTime() ;//timerはアニメーションが起動してから経過した秒数
        std::cout << "frameRate"<< ofGetFrameRate() << " timer" << timer << std::endl;

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
    
    for(int i=0;i<=5;i++){
        messageFbo[i].begin();
        message[i].draw(0,0);
        messageFbo[i].end();
    }
    
    ofMatrix4x4 mat = warper.getMatrix();
    ofPushMatrix();
    ofMultMatrix(mat);

    if(animationFrag){//アニメーション
        //吸い込まれ中
        if(timer <= 5){
            recipeFbo.draw(recipePos.x,recipePos.y,recipeSize.x,recipeSize.y);
        }
        
        //以下レシピを順番に表示
        if(5 < timer && timer <= 14){
            showMessage(0);
            if(13 < timer){
                hideMessage(0);
            }
        }
        if(14 < timer && timer <= 23){
            showMessage(1);
            if(22 < timer){
                hideMessage(1);
            
            }
        }
        if(23 < timer && timer <= 32){
            showMessage(2);
            if(31 < timer){
                hideMessage(2);
            }
        }
        if(32 < timer && timer <= 41){
            showMessage(3);
            if(40 < timer){
                hideMessage(3);
            }
        }
        if(41 < timer && timer <= 50){
            showMessage(4);
            if(49 < timer){
                hideMessage(4);
            }
        }
        if(50 < timer && timer <= 60){
            showMessage(5);
            if(59 < timer){
                hideMessage(5);
            }
        }
        /*アプリの状態を最初に戻す処理はofAppに記述してある*/
        
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
    for(int i=0;i<6;i++){
        alpha[i] = 255;
    }
}

void pmApp::showMessage(int messageNum){
    messageFbo[messageNum].draw(0,0);
    ofSetColor(0, 0, 0,alpha[messageNum]);
    ofDrawRectangle(0, 0, message[messageNum].getWidth(), message[messageNum].getHeight());
    
    if(0 < alpha[messageNum]){
        alpha[messageNum]-=15;
    }
}

void pmApp::hideMessage(int messageNum){
    if(alpha[messageNum] < 256){
        alpha[messageNum]+=40;
    }
}
