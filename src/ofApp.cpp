#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    velocityShader.load("shader/velocityShader");
    blurShader.load("shader/blur");

    
    gui.setup();

    ofDisableArbTex();
    ofLoadImage(tex, "tex/06-olalindberg.jpg");
    
    fbo.allocate(WIDTH, HEIGHT);
    fbo.createAndAttachTexture(GL_RGB, 0); //Position
    fbo.createAndAttachTexture(GL_RGBA32F, 1); //velocity
    fbo.createAndAttachRenderbuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
    fbo.checkStatus();
    fbo.begin(); ofClear(0); fbo.end();
    ofEnableArbTex();
    
    
    
    quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    quad.addVertex(ofVec3f(1.0, 1.0, 0.0)); // top-right
    quad.addTexCoord(ofVec2f(1.0f, 0.0f));
    quad.addVertex(ofVec3f(1.0, -1.0, 0.0)); //bottom-right
    quad.addTexCoord(ofVec2f(1.0f, 1.0f));
    quad.addVertex(ofVec3f(-1.0, -1.0, 0.0)); //bottom-left
    quad.addTexCoord(ofVec2f(0.0f, 1.0f));
    quad.addVertex(ofVec3f(-1.0, 1.0, 0.0)); //top-left
    quad.addTexCoord(ofVec2f(0.0f, 0.0f));
}

//--------------------------------------------------------------
void ofApp::update()
{
    GLfloat currentFrame = ofGetElapsedTimef();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    deltaTime_ += (deltaTime * delta);
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    angle = deltaTime_;
    ofMatrix4x4 model;
    model.rotate(angle * 35.0, 0.1, 1.0, -0.3);

    
    
    ofBackground(0);
    ofEnableDepthTest();

    fbo.begin();
        cam.begin();
        ofMatrix4x4 view = ofGetCurrentViewMatrix();
        fbo.activateAllDrawBuffers();
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        velocityShader.begin();
        velocityShader.setUniformTexture("tex", tex, 0);
        velocityShader.setUniformMatrix4f("projection", cam.getProjectionMatrix());
        
        velocityShader.setUniformMatrix4f("view", view);
        velocityShader.setUniformMatrix4f("model", model);
        
        velocityShader.setUniformMatrix4f("previousViewMat", preViewMatrix);
        velocityShader.setUniformMatrix4f("previousModel", preModelMatrix);
        
        box.draw();
        
        velocityShader.end();
        
        cam.end();
    fbo.end();
    
    ofDisableDepthTest();
    
    
    blurShader.begin();
    blurShader.setUniformTexture("albedoTex", fbo.getTexture(0), 0);
    blurShader.setUniformTexture("velTex", fbo.getTexture(1), 1);
    blurShader.setUniform1f("u_velocityScale", velocityScale);
    quad.draw();
    blurShader.end();
    
    this->drawGui();
    
    
    
    preViewMatrix = view;
    preModelMatrix = model;
    if(angle > 360) angle = 0;
}


void ofApp::drawGui()
{
    //fbo.getTexture(0).getTextureData().bFlipTexture = true;
    bool guishow = true;
    gui.begin();
    
    ImGui::Begin("Albedo", &guishow, 0);
    ImGui::ImageButton((ImTextureID)(uintptr_t) fbo.getTexture(0).getTextureData().textureID, ImVec2(512, 284));
    ImGui::End();
    
    ImGui::Begin("Velocity", &guishow, 0);
    ImGui::ImageButton((ImTextureID)(uintptr_t) fbo.getTexture(1).getTextureData().textureID, ImVec2(512, 284));
    ImGui::End();
    
    ImGui::Begin("View", &guishow, 0);
    ImGui::SliderFloat("delta T", &delta, 0.1, 100.0);
    ImGui::SliderFloat("velocityScale", &velocityScale, 0.001, 3.0);
    ImGui::End();
    
    gui.end();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

