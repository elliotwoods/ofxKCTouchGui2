#pragma once

#include "Element.h"
#include "Touch.h"

#include "ofEvents.h"
#include "ofGraphics.h"

#include <map>
namespace ofxKCTouchGui {
	class Controller {
	public:
		static Controller & X();
		Controller();
		void init();
		void add(shared_ptr<Element>);
		void drop(shared_ptr<Element>);

		void update();
		void draw();
		
		void touchDown(ofTouchEventArgs &);
		void touchMoved(ofTouchEventArgs &);
		void touchUp(ofTouchEventArgs &);
		void touchDoubleTap(ofTouchEventArgs &) { }
		void touchCancelled(ofTouchEventArgs &) { }
		
		const vector<shared_ptr<Element> > & getElements() const;
		const map<int, shared_ptr<Touch> > & getTouches() const;
		
		void setZoom(float zoom = 1.0f);
		float getZoom() const;
		
		float getWidth() const;
		float getHeight() const;
		
		void setBrokenRotation(bool);
	protected:
		vector<shared_ptr<Element> > elements;
		map<int, shared_ptr<Touch> > touches;
		float zoom;
		bool brokenRotation;
		static Controller * singleton;
	};
}