//
//  ToggleButton.h
//  lit_editor
//
//  Created by 狭間祐至 on 2017/04/27.
//
//
#include "ofMain.h"
#ifndef ToggleButton_h
#define ToggleButton_h

class ToggleButton{
    
    float width;
    float height;
    ofVec2f offset;
    ofImage img_on;
    ofImage img_off;
    
    bool is_on;
    
    void setup(string path_on_img, string path_off_img);
    void update();
    void draw();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    bool is_touch_inside;
    bool is_inside(float x,float y);
    
    ofEvent<bool> onClick;
    
    
    ofColor bg_color;
    bool is_locked; //現在のフラグ
    ToggleButton tgl_btn; // 自前のボタンクラス
    void toggleLock(bool &state); // ボタンイベントのコールバック関数

};


#endif /* ToggleButton_h */
