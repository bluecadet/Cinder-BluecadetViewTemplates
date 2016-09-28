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

#include "EllipseView.h"

typedef std::shared_ptr<class TestEllipseViewHeader>	TestEllipseViewHeaderRef;

class TestEllipseViewHeader : public bluecadet::views::EllipseView {

public:

	TestEllipseViewHeader();
	~TestEllipseViewHeader() {};
	void						setup();
	static TestEllipseViewHeaderRef	create();

protected:

private:


};

