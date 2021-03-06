//
//  soundMidi.cpp
//  midiOutputExample
//

#include "soundMidi.h"

//--------------------------------------------------------------

void soundMidi::setup() {
    
    ofSetVerticalSync(true);
    //ofBackground(255);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    
    // connect
    midiOut.openPort(0); // by number
    
    cutOffFreqMax = 16383;
    masterVolumeMax = 90;
    
    channel = 1;
    currentPgm = 0;
    note = 0;
    velocity = 0;
    pan = 0;
    bend = cutOffFreqMax;
    touch = 0;
    polytouch = 0;
        
    midiOut.sendPitchBend(channel, bend);
    executeCutOffFg = false;
    stopCutOffFg = false;

    masterVolume = masterVolumeMax;
    turnDownVolumeFg = false;
    turnUpVolumeFg = false;
}

//--------------------------------------------------------------
void soundMidi::update() {
    /*カットオフ開始処理*/
    if(executeCutOffFg) {
        bend -= 400;
        if(bend < 0) {
            bend = 0;
            executeCutOffFg = false;
        } else if (cutOffFreqMax < bend) {
            bend = cutOffFreqMax;
            executeCutOffFg = false;
        } else {
            midiOut.sendPitchBend(channel, bend);
        }
    }
    
    if(turnDownVolumeFg) {
        masterVolume--;
        if(masterVolume < 0) {
            masterVolume = 0;
            turnDownVolumeFg = false;
        } else {
            midiOut.sendControlChange(1,21, masterVolume);
        }
    }
    /*カットオフ開始処理ここまで*/

    /*カットオフ戻す処理*/
    if(stopCutOffFg) {
        bend += 1000;
        if(cutOffFreqMax < bend) {
            bend = cutOffFreqMax;
            stopCutOffFg = false;
        } else if (bend < 0){
            bend = 0;
            stopCutOffFg = false;
        } else {
            midiOut.sendPitchBend(channel, bend);    //カットオフ周波数を最大に戻す
        }
    }

    if(turnUpVolumeFg) {
        masterVolume += 3;
        if(masterVolumeMax < masterVolume) {
            masterVolume = 0;
            turnUpVolumeFg = false;
        } else {
            midiOut.sendControlChange(1,21, masterVolume);
        }
    }
    /*カットオフ戻す処理ここまで*/
}

//--------------------------------------------------------------
void soundMidi::draw() {
    
    ofPushStyle();
    ofSetColor(0);
    stringstream text;
    text << "<Midi Info>" << endl
    << "connected to port " << midiOut.getPort() << endl
    << " \"" << midiOut.getName() << "\"" << endl
    << "sending to channel " << channel << endl << endl
    << "bend(Low Pass Cut Off): " << bend << endl
    << "<How To Use>" << endl
    << "Press 'c' to execute Cut Off " << endl
    << "Press 'v' to reset Cut Off " << endl;

    ofDrawBitmapString(text.str(), 660, 20);
    ofPopStyle();
}

//--------------------------------------------------------------
void soundMidi::exit() {
    
    // clean up
    midiOut.closePort();
}

//--------------------------------------------------------------
void soundMidi::keyPressed(int key) {
    
    if(key == 'l') {
        ofxMidiOut::listPorts();
    }
}

//--------------------------------------------------------------
void soundMidi::keyReleased(int key) {
    
    switch(key) {

        case 'c':
            executeCutOff(); //カットオフする
            break;
            
        case 'v':
            stopCutOff(); //カットオフを戻す
            break;

    }
}

//--------------------------------------------------------------
void soundMidi::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void soundMidi::mouseDragged(int x, int y, int button) {
    
    // x pos controls the pan (ctl = 10)
    pan = ofMap(x, 0, ofGetWidth(), 0, 127);
    //    midiOut.sendControlChange(channel, 10, pan);
    
    // y pos controls the pitch bend
    bend = ofMap(y, 0, ofGetHeight(), 0, MIDI_MAX_BEND);
    if(bend < 0) {
        bend = 0;
    } else if (cutOffFreqMax < bend) {
        bend = cutOffFreqMax;
    }
    midiOut.sendPitchBend(channel, bend);//これをローパスのカットオフ周波数の制御に使う
}

//--------------------------------------------------------------
void soundMidi::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void soundMidi::mouseReleased() {
}


/*カットオフを実行*/
void soundMidi::executeCutOff() {
    //注意！この関数ではフラグを立てるだけで、実際の制御自体はupdate内でやっている。
    printf("cutOff");
    //カットオフする
    bend = cutOffFreqMax;
    executeCutOffFg = true;
    stopCutOffFg = false;

    //ボリュームも下げる
    masterVolume = masterVolumeMax;
    turnUpVolumeFg = true;
    turnDownVolumeFg = false;
}

//カットオフ無しに変更
void soundMidi::stopCutOff() {
    executeCutOffFg = false;
    stopCutOffFg = true;
    bend = 0;
    //    midiOut.sendControlChange(1, 84, 1);//カットオフ自体を戻す
    //追記：これは制御しなくてもオンオフになるっぽいからいいんじゃね

    //ボリュームを戻す
    masterVolume = 0;
    turnUpVolumeFg = false;
}
