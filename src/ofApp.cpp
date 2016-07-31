#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofBackground(20);
    
    // GL_REPEAT for texture wrap only works with NON-ARB textures //
    ofDisableArbTex();
    texture.load("of.png");
    texture.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    vidGrabber.setup(640, 480, true);
    
    bFill       = true;
    bWireframe  = false;
    bDrawNormals= false;
    bDrawAxes   = false;
    bDrawLights = false;
    bInfoText   = true;
    bMousePressed   = false;
    bSplitFaces = false;
    
    float width     = ofGetWidth() * .12;
    float height    = ofGetHeight() * .12;
    
    
    box.set( width*1.25 );
    
    mode = 2;
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetWindowTitle("ofxSyphon Example");
    
    mainOutputSyphonServer.setName("Screen Output");
    
    mClient.setup();
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
}

//--------------------------------------------------------------
void ofApp::update() {
    //ofSetWindowTitle("Framerate: "+ofToString(ofGetFrameRate(), 0));
    if(mode == 2 || ofGetElapsedTimef() < 10) {
        vidGrabber.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    if(bMousePressed) {
        spinX = spinY = 0.0f;
    }
    
    ofEnableDepthTest();
    
    if(mode == 1 || mode == 3) texture.getTexture().bind();
    if(mode == 2) vidGrabber.getTexture().bind();
    
    // Box //
    box.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);
    box.rotate(spinX, 1.0, 0.0, 0.0);
    box.rotate(spinY, 0, 1.0, 0.0);
    
    if(bFill) {
        material.begin();
        ofFill();
        if(mode == 3) {
            box.transformGL();
            for(int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++ ) {
                ofPushMatrix();
                ofTranslate( boxSides[i].getNormal(0) * sin(ofGetElapsedTimef()) * 50  );
                boxSides[i].draw();
                ofPopMatrix();
            }
            box.restoreTransformGL();
        } else {
            box.draw();
        }
        material.end();
    }
    
    if(bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        box.setScale(1.01f);
        box.drawWireframe();
        box.setScale(1.f);
    }
    
    if(mode == 1 || mode == 3) texture.getTexture().unbind();
    if(mode == 2) vidGrabber.getTexture().unbind();
    
    ofDisableDepthTest();
    
    mainOutputSyphonServer.publishScreen();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    switch(key) {
        case 'f':
            ofToggleFullscreen();
            break;
    }
    
    if(mode == 2) {
        plane.resizeToTexture( vidGrabber.getTexture(), .5 );
        box.mapTexCoordsFromTexture( vidGrabber.getTexture() );
        sphere.mapTexCoordsFromTexture( vidGrabber.getTexture() );
        icoSphere.mapTexCoordsFromTexture( vidGrabber.getTexture() );
        cylinder.mapTexCoordsFromTexture( vidGrabber.getTexture() );
        cone.mapTexCoordsFromTexture( vidGrabber.getTexture() );
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    bMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bMousePressed = false;
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
