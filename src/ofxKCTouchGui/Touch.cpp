#include "Touch.h"

#include "ofMain.h"

namespace ofxKCTouchGui {
	//---------
	Touch::Touch(const ofTouchEventArgs & rawTouch) {
		(ofVec2f &) *this = (ofVec2f &) rawTouch;
		this->index = rawTouch.id;
		this->moved = false;
		this->bornTime = ofGetElapsedTimeMillis();
		this->attachedTo = NULL;
	}
	
	//---------
	Touch::Touch(int index, const ofVec2f & position) {
		(ofVec2f &) *this = position;
		this->index = index;
		this->moved = false;
		this->bornTime = ofGetElapsedTimeMillis();
		this->attachedTo = NULL;		
	}
	
	//---------
	void Touch::attach(Element * element) {
		this->attachedTo = element;
	}
	
	//---------
	void Touch::detach() {
		this->attachedTo = NULL;
	}
	
	//---------
	void Touch::moveTo(const ofVec2f & position) {
		this->movement = position - (ofVec2f &) * this;
		this->moved = true;
		(ofVec2f &) * this = position;
	}
	
	//---------
	int Touch::getIndex() const {
		return this->index;
	}
	
	//---------
	bool Touch::isAttached() const {
		return (bool) this->attachedTo;
	}
	
	//---------
	bool Touch::isAttachedTo(Element * element) const {
		return this->attachedTo == element;
	}
	
	//---------
	float Touch::getAge() const {
		return (float) (ofGetElapsedTimeMillis() - this->bornTime) / 1000.0f;
	}
	
	//---------
	ostream & operator<<(ostream & os, const Touch & touch) {
		os << "[" << touch.getIndex() << "] (" << touch.x << ", " << touch.y << ")\t" << touch.getAge() << "s\t" << (touch.isAttached() ? "[x]" : "[ ]");
		return os;
	}
}