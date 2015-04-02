#include "Canvas.h"
#include "Controller.h"

namespace ofxKCTouchGui {
	namespace Elements {
		//----------
		Canvas::Canvas() {
			this->zoom.set("zoom", 0.8f, 0.01f, 100.0f);
			this->setWorkspaceAspect(4.0f / 3.0f);
			this->viewPosition = ofVec2f();
			ofAddListener(this->onUpdate, this, &Canvas::update);
			ofAddListener(this->onDraw, this, &Canvas::draw);
			ofAddListener(this->onTouchMove, this, & Canvas::touchMoved);
		}
		
		//----------
		void Canvas::update() {
			if (this->getTouchCount() == 2) {
				const auto touches = this->getAttachedTouches();
				ofVec2f mean;
				for(auto touch : touches) {
					mean += (ofVec2f &) * touch;
				}
				mean /= (float) touches.size();
				
				for(auto touch : touches) {
					this->zoom *= sqrt(((ofVec2f &) * touch).distance(mean) / touch->getPreviousPosition().distance(mean));
					this->viewPosition -= ((ofVec3f) touch->getPosition() * this->transform.getInverse() - (ofVec3f) touch->getPreviousPosition() * this->transform.getInverse()) / (float) this->getTouchCount();
				}
			}
			
			this->elementAspectRatio = this->bounds.getWidth() / this->bounds.getHeight();
			
			this->zoom = ofClamp(this->zoom, this->zoom.getMin(), this->zoom.getMax());
			
			//rubber band the view position
			auto globalZoom = Controller::X().getZoom();
			ofVec2f viewPositionClamped;
			viewPositionClamped.x = ofClamp(this->viewPosition.x * globalZoom, -1.0, 1.0f) / globalZoom;
			viewPositionClamped.y = ofClamp(this->viewPosition.y * globalZoom, -1.0, 1.0f) / globalZoom;
			viewPosition = viewPosition * 0.8f + viewPositionClamped * 0.2f;
			
			this->transform.makeIdentityMatrix();
			this->transform.translate(-this->viewPosition);
			auto ourBounds = this->getLocalBounds();
			this->transform.scale(this->workspaceAspectRatio / (ourBounds.getWidth() / ourBounds.getHeight()), 1.0f, 1.0f);
			this->transform.scale(this->zoom, this->zoom, 1.0f);
			this->transform.translate(1.0f, 1.0f, 0.0f);
			this->transform.scale(this->getBounds().getWidth() / 2.0f, this->getBounds().getHeight() / 2.0f, 1.0f);
		}
		
		//----------
		void Canvas::draw() {
			auto bounds = this->getBounds();
			auto zoom = Controller::X().getZoom();
			
			auto globalBounds = bounds;
			globalBounds.x *= zoom;
			globalBounds.y *= zoom;
			globalBounds.width *= zoom;
			globalBounds.height *= zoom;
			
			ofPushView();
			ofViewport(globalBounds);
			ofSetupScreen();
			ofMultMatrix(this->transform);
			
			//fill
			ofPushStyle();
			ofSetLineWidth(0.0f);
			ofSetColor(30);
			ofFill();
			ofRect(-1.0f, -1.0f, 2.0f, 2.0f);
			
			//outline
			ofSetLineWidth(2.0f);
			ofSetColor(200);
			ofNoFill();
			ofRect(-1.0f, -1.0f, 2.0f, 2.0f);
			ofPopStyle();
			
			//minor-lines
			ofPushStyle();
			ofSetColor(100, 100, 100);
			float step = 0.1f;
			for(float x=-1+step; x<1; x+=step) {
				ofLine(x, -1.0f, x, +1.0f);
				ofLine(-1.0f, x, 1.0f, x);
			}
			ofPopStyle();
			
			//mid-lines
			ofPushStyle();
			ofLine(0.0f, -1.0f, 0.0f, +1.0f);
			ofLine(-1.0f, 0.0f, 1.0f, 0.0f);
			ofPopStyle();
			
			//draw workspace contents
			ofNotifyEvent(this->onDrawWorkspace, this);
		
			ofPopView();
		}

		//----------
		void Canvas::setWorkspaceAspect(float aspect) {
			this->workspaceAspectRatio = aspect;
		}

		//----------
		float Canvas::getWorkspaceAspect() const {
			return this->workspaceAspectRatio;
		}
		
		//----------
		void Canvas::touchMoved(Touch & touch) {
			if (this->getTouchCount() != 2) {
				this->viewPosition -= (ofVec3f) touch.getPosition() * this->transform.getInverse() - (ofVec3f) touch.getPreviousPosition() * this->transform.getInverse();
			}
		}
	}
}