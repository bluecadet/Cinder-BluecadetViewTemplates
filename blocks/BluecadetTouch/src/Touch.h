#pragma once

namespace bluecadet {

namespace views {
	// Forward declaration of TouchView class and shared_ptr
	typedef std::shared_ptr<class TouchView> TouchViewRef;
}

namespace touch {

//==================================================
// Types
//

enum TouchType { Touch, Mouse, Simulator, Fiducial, Other };

enum TouchPhase { Began, Moved, Ended };

struct TouchEvent {
	// Mandatory values
	int					id				= -1;
	ci::vec2			position		= ci::vec2(0);
	ci::vec2			localPosition	= ci::vec2(0);
	TouchType			type			= Other;
	TouchPhase			phase			= Began;

	// Optional values
	views::TouchViewRef	target			= nullptr;
	bool				canceled		= false;

	TouchEvent() {};

	TouchEvent(const int id, const ci::vec2& position, const TouchType type, const TouchPhase phase) :
		id(id),
		position(position),
		type(type),
		phase(phase)
	{}
};

}
}
