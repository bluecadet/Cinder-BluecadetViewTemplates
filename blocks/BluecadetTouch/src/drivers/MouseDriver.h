//+---------------------------------------------------------------------------
//  Bluecadet Interactive 2014
//	Developers: Paul Rudolph & Stacey Martens
//  Contents: Code for mouse driver to be used with the touch manager class
//  Comments: This mouse driver was based off of Cinder's listenerBasic sample 
//----------------------------------------------------------------------------

#pragma once
#include "cinder/app/App.h"
#include "TouchManager.h"

namespace bluecadet {
namespace touch {
namespace drivers {

class MouseDriver {

public:
	MouseDriver();
	~MouseDriver();
	void connect();
	void disconnect();

private:
	//! Signals
	ci::signals::Connection mMouseBeganConnection;
	ci::signals::Connection mMouseMovedConnection;
	ci::signals::Connection mMouseEndConnection;

	void mouseBegan(const ci::app::MouseEvent &event);
	void mouseMoved(const ci::app::MouseEvent &event);
	void mouseEnded(const ci::app::MouseEvent &event);

	TouchManagerRef	mTouchManagerPntr;
	int				mTouchId;
};

}
}
}