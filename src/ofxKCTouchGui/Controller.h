#pragma once

#include "Element.h"
#include "Touch.h"

#include "ofEvents.h"
#include "ofGraphics.h"

#include <map>
namespace ofxKCTouchGui {
	class Controller {
	public:
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
	protected:
		vector<shared_ptr<Element> > elements;
		map<int, shared_ptr<Touch> > touches;
	};
}