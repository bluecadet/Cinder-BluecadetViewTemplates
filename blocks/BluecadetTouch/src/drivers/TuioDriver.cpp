#include "TuioDriver.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace bluecadet {
namespace touch {
namespace drivers {

TuioDriver::TuioDriver() {
	mTouchManagerPntr = touch::TouchManager::getInstance();
}

TuioDriver::~TuioDriver() {
	if (mTuioReceiver) mTuioReceiver->disconnect();
}

void TuioDriver::connect() {

	mTuioReceiver = std::shared_ptr<tuio::Receiver>(new tuio::Receiver());
	mTuioReceiver->connect();

	// Callbacks for touches
	mTuioReceiver->setAddedFn<tuio::Cursor2d>(std::bind(&TuioDriver::touchBegan, this, std::placeholders::_1));
	mTuioReceiver->setUpdatedFn<tuio::Cursor2d>(std::bind(&TuioDriver::touchMoved, this, std::placeholders::_1));
	mTuioReceiver->setRemovedFn<tuio::Cursor2d>(std::bind(&TuioDriver::touchEnded, this, std::placeholders::_1));

	// Callbacks for objects
	/*
	//! TODO: @SM Complete when we have objects for testing

	mTuioReceiver->setAddedFn<tuio::Object2d>(std::bind(&TuioDriver::objectBegan, this, std::placeholders::_1));
	mTuioReceiver->setUpdatedFn<tuio::Object2d>(std::bind(&TuioDriver::objectMoved, this, std::placeholders::_1));
	mTuioReceiver->setRemovedFn<tuio::Object2d>(std::bind(&TuioDriver::objectEnded, this, std::placeholders::_1));
	*/
}

void TuioDriver::disconnect() {
	try {
		if (mTuioReceiver) mTuioReceiver->disconnect();
	}
	catch (...) {
		cout << "TuioDriver: Couldn't disconnect TuioDriver From the TouchManager. TouchManager may have already been deleted." << endl;
	}

	mTouchManagerPntr = NULL;
}


void TuioDriver::touchBegan(const tuio::Cursor2d &cursor) {
	if (mTouchManagerPntr) {
		ci::app::TouchEvent::Touch touch = cursor.convertToTouch(getWindow());
		mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Began);
	}
}

void TuioDriver::touchMoved(const tuio::Cursor2d &cursor) {
	if (mTouchManagerPntr) {
		ci::app::TouchEvent::Touch touch = cursor.convertToTouch(getWindow());
		mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Moved);
	}
}

void TuioDriver::touchEnded(const tuio::Cursor2d &cursor) {
	if (mTouchManagerPntr) {
		ci::app::TouchEvent::Touch touch = cursor.convertToTouch(getWindow());
		mTouchManagerPntr->addTouchEvent(touch.getId(), touch.getPos(), TouchType::Touch, TouchPhase::Ended);
	}
}



/*
//! TODO: @SM Complete when we have objects for testing

void TuioDriver::objectBegan(const tuio::Object2d &object) {
	if (mTouchManagerPntr) {
	}
}

void TuioDriver::objectMoved(const tuio::Object2d &object) {
	if (mTouchManagerPntr) {
	}
}

void TuioDriver::objectEnded(const tuio::Object2d &object) {
	if (mTouchManagerPntr) {
	}
}
*/


}
}
}
