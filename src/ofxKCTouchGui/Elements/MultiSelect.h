#pragma once

#include "../Element.h"

namespace ofxKCTouchGui {
	namespace Elements {
		class MultiSelect : public Element {
		public:
			MultiSelect();
			void addOption(string);
			void clearOptions();
			
			void boundsChange(ofRectangle &);
			
			int getSelectionIndex() const;
			string getSelectionCaption() const;
			void setSelection(string);
			void setSelection(int);
			
			ofEvent<int> onSelectIndex;
			ofEvent<string> onSelectCaption;
		protected:
			void update();
			void draw();
			void touch(Touch &);
			vector<string> options;
			int selection;
			float itemWidth;
		};
	}
}