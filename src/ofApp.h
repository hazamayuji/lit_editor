#pragma once
#include "ofMain.h"
//#include "ofxImGui.h"

//vector配列
#include <vector>
#include "ofxOsc.h"

//いっぱいの円
#define NUM 300

//ofxOsc(送信のやつ)
#define HOST "127.0.0.1"
#define PORT 8020

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        bool isCountOver();//
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void displayChar(int key);
    
    /*-----------------------editor-----------------------*/
    std::vector<string> sentences;//無限に行いける
    int currentPos = 0;//行のカウント
    
    /*----------------------文字かくやつ------------------------*/
    int y = 30;
    int start_y = 100;
    int word_height = y;
    
    
    /*---------------------入力に必要---------------------*/
//過去の栄光
//    int count_a = 0;
//    int count_b = 0;
//    int count_c = 0;
//    int count_d = 0;
    int pressed_key = 0;
    
    /*-----------------------いっぱいの円-----------------------*/
    float loc_x[NUM];
    float loc_y[NUM];
    float speed_x[NUM];
    float speed_y[NUM];
    float radius_key[NUM];
    float red[NUM];
    float green[NUM];
    float blue[NUM];
    
    /*-----------------------ひろがる円-----------------------*/
    float radius =30;
    
    /*---------------------フォント---------------------*/
    ofTrueTypeFont font_draw;//真ん中にでる文字
    ofTrueTypeFont font_const_word;
    ofTrueTypeFont type_word;
    
    
    /*-----------------------カーソル-----------------------*/
    float cursor_x1 = 100;
    float cursor_x2 = 100;
    float cursor_y1 = 100;
    float cursor_y2 = 112;
    
    /*-----------------------Sendのボタン-----------------------*/
    //ofxImGui::Gui gui;(つかわいないけどいる）
    bool onButton = false;
    bool clickButton = false;
    
    const float send_box_x = 100;
    const float send_box_y = 440;

    /*-----------------------ofxOsc(送信のやつ)-----------------------*/
    ofxOscSender sender;//OSCメッセージの送信者
    
    /*-----------------------文字入れるBox-----------------------*/
    const float word_box_x = 50;
    const float word_box_y = 90;
    
    /*--------------キーボード押したときにランダムでアニメーションを描画--------------*/
    int rand;
    
    
};



