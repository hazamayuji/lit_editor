//
//  ToggleButton.cpp
//  lit_editor
//
//  Created by 狭間祐至 on 2017/04/27.
//
//

#include "ToggleButton.h"

/*----------------------ボタン-----------------------*/
void ToggleButton::setup(string path_on_img, string path_off_img){
    img_on.loadImage(path_on_img);
    img_off.loadImage(path_off_img);
    width = 100;
    height = 100;
    offset = ofVec2f(0,0);
    
    is_on = true;
}

void ToggleButton::draw(){
    ofPushMatrix();
    ofTranslate(0,0,1);
    if(is_on){
        img_on.draw(offset, width, height);
    } else {
        img_off.draw(offset, width, height);
    }
    ofPopMatrix();
}


void ToggleButton::touchDown(ofTouchEventArgs & touch){
    if (is_inside(touch.x, touch.y)) {
        is_touch_inside = true;
    }
}

void ToggleButton::touchMoved(ofTouchEventArgs & touch){
    
}

void ToggleButton::touchUp(ofTouchEventArgs & touch){
    if (is_touch_inside and is_inside(touch.x, touch.y)) {
        is_on = !is_on;
        is_touch_inside = false;
        ofNotifyEvent(onClick, is_on); //add
    }
}

void ToggleButton::touchDoubleTap(ofTouchEventArgs & touch){
    
}

void ToggleButton::touchCancelled(ofTouchEventArgs & touch){
    
}

bool ToggleButton::is_inside(float x,float y){
    if(offset.x < x and x < offset.x + width){
        if (offset.y < y and y < offset.y + height) {
            return true;
        }
    }
    return false;
}

