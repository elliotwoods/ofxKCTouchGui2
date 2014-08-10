#pragma once

#include "../Element.h"

namespace ofxKCTouchGui {
	namespace Elements {
		class MultiSelect : public Element {
		public:
			MultiSelect();
			void addOption(string);
			void clearOptions();
			
			int getSelectionIndex() const;
			string getSelectionCaption() const;
			void setSelection(string);
			void setSelection(int);
			
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