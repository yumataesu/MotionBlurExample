#pragma once

#include "ofMain.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void lateDrawUpdate(ofMatrix4x4 &mat);
    void drawGui();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    ofBoxPrimitive box;
    ofMatrix4x4 preViewMatrix;
    ofMatrix4x4 preModelMatrix;
    
    
    ofShader velocityShader, blurShader;
    ofEasyCam cam;
    ofMesh quad;
    ofTexture tex;
    
    ofFbo fbo;
    ofxImGui gui;
    
    float time;
    float lastFrame, currentFrame, deltaTime, deltaTime_;
    float delta;
    float angle;
    float velocityScale;
    
    const int WIDTH = ofGetWidth();
    const int HEIGHT = ofGetHeight();
};
