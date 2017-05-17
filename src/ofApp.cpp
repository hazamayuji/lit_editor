#include "ofApp.h"
#include  <iostream>
#include <string>
#include <fstream>

//--------------------------------------------------------------
void ofApp::setup(){
    //背景を黒に
    ofBackground(0, 0, 0);
    //円のまわりを滑らかに
    ofSetCircleResolution(60);
    //透明度を設定可能に
    ofEnableAlphaBlending();
    //フレームレートを60に
    ofSetFrameRate(60);
    
    /*----------------------フォントを指定----------------------*/
    font_draw.load("Anders.ttf", 72);
    font_const_word.load("Anders.ttf", 50);
    type_word.load("Anders.ttf", 20);
    
    //sentenceの最後に空白を追加
    sentences.push_back("\n");
    /*----------------------いっぱいの円----------------------*/
    for (int i=0; i<NUM; i++) {
        //値をランダムで生成（setupなので１回）
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
    //OSC通信の準備
    sender.setup(HOST,PORT);
    
    /*-----------------------音楽を再生&ループ----------------------*/
    soundplayer.load("Eden.mp3");
    soundplayer.setLoop(true);
    soundplayer.setVolume(1.0);
    soundplayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    /*-----------------------音の大きさで半径変わる円----------------------*/
    volume = ofSoundGetSpectrum(1);
    size_circle = volume[0]*90;
    
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
    return sentences.at(currentPos).length() > 23;
    
    /*-----------------------カーソル-----------------------*/
    /*
    cursor_y1 += 10;
    cursor_y2 += 10;
    */
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    /*-----------------------白線の普通のやつ-----------------------*/
    if(pattern_normal){
        /*-----------------------テキストボックスの枠-----------------------*/
        ofSetColor(255, 255, 255);
        ofNoFill();
        ofDrawRectangle(word_box_x, word_box_y, ofGetWidth() - word_box_x * 2, ofGetHeight() - word_box_y * 5);
        
        /*-----------------------Sendのbox(枠)-----------------------*/
        
         ofNoFill();
         ofSetColor(255, 255, 255);
         ofDrawRectangle(send_box_x, send_box_y + 70, ofGetWidth() - send_box_x * 2, 100);
         ofSetColor(255 , 255, 255);
         font_const_word.drawString("Send", ofGetWidth()/2-90 , ofGetHeight()/2 + 205);
    }
    
    
    /*-----------------------ちょっとチカチカするやつ-----------------------*/
    if(pattern_special){
        
        /*-----------------------テキストボックスの周りのやつ-----------------------*/
        ofFill();
        for(int i = 0; i < 30; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(30,word_box_x), ofRandom(word_box_y,ofGetHeight() - word_box_y * 4 ), size_circle);
        }
        
        for(int i = 0; i < 30; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(ofGetWidth()-word_box_x, ofGetWidth()- 20), ofRandom(word_box_y,ofGetHeight() - word_box_y * 4), size_circle);
        }
        
        for(int i = 0; i < 60; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(30, ofGetWidth()-30), ofRandom(60,word_box_y), size_circle);
        }
        
        for(int i = 0; i < 60; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(30, ofGetWidth() -30), ofRandom(ofGetHeight() - word_box_y * 4,ofGetHeight() - word_box_y * 3 - 50), size_circle);
        }

        /*-----------------------Sendのbox(枠)-----------------------*/
        ofFill();
        for(int i = 0; i < 20; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(send_box_x,ofGetWidth() - send_box_x), ofRandom( send_box_y + 70,send_box_y + 50), size_circle);
        }
        
        ofFill();
        for(int i = 0; i < 20; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(send_box_x,ofGetWidth() - send_box_x), ofRandom( send_box_y + 170,send_box_y + 190), size_circle);
        }
        
        ofFill();
        for(int i = 0; i < 10; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(send_box_x - 20,send_box_x), ofRandom( send_box_y + 50,send_box_y + 190), size_circle);
        }
        
        ofFill();
        for(int i = 0; i < 10; i++){
            ofSetColor(red[i], green[i], blue[i]);
            ofDrawCircle(ofRandom(ofGetWidth() - send_box_x, (ofGetWidth() - send_box_x ) + 20), ofRandom( send_box_y + 50,send_box_y + 190), size_circle);
        }
        
        ofSetColor(255 , 255, size_circle* 100);
        font_const_word.drawString("Send", ofGetWidth()/2-90 , ofGetHeight()/2 + 205);
    }
    
    /*-----------------------定規-----------------------*/
    /*
    ofSetColor(255, 255, 255);
     
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
    

    /*-----------------------Sendのカバー(しろ)-----------------------*/
    if(onButton){
        //ここまでofNoFillできたからここで変更
        ofFill();
        //透明度を追加することによってカバーを生成
        ofSetColor(255, 255, 255, 127);
        ofDrawRectangle(send_box_x, send_box_y + 70, ofGetWidth() - send_box_x * 2, 100);
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
        //sentenceという行に文字列を代入
        type_word.drawString(sentence, word_box_x + 10, start_y + word_height);
        //それが新しいのを生成したらyをプラス
        word_height += y;
    }
    
    /*-----------------------キーボード押したときに字を描画-----------------------*/
    
    if(pressed_key <= 0) return;//0以下（a(数字になる)などなにもしていないときは終了）
    //tmpという文字列を生成してそこに空白を代入
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
    
    
   // if(currentPos > 10){
        ofSetColor(255,255,255);
        font_const_word.drawString("Stop", ofGetWidth()/2-120 , ofGetHeight()/2);
    //}
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;//文字の番号確認用
    cout << currentPos << endl;
    
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
        sentences.push_back("\n");
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
    if (key == 127 && sentences.at(currentPos).size() > 0) {
        sentences.at(currentPos).pop_back();
        
        if (sentences.at(currentPos).length() <= 0) {
            currentPos --;
        }
    }
    
    /*--------------------"fn"おしたとき切り替え--------------------*/
    if (key == -1){//fnキー
        num_normal++;
        if(num_normal % 2 == 1){
            pattern_normal = true;
            pattern_special = false;
        }else if(num_normal % 2 == 0){
            pattern_normal = false;
            pattern_special = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    pressed_key = 0;
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    /*-----------------------Sendカバー-----------------------*/
    if(mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 + 70 && mouseY < 540 +70 ){
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
    if (mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 + 70 && mouseY < 540 + 70 ){
        clickButton = true;
        
        /*-----------------------OSC部分-----------------------*/
        //OSCメッセージの準備
        ofxOscMessage m;
        //OSCアドレスの設定
        m.setAddress("/key/sentences");
        //行数を計測
        int num = sentences.size();
        //numの数字を送信
        m.addIntArg(num);
        
        for (string sentence : sentences) {
            //OSC引数として、sentenceを送信
            m.addStringArg(sentence);
        }
        sender.sendMessage(m);
        
        
        /*-----------------------Sendボタンを押したら文字を全部削除-----------------------*/
        sentences.clear();
        sentences.push_back("\n");
        currentPos = 0;
        
        /*-----------------------Sendボタンを押したら文字を.txtのファイルで出力----------------------*/
        /*
        string filename = "test01.txt";
        trunc (sentences);
        ofstream out_file("Desktop/of_v0.9.8_osx_release/apps/myApps/lit_editor/bin/data/test01.txt");
        */
    }
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    /*-----------------------Sendボタン-----------------------*/
    if (mouseX > send_box_x && mouseX < ofGetWidth() - send_box_x && mouseY > 440 +70 && mouseY < 540 + 70 ){
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
