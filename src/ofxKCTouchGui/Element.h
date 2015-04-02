#pragma once

#include "Touch.h"

#include "ofRectangle.h"
#include "ofEventUtils.h"

#include <set>

namespace ofxKCTouchGui {
	class Element {
	public:
		Element();
		
		void update();
		void draw();
		
		void setEnabled(bool);
		bool getEnabled() const;
		
		void touchDown(shared_ptr<Touch>); ///< call attach() to take ownership of this touch
		void touchUp(shared_ptr<Touch>);
		void touchMoved(shared_ptr<Touch>);
		
		void setBounds(const ofRectangle &);
		const ofRectangle & getBounds() const;
		ofRectangle getLocalBounds() const;
		
		int getTouchCount() const;
		const set<shared_ptr<Touch> > & getAttachedTouches() const;
		
		ofEvent<void> onUpdate;
		ofEvent<void> onDraw;
		ofEvent<Touch> onHit;
		ofEvent<void> onHitSimple;
		ofEvent<Touch> onTouchDown;
		ofEvent<Touch> onTouchMove;
		ofEvent<ofRectangle> onBoundsChange;
	protected:
		ofRectangle bounds;
		set<shared_ptr<Touch> > attachedTouches;
		
		bool enabled;
	};
}