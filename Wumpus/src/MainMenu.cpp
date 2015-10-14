#include "../includes/MainMenu.h"
#include "../includes/ServiceLocator.h"
#include "../includes/ResourceManager.h"

MainMenu::MainMenu( GLuint w, GLuint h ) {
	width = w;
	height = h;

	// initialize buttons
	bExit = Button( glm::vec2( width * 0.2f, height * 0.6f ), glm::vec2( width * 0.25f, height * 0.2f ) );
	bPlay = Button( glm::vec2( width * 0.55f, height * 0.6f ), glm::vec2( width * 0.25f, height * 0.2f ) );
	bExit.setText( "Exit Game" );
	bPlay.setText( "Play Game" );
	bExit.setOnClickFunction( [&]() {
		state = EXIT;
	} );
	bPlay.setOnClickFunction( [&]() {
		state = PLAY;
	} );
}


MainMenu::~MainMenu() {
}

void MainMenu::init() {
	state = MAIN;
	ServiceLocator::getInput().addOnClickObserver( &bPlay );
	ServiceLocator::getInput().addOnClickObserver( &bExit );
}

STATE MainMenu::getMenuState() {
	if ( state == PLAY ) {
		// Unregister from input
		ServiceLocator::getInput().removeOnClickObserver( &bExit );
		ServiceLocator::getInput().removeOnClickObserver( &bPlay );
	}
	return state;
}

void MainMenu::render( GLfloat dt ) {
	// render buttons
	bPlay.render( ServiceLocator::getGraphics() );
	bExit.render( ServiceLocator::getGraphics() );

	// render game title
	ServiceLocator::getGraphics().renderText(ResourceManager::getFont("default"), "WILLY AND THE WUMPUS!", glm::vec2( width / 2.0f, height * 0.3f ), 
		3.0f, glm::vec3(1.0f, 0.0f, 1.0f), HOR_CENTERED, VERT_CENTERED);
}
