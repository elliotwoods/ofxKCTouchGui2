#pragma once

#include "ofVec2f.h"
#include "ofEvents.h"
#include "ofTypes.h"

using namespace std;

namespace ofxKCTouchGui {
	class Element;
	
	class Touch : public ofVec2f {
	public:
		Touch(const ofTouchEventArgs &);
		Touch(int index, const ofVec2f & position);
		
		void attach(Element *);
		void detach();
		void moveTo(const ofVec2f & position);
		
		int getIndex() const;
		
		bool isAttached() const;
		bool isAttachedTo(Element *) const;
		
		float getAge() const;
	protected:
		int index;
		bool moved;
		ofVec2f movement;
		long bornTime;
		Element * attachedTo;
	};
	
	ostream & operator<<(ostream & os, const Touch &);
}