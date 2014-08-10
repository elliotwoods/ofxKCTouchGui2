#include "Element.h"

#define CHECK_ENABLED if (!this->enabled)return;
namespace ofxKCTouchGui {
	//---------
	Element::Element() {
		this->enabled = true;
	}
	
	//---------
	void Element::update() {
		ofNotifyEvent(this->onUpdate, this);
	}
	
	//---------
	void Element::draw() {
		CHECK_ENABLED
		ofNotifyEvent(this->onDraw, this);
	}
	
	//---------
	void Element::setEnabled(bool enabled) {
		this->enabled = enabled;
	}
	
	//---------
	bool Element::getEnabled() const {
		return this->enabled;
	}
	
	//---------
	void Element::touchDown(shared_ptr<Touch> touch) {
		CHECK_ENABLED
		if (this->bounds.inside(* touch)) {
			touch->attach(this);
			this->attachedTouches.insert(touch);
			ofNotifyEvent(this->onTouchDown, * touch, this);
		}
	}
	
	//---------
	void Element::touchUp(shared_ptr<Touch> touch) {
		CHECK_ENABLED
		if (touch->isAttachedTo(this)) {
			if (this->bounds.inside(* touch) && ! touch->hasMoved()) {
				ofNotifyEvent(this->onHit, * touch, this);
			}
			touch->detach();
			this->attachedTouches.erase(touch);
		}
	}
	
	//---------
	void Element::touchMoved(shared_ptr<Touch> touch) {
		CHECK_ENABLED
		if (touch->isAttachedTo(this)) {
			ofNotifyEvent(this->onTouchMove, * touch, this);
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