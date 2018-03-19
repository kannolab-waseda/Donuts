//
//  soundMidi.hpp
//  midiOutputExample
//
//

#ifndef soundMidi_hpp
#define soundMidi_hpp

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "soundMidi.h"

class soundMidi {
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed (int key);
    void keyReleased (int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    
    ofxMidiOut midiOut;
    int channel;
    
    unsigned int currentPgm;
    int note, velocity;
    int pan, bend, touch, polytouch;
    
    /*自作*/
    int executeCutOffFg;
    int cutOffFreqMax;
    int masterVolume;
    int executeTurnDownVolumeFg;
    int masterVolumeMax;
    
    void executeCutOff();
    void stopCutOff();
    /*自作終わり*/
};

#endif /* soundMidi_hpp */
