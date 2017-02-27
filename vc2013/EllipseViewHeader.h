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

#include "views/EllipseView.h"


namespace $rootnamespace$ {

	typedef std::shared_ptr<class $safeitemname$>	$safeitemname$Ref;

	class $safeitemname$ : public bluecadet::views::EllipseView {

	public:

		enum class State {

		} mState;

		$safeitemname$();
		~$safeitemname$() {};

		void			setup();
		void			updateState($safeitemname$::State newState);

	protected:

	private:

	};

}

