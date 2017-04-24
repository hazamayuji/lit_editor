#include "ofApp.h"
int x = 30;
int y = 10;



//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    verdana.load("verdana.ttf",30);
    sentences.push_back("");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
     ofSetColor(255, 255, 255);
    int height = y;
     if(count < 120){
         for (string sentence : sentences) {
             ofDrawBitmapString(sentence, x, height);
             height += y;
         }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
        sentences.at(currentPos) += key;
    if (key == 13) {
        sentences.push_back("");
        currentPos++;
    }
        count ++;
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
