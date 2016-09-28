#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BluecadetCinderTemplatesApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void BluecadetCinderTemplatesApp::setup()
{
}

void BluecadetCinderTemplatesApp::mouseDown( MouseEvent event )
{
}

void BluecadetCinderTemplatesApp::update()
{
}

void BluecadetCinderTemplatesApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( BluecadetCinderTemplatesApp, RendererGl )
