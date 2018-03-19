#include "ofMain.h"
#include "ofApp.h"
#include "pmApp.hpp"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
	//複数ウィンドウ化
    ofGLFWWindowSettings settings;
    
    settings.width = 1024;
    settings.height = 768;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 1024;
    settings.height = 768;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
<<<<<<< HEAD
    shared_ptr<ofAppBaseWindow> pmWindow = ofCreateWindow(settings);
    
=======
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
>>>>>>> cafc96a9d77238b7ac4413cd86410ce2feb06db6
    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<pmApp> PmApp(new pmApp);
    PmApp->of = mainApp;
    
    ofRunApp(pmWindow, PmApp);
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
