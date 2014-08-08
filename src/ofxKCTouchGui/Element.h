#pragma once

#include "Touch.h"

#include "ofRectangle.h"
#include "ofEventUtils.h"

#include <set>

namespace ofxKCTouchGui {
	class Element {
	public:
		Element();
		void touchDown(shared_ptr<Touch>); ///< call attach() to take ownership of this touch
		void touchUp(shared_ptr<Touch>);
		void touchDragged(shared_ptr<Touch>);
		
		void setBounds(const ofRectangle &);
		const ofRectangle & getBounds() const;
		ofRectangle getLocalBounds() const;
		
		virtual void draw() = 0;
		
		int getTouchCount() const;
		const set<shared_ptr<Touch> > & getAttachedTouches() const;
		
		ofEvent<Touch> onHit;
		ofEvent<Touch> onDrag;
		ofEvent<ofRectangle> onBoundsChange;
	protected:
		ofRectangle bounds;
		set<shared_ptr<Touch> > attachedTouches;
	};
}