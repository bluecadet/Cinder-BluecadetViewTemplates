/**+---------------------------------------------------------------------------
Bluecadet Interactive $year$
Developers:
Contents:
Comments:
----------------------------------------------------------------------------*/

#pragma once
#include "cinder/app/App.h"
#include "cinder/Timeline.h"
#include "cinder/Shape2d.h"

#include "LineView.h"

typedef std::shared_ptr<class $safeitemname$>	$safeitemname$Ref;

class $safeitemname$ : public bluecadet::views::LineView {

public:

	$safeitemname$();
	~$safeitemname$() {};
	void						setup();
	static $safeitemname$Ref	create();

protected:

private:


};

