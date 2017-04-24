#include "ofApp.h"
float radius =30;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    //verdana.load("verdana.ttf",30);
    font.load("arial.ttf", 72);
    sentences.push_back("");
    ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------

bool ofApp::isCountOver() {
    return sentences.at(currentPos).length() > 115;
}

//--------------------------------------------------------------

void ofApp::draw(){
     ofSetColor(255, 255, 255);
    int height = y;
    
    for (string sentence : sentences) {
        ofDrawBitmapString(sentence, x, start_y + height);
        height += y;
    }
    
    if(count == 1){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            font.drawString("a", ofGetWidth()/2 - 22, ofGetHeight()/2 + 20);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, i * 10 * ofRandom(8,15) );
        }
    
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    sentences.at(currentPos) += key;
    
    if (key == 13 || isCountOver()) {
        sentences.push_back("");
        currentPos++;
    }
    
    if(key == 'a'){
        count ++;
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'a'){
        count --;
    }


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
