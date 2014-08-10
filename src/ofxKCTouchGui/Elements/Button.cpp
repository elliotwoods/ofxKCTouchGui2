#include "Button.h"
#include "ofMain.h"

namespace ofxKCTouchGui {
	namespace Elements {
		//----------
		Button::Button(const ofImage & image) {
			this->upImage = image;
			this->downImage = image;
			
			this->upColor = ofColor(255);
			this->downColor = ofColor(100);
			
			ofAddListener(this->onDraw, this, &Button::draw);
			ofAddListener(this->onHit, this, &Button::hit);
		}
		
		//----------
		void Button::setUpImage(const ofImage & image) {
			this->upImage = image;
		}
		
		//----------
		void Button::setDownImage(const ofImage & image) {
			this->downImage = image;
		}
		
		//----------
		void Button::setUpColor(ofColor color) {
			this->upColor = color;
		}
		
		//----------
		void Button::setDownColor(ofColor color) {
			this->downColor = color;
		}
		
		//----------
		void Button::draw() {
			ofPushStyle();
			if (this->getTouchCount() == 0) {
				ofSetColor(this->upColor);
				this->upImage.draw(this->getLocalBounds());
			} else {
				ofSetColor(this->downColor);
				this->downImage.draw(this->getLocalBounds());
			}
			ofPopStyle();
		}
		
		//----------
		void Button::hit(Touch &) {
			ofNotifyEvent(this->onButtonHit, this);
		}
	}
}