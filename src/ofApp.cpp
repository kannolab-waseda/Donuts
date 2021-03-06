#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);//フレームレートは落ちまくるので、これはあまり意味がない
    hCircle.setup();  //カメラの設定
    
    sMidi.setup();
    
    state = 0; 
}

//--------------------------------------------------------------
void ofApp::update(){

    hCircle.update(); //カメラの更新及びハフ変換による円検出
    sMidi.update();
    
    /*ドーナツ出来たらカットオフ実行の部分*/
    if(hCircle.cSwitch && state == 0) {
        state = 1;
        sMidi.executeCutOff();
        pm->animationFrag = true;
        //pm->goalPos = ofVec2f(hCircle.p[0], hCircle.p[1]);
    }
    
    /*自動[60秒後]でアプリの状態を最初に戻す*/
    if(60 < pm->timer) {
        resetAllState();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    sMidi.draw();
    hCircle.draw();//カメラの画像及び検出された円の描画
}

//--------------------------------------------------------------
void ofApp::exit() {
    sMidi.exit();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    sMidi.keyPressed(key);
    //キー「0」で状態をリセット
    if(key == '0') {
        resetAllState();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    sMidi.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    sMidi.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resetAllState(){
    state = 0;
    sMidi.stopCutOff();
    hCircle.resetHough();
    pm->resetPM();
}
