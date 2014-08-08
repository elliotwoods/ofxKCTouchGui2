#include "Element.h"

namespace ofxKCTouchGui {
	//---------
	Element::Element() {
		
	}
	
	//---------
	void Element::touchDown(shared_ptr<Touch> touch) {
		if (this->bounds.inside(* touch)) {
			touch->attach(this);
			this->attachedTouches.insert(touch);
		}
	}
	
	//---------
	void Element::touchUp(shared_ptr<Touch> touch) {
		if (touch->isAttachedTo(this)) {
			if (this->bounds.inside(* touch)) {
				ofNotifyEvent(this->onHit, * touch, this);
			}
			touch->detach();
			this->attachedTouches.erase(touch);
		}
	}
	
	//---------
	void Element::touchDragged(shared_ptr<Touch> touch) {
		if (touch->isAttachedTo(this)) {
			ofNotifyEvent(this->onDrag, * touch, this);
		}
	}
	
	//---------
	void Element::setBounds(const ofRectangle & bounds) {
		this->bounds = bounds;
		ofRectangle boundsCopy = bounds;
		ofNotifyEvent(this->onBoundsChange, boundsCopy, this);
	}
	
	//---------
	const ofRectangle & Element::getBounds() const {
		return this->bounds;
	}

	//---------
	ofRectangle Element::getLocalBounds() const {
		auto localBounds = this->bounds;
		localBounds.setPosition(0.0f, 0.0f);
		return localBounds;
	}
	
	//---------
	int Element::getTouchCount() const {
		return this->attachedTouches.size();
	}
	
	//---------
	const set<shared_ptr<Touch> > & Element::getAttachedTouches() const {
		return this->attachedTouches;
	}
}