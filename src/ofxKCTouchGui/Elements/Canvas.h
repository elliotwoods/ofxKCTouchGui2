#pragma once

#include "ofMain.h"
#include "../Element.h"

namespace ofxKCTouchGui {
	namespace Elements {
		class Canvas : public ofxKCTouchGui::Element {
		public:
			Canvas();
			
			void update();
			void draw();
			
			void setWorkspaceAspect(float aspect); /// aspect : 1.0
			float getWorkspaceAspect() const;
			
			ofEvent<void> onDrawWorkspace;
		protected:
			virtual void touchMoved(Touch &);
			
			ofVec2f viewPosition;
			ofVec2f workspaceSize;
			
			ofParameter<float> zoom;
			
			float elementAspectRatio;
			float workspaceAspectRatio;
			
			ofMatrix4x4 transform; // workspace to element
		};
	}
}