#pragma once

#include "../Element.h"
#include "ofImage.h"

namespace ofxKCTouchGui {
	namespace Elements {
		class Button : public Element {
		public:
			Button(const ofImage &);
			
			void setUpImage(const ofImage &);
			void setDownImage(const ofImage &);
			void setUpColor(ofColor);
			void setDownColor(ofColor);
			
			ofEvent<void> onButtonHit;
		protected:
			void draw();
			void hit(Touch &);
			ofImage upImage, downImage;		
			ofColor upColor, downColor;
		};
	}
}