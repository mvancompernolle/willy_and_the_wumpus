#include "../includes/MainMenu.h"
#include "../includes/ServiceLocator.h"
#include "../includes/ResourceManager.h"

MainMenu::MainMenu( GLuint w, GLuint h ) {
	width = w;
	height = h;

	// initialize buttons
	bExit = Button( glm::vec2( width * 0.2f, height * 0.7f ), glm::vec2( width * 0.25f, height * 0.2f ) );
	bPlay = Button( glm::vec2( width * 0.55f, height * 0.7f ), glm::vec2( width * 0.25f, height * 0.2f ) );
	bExit.setText( "Exit Game" );
	bPlay.setText( "Play Game" );
	bExit.setOnClickFunction( [&]() {
		state = EXIT;
	} );
	bPlay.setOnClickFunction( [&]() {
		state = PLAY;
	} );

	// load background
	ResourceManager::loadTexture( "cave_entrance.jpg", GL_FALSE, "cave_entrance" );

	// play eerie music
	ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "Intrepid.mp3", GL_TRUE );
	ServiceLocator::getAudio().setMasterVolume( 0.5f );
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
	// render background
	ServiceLocator::getGraphics().draw2DTexture( ResourceManager::getTexture( "cave_entrance" ), glm::vec2( 0.0f ), glm::vec2( width, height ), 0.0f );

	// render buttons
	bPlay.render( ServiceLocator::getGraphics() );
	bExit.render( ServiceLocator::getGraphics() );

	// render game title
	ServiceLocator::getGraphics().renderText(ResourceManager::getFont("default"), "WILLY AND THE WUMPUS!", glm::vec2( width / 2.0f, height * 0.10f ), 
		3.0f, glm::vec3(0.0f), HOR_CENTERED, VERT_CENTERED);
}
