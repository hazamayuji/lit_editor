#pragma once

#include "ofMain.h"
#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        bool isCountOver();

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
    
    std::vector<string> sentences;//動的配列
    
    int currentPos = 0;//配列の最初は0 currentPos = 現在の位置
    int x = 30;
    int y = 10;

    int start_y = 30;
    int count = 0;
    
    ofTrueTypeFont font;
		
};
