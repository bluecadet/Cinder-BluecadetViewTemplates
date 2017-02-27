/**+---------------------------------------------------------------------------
Bluecadet Interactive $year$
Developers:
Contents:
Comments:
----------------------------------------------------------------------------*/

#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "views/TextView.h"

namespace $rootnamespace$ {

	typedef std::shared_ptr<class $safeitemname$>	$safeitemname$Ref;

	class $safeitemname$ : public bluecadet::views::TextView {

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