#include "NativeTouchDriver.h"

using namespace ci::app;

namespace bluecadet {
namespace touch {
namespace drivers {

NativeTouchDriver::NativeTouchDriver() {
	mTouchManagerPntr = NULL;
}

void NativeTouchDriver::connect() {
	// Connect to the application window touch event signals
	ci::app::WindowRef window = cinder::app::getWindow();

	if (window) {
		//began
		mTouchBeganConnection = window->getSignalTouchesBegan().connect(std::bind(&NativeTouchDriver::nativeTouchBegan, this, std::placeholders::_1));
		mTouchMovedConnection = window->getSignalTouchesMoved().connect(std::bind(&NativeTouchDriver::nativeTouchMoved, this, std::placeholders::_1));
		mTouchEndConnection = window->getSignalTouchesEnded().connect(std::bind(&NativeTouchDriver::nativeTouchEnded, this, std::placeholders::_1));
	}

	// Shared pointer to the Touch Manager
	mTouchManagerPntr = TouchManager::getInstance();
}

NativeTouchDriver::~NativeTouchDriver() {
	// Disconnect from the mouse signals
	mTouchBeganConnection.disconnect();
	mTouchMovedConnection.disconnect();
	mTouchEndConnection.disconnect();

	// Remove the pointer to the touch manager
	mTouchManagerPntr = NULL;
}

void NativeTouchDriver::disconnect() {
	// Disconnect from the mouse signals
	mTouchBeganConnection.disconnect();
	mTouchMovedConnection.disconnect();
	mTouchEndConnection.disconnect();

	// Remove the pointer to the touch manager
	mTouchManagerPntr = NULL;
}

void NativeTouchDriver::nativeTouchBegan(const cinder::app::TouchEvent &event) {
	if (mTouchManagerPntr) {
		for (cinder::app::TouchEvent::Touch touch : event.getTouches())
			mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Began);
	}
}

void NativeTouchDriver::nativeTouchMoved(const cinder::app::TouchEvent &event) {
	if (mTouchManagerPntr) {
		for (cinder::app::TouchEvent::Touch touch : event.getTouches())
			mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Moved);
	}
}

void NativeTouchDriver::nativeTouchEnded(const  cinder::app::TouchEvent &event) {
	if (mTouchManagerPntr) {
		for (cinder::app::TouchEvent::Touch touch : event.getTouches())
			mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Ended);
	}
}

}
}
}