//+---------------------------------------------------------------------------
//  Bluecadet Interactive 2016
//	Developers: Paul Rudolph, Stacey Martens & Ben Bojko
//  Contents: 
//  Comments: 
//----------------------------------------------------------------------------

#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <mutex>
#include <boost/signals2.hpp>

#include "Touch.h"
#include "TouchView.h"

namespace bluecadet {
namespace touch {

typedef std::shared_ptr<class TouchManager> TouchManagerRef;

class TouchManager {

public:

	//==================================================
	// Broadcast signals
	//
	boost::signals2::signal<void(const TouchEvent& touchEvent)>	mDidBeginTouch;	//! Fired before any touch objects receive this event
	boost::signals2::signal<void(const TouchEvent& touchEvent)>	mDidMoveTouch;	//! Fired before any touch objects receive this event
	//boost::signals2::signal<void(const TouchEvent& touchEvent)>	mDidCancel;		//! Fired before any touch objects receive this event
	boost::signals2::signal<void(const TouchEvent& touchEvent)>	mDidEndTouch;	//! Fired before any touch objects receive this event


	//==================================================
	// Lifecycle
	//

	//! Shared singleton instance
	static TouchManagerRef getInstance();
	virtual ~TouchManager();

	void					update(views::BaseViewRef rootView);
	void					debugDrawTouches();


	//==================================================
	// Touch Management
	//
	
	//! Adds a touch event to the event queue which will be processed on the main thread and forwarded to views
	void					addTouchEvent(const int id, const ci::vec2& position, const TouchType type, const TouchPhase phase);

	//! Removes a touch if it exists. Views associated to this event will be notifed with touchEnded.
	// TODO: Rethink naming;
	inline void				endTouch(TouchEvent& touchEvent);


	//==================================================
	// Accessors
	//

	//! Time in seconds of the most recent touch event regardless of touch type or phase
	float                   getLatestTouchTime() { return mLatestTouchTime; };

	//! Immediately discard touches that begin outside of any active touch view if enabled
	bool					getDiscardMissedTouches() const { return mDiscardMissedTouches; }
	void					setDiscardMissedTouches(const bool value) { mDiscardMissedTouches = value; }

protected:
	//! Private to make the TouchManager a singleton
	TouchManager();


	//==================================================
	// Internal Helpers
	//

	//! TUIO touches aren't always on the main thread. So when we receive touches through TUIO, we want to hold onto the functions in the mRenderFunctionQueue, 
	//and on each update we will call all of the functions in that deque
	void					mainThreadTouchesBegan(TouchEvent& touchEvent, views::BaseViewRef rootView);
	void					mainThreadTouchesMoved(TouchEvent& touchEvent, views::BaseViewRef rootView);
	void					mainThreadTouchesEnded(TouchEvent& touchEvent, views::BaseViewRef rootView);

	views::TouchViewRef		getTouchViewForId(const int touchId);

	//! Find the object that the current touch is hitting by navigating up the view hierarchy
	views::TouchView*		getTopViewAtPosition(const ci::vec2 &position, views::BaseViewRef rootView);

	//==================================================
	// Members
	//

	std::recursive_mutex						mTouchIdMutex;
	std::map<int, views::TouchViewWeakRef>		mViewsByTouchId;	// Stores views that are currently being touched
	std::map<int, TouchEvent>					mEventsByTouchId;	// Whatever the latest event is for a touch id

	std::recursive_mutex						mEventMutex;
	std::deque<TouchEvent>						mEventQueue; // Collects all touch events until they're processed on the main thread

	bool										mDiscardMissedTouches = true;
	float                                       mLatestTouchTime;
};

}
}