#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetCircleResolution(60);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    font_draw.load("Anders.ttf", 72);
    font_const_word.load("Anders.ttf", 50);
    type_word.load("Anders.ttf", 20);
    
    sentences.push_back("");
    
    
    /*----------------------いっぱいの円----------------------*/
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
    
    /*-----------------------ofxOsc(送信のやつ)-----------------------*/
    sender.setup(HOST,PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    /*-----------------------いっぱいの円----------------------*/
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

/*-----------------------100文字超えたら改行-----------------------*/
bool ofApp::isCountOver() {
    return sentences.at(currentPos).length() > 100;
    
    /*-----------------------カーソル-----------------------*/
    cursor_y1 += 10;
    cursor_y2 += 10;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    /*-----------------------カーソルの描画-----------------------*/
    ofDrawLine(cursor_x1, cursor_y1, cursor_x2, cursor_y2);
    
    /*-----------------------文字を入れるBox-----------------------*/
    ofNoFill();
    ofDrawRectangle(word_box_x, word_box_y, ofGetWidth() - word_box_x * 2, ofGetHeight() - word_box_y * 5);
    
    /*-----------------------Sendのbox(枠)-----------------------*/
    ofNoFill();
    ofDrawRectangle(send_box_x, send_box_y, ofGetWidth() - send_box_x * 2, 100);
    font_const_word.drawString("Send", ofGetWidth()/2-90 , ofGetHeight()/2 + 135);
    
    /*-----------------------Sendのカバー(しろ)-----------------------*/
    if(onButton){
        ofFill();
        ofSetColor(255, 255, 255, 127);
        ofDrawRectangle(send_box_x, send_box_y, ofGetWidth() - send_box_x * 2, 100);
    }
    
    /*-----------------------Sendのボタン(アクション)-----------------------*/
    if(clickButton){
        ofSetColor(255, 255, 255);
        font_const_word.drawString("thank you", ofGetWidth()/2-220 , ofGetHeight()/2);
    }

    
    /*----------------------文字かくやつ------------------------*/
    int word_height = y;
    
    for (string sentence : sentences) {
        
        ofSetColor(255, 255, 255);
        type_word.drawString(sentence, word_box_x + 10, start_y + word_height);
        //ofDrawBitmapString(sentence, word_box_x + 10, start_y + word_height);//文字描画
        word_height += y;
        
    }
    
    /*-----------------------キーボード押したときに字を描画-----------------------*/
    
    if(pressed_key <= 0) return;//0以下（a(数字になる)などなにもしていないときは終了）
    string tmp = "";
    tmp += pressed_key;
    font_draw.drawString(tmp, ofGetWidth()/2 - 30, ofGetHeight()/2 + 20);

    /*-----------------------キーボード押したときにランダムでアニメーションを描画-----------------------*/
    
    if(rand == 1){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, i * 10 * ofRandom(8,15) );
            }
        
    }else if(rand == 2){
            for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawTriangle(ofRandom(0,ofGetWidth()), ofRandom(0,768),ofRandom(0,ofGetWidth()), ofRandom(0,768), ofRandom(0,ofGetWidth()), ofRandom(0,768));
            
            }
    }else if(rand == 3){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawRectangle(ofRandom(0,ofGetWidth()), ofRandom(0,768),ofRandom(0,ofGetWidth()), ofRandom(0,768));
            }
    }else if(rand == 4){
        for (int i=0; i<NUM; i++) {
            ofNoFill();
            ofSetColor(red[i], green[i], blue[i],127);
            ofDrawCircle(loc_x[i], loc_y[i], radius_key[i]);
            }
    }
    
   
   /*------------------いらんけど大事なこと(ofximgui)-------------------*
    *          ofFill();//ofximgui　　　　　　　　　                   *
    *          gui.begin();                                         *
    *           if(ImGui::Button("Test Window"))                    *
    *           {                                                   *
    *              //動作を入力する　　　　　　　　　　　　　　　　　　　　　　*
    *            }                                                  *
    *          gui.end();                                           *
    *---------------------------------------------------------------*/
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;//文字の番号確認用

    if(key >= 32 && key != 127) {
        sentences.at(currentPos) += key;
        /*-----------------------カーソル-----------------------*/
        cursor_x1 += 8.05;
        cursor_x2 += 8.05;
        
        /*--------------キーボード押したときにランダムでアニメーションを描画--------------*/
        rand = ofRandom(1,4);
    }
    
    pressed_key = key;//キーボードおしたとき
    


    /*--------------------"enter"を押したとき改行--------------------*/
    if (key == 13 || isCountOver()) {   //enterは13
        sentences.push_back("");
        currentPos++;
        
        /*-----------------------カーソル-----------------------*/
        cursor_y1 += 10;
        cursor_y2 += 10;
        cursor_x1 = 100;
        cursor_x2 = 100;
    }
    
     /*--------------------"delete"おしたとき（まだ）--------------------*/
    if (key == 127 && sentences.at(currentPos).size() > 0) {//delete"は8
        sentences.at(currentPos).pop_back();
    }
    
    
    
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    pressed_key = 0;
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    /*-----------------------Sendカバー-----------------------*/
    if(mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 && mouseY < 540 ){
        
        //send_box_x, send_box_y, ofGetWidth() - send_box_x * 2, 100
        onButton = true;
    }else{
        onButton = false;
    }
    
    
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    /*-----------------------Send„ボタン-----------------------*/
    if (mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 && mouseY < 540 ){
        
        
        clickButton = true;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    /*-----------------------Sendボタン-----------------------*/
    if (mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 && mouseY < 540 ){
        clickButton =false;
    }
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
