#include "TouchManager.h"
#include "boost/lexical_cast.hpp"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace bluecadet {
namespace touch {

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace bluecadet::views;


//==================================================
// Lifecycle
//

TouchManager::TouchManager() :
	mDiscardMissedTouches(true)
{
}

TouchManager::~TouchManager() {
}

TouchManagerRef TouchManager::getInstance() {
	static TouchManagerRef instance = nullptr;
	if (!instance) {
		instance = TouchManagerRef(new TouchManager());
	}
	return instance;
}

void TouchManager::update(BaseViewRef rootView) {
	lock_guard<recursive_mutex> scopedUpdateLock(mEventMutex);
	lock_guard<recursive_mutex> scopedTouchMapLock(mTouchIdMutex);

	for (auto& event : mEventQueue) {
		switch (event.phase) {
			case TouchPhase::Began: mainThreadTouchesBegan(event, rootView); break;
			case TouchPhase::Moved: mainThreadTouchesMoved(event, rootView); break;
			case TouchPhase::Ended: mainThreadTouchesEnded(event, rootView); break;
		}
	}

	mEventQueue.clear();
}


//==================================================
// Touch Management
//

void TouchManager::addTouchEvent(const int id, const ci::vec2& position, const TouchType type, const TouchPhase phase) {
	lock_guard<recursive_mutex> scopedUpdateLock(mEventMutex);
	mLatestTouchTime = (float)getElapsedSeconds(); // Update the most recent touch time on the app
	mEventQueue.push_back(TouchEvent(id, position, type, phase));
}

void TouchManager::endTouch(TouchEvent& touchEvent) {
	TouchViewRef view = nullptr;

	{// scoped lock start
		lock_guard<recursive_mutex> scopedTouchMapLock(mTouchIdMutex);

		// remove view
		const auto viewIt = mViewsByTouchId.find(touchEvent.id);

		if (viewIt != mViewsByTouchId.end()) {
			view = viewIt->second.lock();
			mViewsByTouchId.erase(viewIt);
		}

		// remove event
		const auto eventIt = mEventsByTouchId.find(touchEvent.id);
		if (eventIt != mEventsByTouchId.end()) {
			mEventsByTouchId.erase(eventIt);
		}

	}// scoped lock end

	if (view) {
		touchEvent.target = view;
		touchEvent.localPosition = view->convertGlobalToLocal(touchEvent.position);
	}

	mDidEndTouch(touchEvent);

	if (view) {
		view->processTouchEnded(touchEvent);
	}
}

void TouchManager::mainThreadTouchesBegan(TouchEvent& touchEvent, views::BaseViewRef rootView) {

	TouchView* view = getTopViewAtPosition(touchEvent.position, rootView);

	if (view) {
		touchEvent.target = view->shared_from_this();
		touchEvent.localPosition = view->convertGlobalToLocal(touchEvent.position);
	}

	mDidBeginTouch(touchEvent);

	if (view) {
		mViewsByTouchId[touchEvent.id] = views::TouchViewWeakRef(touchEvent.target);
		view->processTouchBegan(touchEvent);
	}

	if (view || !mDiscardMissedTouches) {
		mEventsByTouchId[touchEvent.id] = touchEvent;
	}
}

void TouchManager::mainThreadTouchesMoved(TouchEvent& touchEvent, views::BaseViewRef rootView) {
	
	auto view = getTouchViewForId(touchEvent.id);
	
	if (view) {
		touchEvent.target = view;
		touchEvent.localPosition = view->convertGlobalToLocal(touchEvent.position);
	}

	mDidMoveTouch(touchEvent);

	if (view) {
		view->processTouchMoved(touchEvent);
	}

	if (view || !mDiscardMissedTouches) {
		mEventsByTouchId[touchEvent.id] = touchEvent;
	}
}

void TouchManager::mainThreadTouchesEnded(TouchEvent& touchEvent, views::BaseViewRef rootView) {
	endTouch(touchEvent);
}


//==================================================
// View Helpers
//

TouchViewRef TouchManager::getTouchViewForId(const int touchId) {
	lock_guard<recursive_mutex> scopedTouchMapLock(mTouchIdMutex);
	const auto touchViewIt = mViewsByTouchId.find(touchId);
	const bool containsId = touchViewIt != mViewsByTouchId.end();

	if (!containsId) {
		// Stop if we can't find this object
		return nullptr;
	}

	// Try to get a strong pointer; This could return nullptr
	return touchViewIt->second.lock();
}

TouchView* TouchManager::getTopViewAtPosition(const ci::vec2 &position, BaseViewRef rootView) {
	if (!rootView) {
		return nullptr;
	}

	if (rootView->isHidden()) {
		// Don't check for touches in this view or in children if hidden
		return nullptr;
	}

	TouchView* obj = dynamic_cast<TouchView*>(rootView.get());

	if (obj && (!obj->isTouchEnabled() || !obj->canAcceptTouch())) {
		// Don't check for touches in this view or in children if untouchable
		return nullptr;
	}

	// Go through children first
	const auto& children = rootView->getChildren();
	for (auto it = children.rbegin(); it != children.rend(); ++it) {
		const auto& touchedChild = getTopViewAtPosition(position, *it);
		if (touchedChild) {
			return touchedChild;
		}
	}

	if (obj) {
		// Check if the object itself is touched if none of the children were
		const vec2 localPosition = obj->convertGlobalToLocal(position);

		if (obj->containsPoint(localPosition)) {
			return obj;
		}
	}

	return nullptr;
}


//==================================================
// Debugging
//

void TouchManager::debugDrawTouches() {
	const auto circleColor = ColorA(1.0f, 0.0f, 0.0f, 0.5f);
	const auto labelColor = Color(1, 1, 1);
	const auto labelFont = Font("Arial", 24.0f);

	lock_guard<recursive_mutex> scopedTouchMapLock(mTouchIdMutex);

	for (const auto& it : mEventsByTouchId) {
		gl::ScopedColor scopedColor(circleColor);
		const auto& touchEvent = it.second;
		gl::drawSolidCircle(touchEvent.position, 20.0f, 32);
		gl::drawString(to_string(touchEvent.id), touchEvent.position - vec2(-40.0f, 0.0f), labelColor, labelFont);
	}
}

}
}