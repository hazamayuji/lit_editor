#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofBackground(0, 0, 0);
    ofSetCircleResolution(60);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    
    /*----------------------フォントを指定----------------------*/
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

/*-----------------------24文字超えたら改行-----------------------*/
bool ofApp::isCountOver() {
    return sentences.at(currentPos).length() > 24;
    
    /*-----------------------カーソル-----------------------*/
    cursor_y1 += 10;
    cursor_y2 += 10;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    /*-----------------------定規-----------------------*/
    
    ofDrawLine(0, 200, ofGetWidth(), 200);
    for(int i; i < ofGetWidth();  i = i + 10){
        ofDrawLine(i, 190, i, 200);
    }
    
    ofDrawLine(200, 0, 200, ofGetHeight());
    for(int i = 0; i < ofGetHeight();  i = i + 10){
        ofDrawLine(190, i, 200, i);
    }

    /*-----------------------カーソルの描画-----------------------*/
    //ofDrawLine(cursor_x1, cursor_y1, cursor_x2, cursor_y2);
    
     
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
        word_height += y;
        
    }
    
    /*-----------------------キーボード押したときに字を描画-----------------------*/
    
    if(pressed_key <= 0) return;//0以下（a(数字になる)などなにもしていないときは終了）
    string tmp = "";
    tmp += pressed_key;
    font_draw.drawString(tmp, ofGetWidth()/2 - 30, ofGetHeight()/2 + 20);

    /*-----------------------キーボード押したときにランダムでアニメーションを描画-----------------------*/
    
    if(rand == 0){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, i * 10 * ofRandom(8,15) );
            }
        
    }else if(rand == 1){
            for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawTriangle(ofRandom(0,ofGetWidth()), ofRandom(0,768),ofRandom(0,ofGetWidth()), ofRandom(0,768), ofRandom(0,ofGetWidth()), ofRandom(0,768));
            
            }
    }else if(rand == 2){
        for(int i = 0; i < 5; i++){
            ofSetColor(255,255,255);
            ofNoFill();
            ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
            ofDrawRectangle(ofRandom(0,ofGetWidth()), ofRandom(0,768),ofRandom(0,ofGetWidth()), ofRandom(0,768));
            }
    }else if(rand == 3){
        for (int i=0; i<NUM; i++) {
            ofNoFill();
            ofSetColor(red[i], green[i], blue[i],127);
            ofDrawCircle(loc_x[i], loc_y[i], radius_key[i]);
            }
    }
   
   /*------------------いらんけど大事なこと(ofximgui)-------------------*
    *          ofFill();//ofximgui                                  *
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
        /*
        cursor_x1 += 21;
        cursor_x2 += 21;
        */
        
        /*--------------キーボード押したときにランダムでアニメーションを描画--------------*/
        rand = ofRandom(0,4);
    }
    
    pressed_key = key;//キーボードおしたとき

    /*--------------------"enter"を押したとき改行--------------------*/
    if (key == 13 || isCountOver()) {   //enterは13
        sentences.push_back("");
        currentPos++;
        
    /*-----------------------カーソル-----------------------*/
        /*
        cursor_y1 += 30;
        cursor_y2 += 30;
        cursor_x1 = 65;
        cursor_x2 = 65;
         */
        
    }
    
    /*--------------------"delete"おしたとき--------------------*/
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
    
    /*-----------------------Sendボタン-----------------------*/
    if (mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 && mouseY < 540 ){
        clickButton = true;
        
        
        
        
        /*-----------------------Sendボタンを押したら文字を全部削除-----------------------*/
        
        
        
        
        //sentences.erase(sentences.begin(),sentences.begin()+23);//間違い？？？

        
        
        
        
        
        
        
        
        
        
        
        
        /*-----------------------OSC部分-----------------------*/
        ofxOscMessage m;
        m.setAddress("/key/sentences");
        int num = sentences.size();//行数を計測
        m.addIntArg(num);
        for (string sentence :sentences) {
            m.addStringArg(sentence);
        }
        sender.sendMessage(m);
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
