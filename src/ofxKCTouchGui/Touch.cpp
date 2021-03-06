#include "Touch.h"

#include "ofMain.h"

namespace ofxKCTouchGui {
	//---------
	Touch::Touch(const ofTouchEventArgs & rawTouch, float zoom) {
		(ofVec2f &) *this = (ofVec2f &) rawTouch / zoom;
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
		
		//first 0.1s of movement aren't counted
		if (this->getAge() > 0.1f) {
			this->moved = true;
		}
		
		(ofVec2f &) * this = position;
	}
	
	//---------
	void Touch::clearFrameMovement() {
		this->movement = ofVec2f();
	}
	
	//---------
	int Touch::getIndex() const {
		return this->index;
	}
	
	//---------
	const ofVec2f & Touch::getPosition() const {
		return * (ofVec2f *) this;
	}
	
	//---------
	bool Touch::isAttached() const {
		return (bool) this->attachedTo;
	}
	
	//---------
	bool Touch::hasMoved() const {
		return this->moved;
	}

	//---------
	ofVec2f Touch::getMovement() const {
		if (this->hasMoved()) {
			return this->movement;
		} else {
			return ofVec2f(0.0f, 0.0f);
		}
	}
	
	//---------
	ofVec2f Touch::getPreviousPosition() const {
		return (ofVec2f &) * this - this->getMovement();
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
	void Touch::drawDebug() const {
		ofPushStyle();
		ofSetLineWidth(1.0f);
		ofNoFill();
		ofSetCircleResolution(30.0f);
		
		ofCircle((ofVec2f &) * this, this->getAge() * 50.0f);
		stringstream status;
		status << * this;
		ofDrawBitmapString(status.str(), (ofVec2f &) * this + ofVec2f(100.0f, 100.0f));
		
		ofPopStyle();
	}
	
	//---------
	ostream & operator<<(ostream & os, const Touch & touch) {
		os << "[" << touch.getIndex() << "] (" << touch.x << ", " << touch.y << ")\t" << touch.getAge() << "s\t[" << (touch.isAttached() ? "a" : " ") << (touch.hasMoved() ? "m" : " ") << "]";
		return os;
	}
}