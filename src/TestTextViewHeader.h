/**+---------------------------------------------------------------------------
Bluecadet Interactive 2016
Developers:
Contents:
Comments:
----------------------------------------------------------------------------*/

#pragma once
#include "cinder/app/App.h"
#include "cinder/Timeline.h"
#include "cinder/Shape2d.h"

#include "TextView.h"

typedef std::shared_ptr<class TestTextViewHeader>	TestTextViewHeaderRef;

class TestTextViewHeader : public bluecadet::views::TextView {

public:

	TestTextViewHeader();
	~TestTextViewHeader() {};
	void							setup();
	static TestTextViewHeaderRef	create();

protected:

private:


};

