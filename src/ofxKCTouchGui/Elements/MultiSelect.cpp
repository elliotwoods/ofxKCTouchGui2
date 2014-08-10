#include "MultiSelect.h"
#include "ofMain.h"
#include "ofxAssets.h"

#define INNER_MARGIN 20

namespace ofxKCTouchGui {
	namespace Elements {
		//----------
		MultiSelect::MultiSelect() {
			ofAddListener(this->onDraw, this, &MultiSelect::draw);
			ofAddListener(this->onTouchDown, this, &MultiSelect::touch);
			ofAddListener(this->onTouchMove, this, &MultiSelect::touch);
			this->selection = -1;
			this->itemWidth = 10.0f;
		}

		//----------
		void MultiSelect::addOption(string option) {
			this->options.push_back(option);
			this->update();
		}
		
		//----------
		void MultiSelect::clearOptions() {
			this->options.clear();
			this->update();
		}
		
		//----------
		int MultiSelect::getSelectionIndex() const {
			return this->selection;
		}
		
		//----------
		string MultiSelect::getSelectionCaption() const {
			if (this->options.empty()) {
				return "";
			} else {
				return this->options.at(this->selection);
			}
		}
		
		//----------
		void MultiSelect::update() {
			if (this->options.empty()) {
				this->selection = -1;
			} else {
				this->selection = ofClamp(this->selection, 0, this->options.size() - 1);
				this->itemWidth = (this->getLocalBounds().getWidth() - INNER_MARGIN * 2) / (float) this->options.size();
			}
		}
		
		//----------
		void MultiSelect::draw() {
			ofPushStyle();
			
			const auto bounds = this->getLocalBounds();
			//fill
			ofSetLineWidth(0.0f);
			ofFill();
			ofSetColor(40);
			ofRectRounded(bounds, 50.0f);
			
			//draw Selection
			if (this->selection != -1) {
				ofSetColor(80.0f);
				ofRectRounded(ofRectangle(INNER_MARGIN + this->itemWidth * this->selection, INNER_MARGIN, this->itemWidth, this->getLocalBounds().getHeight() - INNER_MARGIN * 2.0f), 50.0f);
			}
			
			ofSetColor(255);
			
			for (int i=0; i<this->options.size(); i++) {
				auto & font = ofxAssets::font("swisop3", 60.0f);
				auto bounds = font.getStringBoundingBox(this->options[i], 0, 0);
				font.drawString(this->options[i], ((float) i + 0.5f) * this->itemWidth + INNER_MARGIN - bounds.getWidth() / 2.0f, (this->getBounds().getHeight() + bounds.getHeight()) / 2.0f);
			}
			
			ofPopStyle();
		}
		
		//----------
		void MultiSelect::touch(Touch & touch) {
			auto localTouchX = touch.x - this->getLocalBounds().x;
			auto newSelection = (localTouchX - INNER_MARGIN) / this->itemWidth;
			this->selection = ofClamp(newSelection, 0, this->options.size() - 1);
		}
	}
}