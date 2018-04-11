#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
        state = 0;
        sMidi.stopCutOff();
        hCircle.resetHough();
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
