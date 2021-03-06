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
    
    settings.width = 1280;//プロジェクターの縦 (720p)
    settings.height = 720;//横
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    shared_ptr<ofAppBaseWindow> pmWindow = ofCreateWindow(settings);

    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<pmApp> PmApp(new pmApp);
    mainApp->pm = PmApp;
    
    ofRunApp(mainWindow, mainApp);
    ofRunApp(pmWindow, PmApp);
    ofRunMainLoop();
}
