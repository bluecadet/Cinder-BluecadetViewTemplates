#include "MouseDriver.h"

namespace bluecadet {
namespace touch {
namespace drivers {

MouseDriver::MouseDriver() {
	mTouchManagerPntr = NULL;
	mTouchId = -1;
}

MouseDriver::~MouseDriver() {
	// Disconnect from the mouse signals
	mMouseBeganConnection.disconnect();
	mMouseMovedConnection.disconnect();
	mMouseEndConnection.disconnect();

	// Remove the pointer to the touch manager
	mTouchManagerPntr = NULL;
}

void MouseDriver::connect() {
	// Connect to the application window touch event signals
	ci::app::WindowRef window = cinder::app::getWindow();

	mMouseBeganConnection = window->getSignalMouseDown().connect(std::bind(&MouseDriver::mouseBegan, this, std::placeholders::_1));
	mMouseMovedConnection = window->getSignalMouseDrag().connect(std::bind(&MouseDriver::mouseMoved, this, std::placeholders::_1));
	mMouseEndConnection = window->getSignalMouseUp().connect(std::bind(&MouseDriver::mouseEnded, this, std::placeholders::_1));

	// Shared pointer to the Touch Manager
	mTouchManagerPntr = TouchManager::getInstance();
}

void MouseDriver::disconnect() {
	// Disconnect from the mouse signals
	mMouseBeganConnection.disconnect();
	mMouseMovedConnection.disconnect();
	mMouseEndConnection.disconnect();

	// Remove the pointer to the touch manager
	mTouchManagerPntr = NULL;
}

void MouseDriver::mouseBegan(const cinder::app::MouseEvent &event) {
	if (mTouchManagerPntr) {
		mTouchManagerPntr->addTouchEvent(mTouchId, event.getPos(), TouchType::Mouse, TouchPhase::Began);
	}
}

void MouseDriver::mouseMoved(const cinder::app::MouseEvent &event) {
	if (mTouchManagerPntr) {
		mTouchManagerPntr->addTouchEvent(mTouchId, event.getPos(), TouchType::Mouse, TouchPhase::Moved);
	}
}

void MouseDriver::mouseEnded(const  cinder::app::MouseEvent &event) {
	if (mTouchManagerPntr) {
		mTouchManagerPntr->addTouchEvent(mTouchId, event.getPos(), TouchType::Mouse, TouchPhase::Ended);
	}
}

}
}
}