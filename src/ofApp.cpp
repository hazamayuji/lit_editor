#include "ofApp.h"
#include <windows.h>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);//背景は黒
    ofSetCircleResolution(60);//円の周りをきれいに
    ofEnableAlphaBlending();//透明度を使用可能
    ofSetFrameRate(60);//１秒に60枚画面を切り替え
    
    font.load("arial.ttf", 72);//フォントを使用(フォント,サイズ)
    font_2.load("Anders.ttf", 72);
    font_small.load("Anders.ttf", 50);
    
    sentences.push_back(u8"はざま");
    
    
    /*-----------------------いっぱいの円-----------------------*/
    for (int i=0; i<NUM; i++) {
        loc_x[i] = ofRandom(0,ofGetWidth());
        loc_y[i] = ofRandom(0,ofGetHeight());
        speed_x[i] = ofRandom(-10,10);
        speed_y[i] = ofRandom(-10,10);
        radius_key[i] =ofRandom(4,40);
        red[i] = ofRandom(0,255);
        blue[i] = ofRandom(0,255);
        green[i] = ofRandom(0,255);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*-----------------------いっぱいの円-----------------------*/
    for (int i=0; i<NUM; i++) {
        if (loc_x[i] < 0) {
            loc_x[i] = 0;
            speed_x[i] = speed_x[i]*-1;
        }
        if (loc_x[i] > ofGetWidth()) {
            loc_x[i] = ofGetWidth();
            speed_x[i] = speed_x[i]*-1;
        }
        if (loc_y[i] < 0) {
            loc_y[i] = 0;
            speed_y[i] = speed_y[i]*-1;
        }
        if (loc_y[i] > ofGetHeight()) {
            loc_y[i] = ofGetHeight();
            speed_y[i] = speed_y[i]*-1;
        }
        loc_x[i] = loc_x[i] + speed_x[i];
        loc_y[i] = loc_y[i] + speed_y[i];
    }

}

//--------------------------------------------------------------

/*-----------------------115文字以上で改行のため-----------------------*/
bool ofApp::isCountOver() {
    return sentences.at(currentPos).length() > 110;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255, 255);//白色
    
    /*-----------------------文字を書くためのBox-----------------------*/
    ofNoFill();
    ofDrawRectangle(87, 90, 850, 300);
    
    /*-----------------------Sendボタン-----------------------*/
    ofNoFill();
    ofDrawRectangle(341, 440, 341, 100);
    font_small.drawString("Send", ofGetWidth()/2-90 , ofGetHeight()/2 + 135);
    
    /*-----------------------文字が描画される-----------------------*/
    int height = y;
    for (string sentence : sentences) {
        ofDrawBitmapString(sentence, x, start_y + height);//文字を描画
        height += y;
    }
    
    
    /*-----------------------"a"が押された時-----------------------*/
    if(count_a == 1){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            font_2.drawString("a", ofGetWidth()/2 - 22, ofGetHeight()/2 + 20);
            
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, i * 10 * ofRandom(8,15) );
        }
    }
   
    /*-----------------------"b"が押された時-----------------------*/
    if(count_b == 1){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            font_2.drawString("b", ofGetWidth()/2 - 22, ofGetHeight()/2 + 20);
            
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawTriangle(ofRandom(0,1024), ofRandom(0,768),ofRandom(0,1024), ofRandom(0,768), ofRandom(0,1024), ofRandom(0,768));
           
        }
    }
    
    /*-----------------------"c"が押された時-----------------------*/
    if(count_c == 1){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            font_2.drawString("c", ofGetWidth()/2 - 22, ofGetHeight()/2 + 20);
            
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawRectangle(ofRandom(0,1024), ofRandom(0,768),ofRandom(0,1024), ofRandom(0,768));
        }
    }
    
    /*-----------------------"d"が押された時-----------------------*/
    if(count_d == 1){
        ofSetColor(255,255,255);
        font_2.drawString("d", ofGetWidth()/2 - 22, ofGetHeight()/2 + 20);
    
        for (int i=0; i<NUM; i++) {
            ofNoFill();
            ofSetColor(red[i], green[i], blue[i],127);
            ofDrawCircle(loc_x[i], loc_y[i], radius_key[i]);
        }
        
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    sentences.at(currentPos) += key;
    
    /*--------------------"enter"が押された時改行--------------------*/
    if (key == 13 || isCountOver()) {   //enterは13(?)
        sentences.push_back("");
        currentPos++;
    }
    
    /*--------------------"a"が押された時--------------------*/
    if(key == 'a'){
        count_a ++;
    }
    
    /*--------------------"b"が押された時--------------------*/
    if(key == 'b'){
        count_b ++;
    }
    
    /*--------------------"c"が押された時--------------------*/
    if(key == 'c'){
        count_c ++;
    }
    
    /*--------------------"d"が押された時--------------------*/
    if(key == 'd'){
        count_d ++;
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    /*--------------------"a"がはなされた時--------------------*/
    if(key == 'a'){
        count_a --;
    }

    /*--------------------"b"がはなされた時--------------------*/
    if(key == 'b'){
        count_b --;
    }
    
    /*--------------------"c"がはなされた時--------------------*/
    if(key == 'c'){
        count_c --;
    }
    
    /*--------------------"d"がはなされた時--------------------*/
    if(key == 'd'){
        count_d --;
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
