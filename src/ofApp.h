#pragma once
#include "ofMain.h"

//editorの部分
#include <vector>

//いっぱいの円に必要
#define NUM 300

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        bool isCountOver();//改行のため
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
    
    /*-----------------------editorの部分-----------------------*/
    std::vector<string> sentences;//動的配列
    int currentPos = 0;//配列の最初は0 currentPos = 現在の位置
    
    int x = 100;
    int y = 10;

    int start_y = 100;
    
    
    /*---------------------key_pressedで使用---------------------*/
    int count_a = 0;
    int count_b = 0;
    int count_c = 0;
    int count_d = 0;
    
    /*-----------------------いっぱいの円-----------------------*/
    float loc_x[NUM];
    float loc_y[NUM];
    float speed_x[NUM];
    float speed_y[NUM];
    float radius_key[NUM];
    float red[NUM];
    float green[NUM];
    float blue[NUM];
    
    /*-----------------------"a"の時必要-----------------------*/
    float radius =30;
    
    
    /*---------------------フォントについて---------------------*/
    ofTrueTypeFont font;
    ofTrueTypeFont font_2;//フォントを使用
    ofTrueTypeFont font_small;
};
