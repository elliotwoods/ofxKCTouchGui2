#include "Controller.h"
#include "ofxAssets.h"
#include "ofAppRunner.h"

namespace ofxKCTouchGui {
	//----------
	Controller * Controller::singleton = 0;
	
	//----------
	Controller & Controller::X() {
		return * Controller::singleton;
	}
	
	//----------
	Controller::Controller() {
		this->zoom = 1.0f;
		Controller::singleton = this;
	}
	
	//----------
	void Controller::init() {
		ofxAssets::AssetRegister.addAddon("ofxKCTouchGui2");
		ofRegisterTouchEvents(this);
	}
	
	//----------
	void Controller::add(shared_ptr<ofxKCTouchGui::Element> element) {
		this->elements.push_back(element);
	}
	
	//----------
	void Controller::drop(shared_ptr<ofxKCTouchGui::Element> element) {
		bool found = false;
		while (!found) {
			for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
				if (*it == element) {
					this->elements.erase(it);
					found = true;
				}
			}
		}
	}
	
	//----------
	void Controller::update() {
		for(auto element : this->elements) {
			element->update();
		}
		for(auto touch : this->touches) {
			touch.second->clearFrameMovement();
		}
	}
	//----------
	void Controller::draw() {
		ofPushMatrix();
		ofScale(this->zoom, this->zoom);
		for(auto element : this->elements) {
			ofPushMatrix();
			ofTranslate(element->getBounds().getTopLeft());
			element->draw();
			ofPopMatrix();
		}
		for(auto touch : this->touches) {
			touch.second->drawDebug();
		}
		ofPopMatrix();
	}
	//----------
	void Controller::touchDown(ofTouchEventArgs & rawTouch) {
		shared_ptr<Touch> touch;
		
		//check if we've already got this touch in the register (we basically never should at this point)
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			touch = shared_ptr<Touch>(new Touch(rawTouch, zoom));
			this->touches.insert(pair<int, shared_ptr<Touch> >(rawTouch.id, touch));
		} else {
			touch = findTouch->second;
		}
		for(auto it = this->elements.rbegin(); it != this->elements.rend(); it++) {
			if (!touch->isAttached()) {
				auto element = *it;
				element->touchDown(touch);
			}
		}
	}
	
	//----------
	void Controller::touchMoved(ofTouchEventArgs & rawTouch) {
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			ofLogError("ofxKCTouch") << "We're receiving a touchMoved event before a touchDown. The world has gone to hell";
			return;
		}
		
		auto & touch = findTouch->second;
		touch->moveTo((ofVec2f &) rawTouch / zoom);
		
		for(auto element : this->elements) {
			if (touch->isAttachedTo(element.get())) {
				element->touchMoved(touch);
			}
		}
	}
	
	//----------
	void Controller::touchUp(ofTouchEventArgs & rawTouch) {
		auto findTouch = this->touches.find(rawTouch.id);
		if (findTouch == this->touches.end()) {
			ofLogError("ofxKCTouch") << "We're receiving a touchUp event before a touchDown. The world has gone to hell";
			return;
		}
		
		auto & touch = findTouch->second;
		
		for(auto element : this->elements) {
			element->touchUp(touch);
		}
		
		this->touches.erase(findTouch);
	}
	
	//----------
	const vector<shared_ptr<Element> > & Controller::getElements() const {
		return this->elements;
	}
	
	//----------
	const map<int, shared_ptr<Touch> > & Controller::getTouches() const {
		return this->touches;
	}
	
	//----------
	void Controller::setZoom(float zoom) {
		this->zoom = zoom;
	}
	
	//----------
	float Controller::getZoom() const {
		return this->zoom;
	}
	
	//----------
	float Controller::getWidth() const {
		if(ofGetWidth() > ofGetHeight()) { // fix for switched dimensions on older iPads
			return ofGetWidth() / zoom;
		} else {
			return ofGetHeight() / zoom;
		}
	}
	
	//----------
	float Controller::getHeight() const {
		if(ofGetWidth() > ofGetHeight()) { // fix for switched dimensions on older iPads
			return ofGetHeight() / zoom;
		} else {
			return ofGetWidth() / zoom;
		}
	}
}