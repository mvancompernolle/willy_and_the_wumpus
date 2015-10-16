#include "../includes/HuntTheWumpus.h"
#include "../includes/ResourceManager.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

HuntTheWumpus::HuntTheWumpus( GLuint width, GLuint height )
	: width( width ), height( height ),
	rooms{ Room( { 1, 4, 7 } ), Room( { 0, 2, 9 } ), Room( { 1, 3, 11 } ), Room( { 2, 4, 13 } ), Room( { 0, 3, 5 } ), Room( { 4, 6, 14 } ),
		Room( { 5, 7, 16 } ), Room( { 0, 6, 8 } ), Room( { 7, 9, 17 } ), Room( { 1, 8, 10 } ), Room( { 9, 11, 18 } ), Room( { 2, 10, 12 } ),
		Room( { 11, 13, 19 } ), Room( { 3, 12, 14 } ), Room( { 5, 13, 15 } ), Room( { 14, 16, 19 } ), Room( { 6, 15, 17 } ), Room( { 8, 16, 18 } ),
		Room( { 10, 17, 19 } ), Room( { 12, 15, 18 } ) },
	textBox( glm::vec2( width * 0.05f, height * 0.1f ), glm::vec2( width * 0.65f, height * 0.8f ), 8, ResourceManager::getFont( "default" ) ), stateChanged( GL_TRUE ),
	buttonsState( BUTTON_MAIN ), gameOver(GL_FALSE), isWumpusTurn(GL_FALSE)
{
	// initialize text box
	textBox.setPadding( 24.0f, 24.0f );
	textBox.setBorderColor( glm::vec3( 0.0f ) );
	textBox.setLineSpacing( 2.0f );

	// initialize buttons
	GLfloat spaceBetween = 0.05f * height;
	GLfloat buttonYSize = ( ( 0.8f * height - 4 * spaceBetween ) / 5.0f );
	for ( int i = 0; i < 5; ++i ) {
		buttons[i].setSize( glm::vec2( width * 0.2f, buttonYSize ) );
		buttons[i].setPos( glm::vec2( width * 0.75f, ( 0.1f * height + buttonYSize * i + spaceBetween * i ) ) );
	}

	buttons[4].setText( "Quit" );
	buttons[4].setOnClickFunction( [&]() {
		gameOver = GL_TRUE;
	} );

	// load background
	ResourceManager::loadTexture( "cave.jpg", GL_FALSE, "cave_background" );

	// init random
	srand( time( NULL ) );
}

HuntTheWumpus::~HuntTheWumpus() {
}

void HuntTheWumpus::init() {
	gameOver = GL_FALSE;
	isWumpusTurn = GL_FALSE;

	// init textbox
	textBox.clear();
	textBox.setBorderColor( glm::vec3( 0.0f ) );
	textBox.addText( "Welcome to Willy and the Wumpus!", GL_TRUE );
	textBox.addText( "-------------------------------------------------------------------", GL_TRUE );
	textBox.addText( "It plays just like regular Hunt the Wumpus, but your name is Willy!", GL_TRUE );
	textBox.addNewLine();
	ServiceLocator::getInput().addOnClickObserver( &textBox );
	ServiceLocator::getInput().addOnScrollObserver( &textBox );

	// set listeners for buttons
	for ( int i = 0; i < 5; ++i ) {
		ServiceLocator::getInput().addOnClickObserver( &buttons[i] );
	}

	// initialize rooms
	willy = Willy();
	for ( int i = 0; i < 20; ++i ) {
		rooms[i].hasBat = rooms[i].hasHole = GL_FALSE;
	}

	// randomly choose where 2 bats are, 2 holes are
	int room;
	for ( int i = 0; i < 2; ++i ) {
		room = rand() % 20;
		while ( rooms[room].hasBat ) {
			room = rand() % 20;
		}
		rooms[room].hasBat = GL_TRUE;
	}
	for ( int i = 0; i < 2; ++i ) {
		room = rand() % 20;
		while ( rooms[room].hasHole ) {
			room = rand() % 20;
		}
		rooms[room].hasHole = GL_TRUE;
	}

	// put player in room
	GLuint playerRoom = rand() % 20;
	while ( rooms[playerRoom].hasBat || playerRoom == wumpus.currentRoom || rooms[playerRoom].hasHole ) {
		playerRoom = rand() % 20;
	}
	willy.currentRoom = playerRoom;
	// put wumpus at least 2 rooms away
	wumpus.isAwake = GL_FALSE;
	room = rand() % 20;
	while ( willy.canSmellWumpus( rooms, &wumpus, playerRoom, -1, 1 ) ) {
		wumpus.currentRoom = rand() % 20;
	}

	willy.move( rooms, playerRoom, &wumpus, textBox );

	buttonsState = BUTTON_MAIN;
	setOnClickFunctions();
}

void HuntTheWumpus::render( GLfloat dt ) {

	// render background
	ServiceLocator::getGraphics().draw2DTexture( ResourceManager::getTexture( "cave_background" ), glm::vec2( 0.0f ), glm::vec2( width, height ), 0.0f );

	// render textBox
	textBox.render( ServiceLocator::getGraphics() );

	// render buttons
	for ( int i = 0; i < 5; ++i ) {
		buttons[i].render( ServiceLocator::getGraphics() );
	}

	// render info bars
	ServiceLocator::getGraphics().draw2DBox( glm::vec2( width * 0.05f, height * 0.025f ), glm::vec2( width * 0.65f, height * 0.05f ), glm::vec3( 0.0f ) );
	std::stringstream ss;
	ss << "Room: " << willy.currentRoom + 1;
	ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), ss.str().c_str(), glm::vec2( width * 0.075f, height * 0.05f ), 1.0f, glm::vec3( 1.0f ),
		LEFT_ALIGNED, VERT_CENTERED );
	ss.str( std::string() );
	ss << "Arrow Energy: " << willy.numArrows;
	ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), ss.str().c_str(), glm::vec2( width * 0.35f, height * 0.05f ), 1.0f, glm::vec3( 1.0f ),
		HOR_CENTERED, VERT_CENTERED );
	ss.str( std::string() );
	ss << "Arrow Path: ";
	if ( buttonsState == BUTTON_ARROW_PATH || buttonsState == BUTTON_ARROW_PATH_INIT ) {
		for ( int i = 0; i < willy.arrowPath.size(); ++i ) {
			ss << willy.arrowPath[i] + 1;
			if ( i != willy.arrowPath.size() - 1 ) {
				ss << ",";
			}
		}
	}
	ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), ss.str().c_str(), glm::vec2( width * 0.675f, height * 0.05f ), 1.0f, glm::vec3( 1.0f ),
		RIGHT_ALIGNED, VERT_CENTERED );

	ServiceLocator::getGraphics().draw2DBox( glm::vec2( width * 0.75f, height * 0.025f ), glm::vec2( width * 0.2f, height * 0.05f ), glm::vec3( 0.0f ) );
	ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), optionsString.cstring(), glm::vec2( width * 0.85f, height * 0.05f ), 1.0f, glm::vec3( 1.0f ),
		HOR_CENTERED, VERT_CENTERED );
}

STATE HuntTheWumpus::update( GLfloat dt ) {
	if ( stateChanged ) {
		setOnClickFunctions();
	}

	if ( !gameOver && isWumpusTurn ) {
		if ( wumpus.update( rooms, &willy, textBox ) ) {
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_GAME_OVER;
		}
		isWumpusTurn = GL_FALSE;
	}


	if ( !gameOver ) {
		return GAME;
	} else {
		// unset listeners
		ServiceLocator::getInput().removeOnClickObserver( &textBox );
		ServiceLocator::getInput().removeOnScrollObserver( &textBox );
		for ( int i = 0; i < 5; ++i ) {
			ServiceLocator::getInput().removeOnClickObserver( &buttons[i] );
		}
		return MAIN_INIT;
	}
}

void HuntTheWumpus::setOnClickFunctions() {
	// programs what the buttons in the game should do
	switch ( buttonsState ) {
	case BUTTON_MAIN:
		optionsString = "Options:";

		// set button 0 to go to move menu
		buttons[0].setText( "Move Willy" );
		buttons[0].setVisible( GL_TRUE );
		buttons[0].setOnClickFunction( [&]() {
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_MOVE;
		} );
		// set button 1 to go to shoot arrow menu
		buttons[1].setText( "Shoot an arrow" );
		buttons[1].setVisible( GL_TRUE );
		buttons[1].setOnClickFunction( [&] () {
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_ARROW_PATH_INIT;
		} );

		// hide buttons 2 and 3
		buttons[2].setVisible( GL_FALSE );
		buttons[3].setVisible( GL_FALSE );
		break;
	case BUTTON_MOVE:
		optionsString = "Move to:";

		for ( int i = 0; i < 3; ++i ) {
			// set first 3 buttons to move to adjacent rooms
			std::stringstream ss;
			ss.str( std::string() );
			ss << "Room " << rooms[willy.currentRoom].nearbyRooms[i] + 1;
			buttons[i].setVisible( GL_TRUE );
			buttons[i].setText( ss.str() );
			buttons[i].setOnClickFunction( [=]() {
				stateChanged = GL_TRUE;
				// move player, returns true if dead
				if ( willy.move( rooms, rooms[willy.currentRoom].nearbyRooms[i], &wumpus, textBox ) ) {
					buttonsState = BUTTON_GAME_OVER;
				} else {
					buttonsState = BUTTON_MAIN;
					isWumpusTurn = GL_TRUE;
				}
			} ); 
		}

		// set fourth button to go back
		buttons[3].setVisible( GL_TRUE );
		buttons[3].setText( "Back" );
		buttons[3].setOnClickFunction( [=] () {
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_MAIN;
		} );
		break;
	case BUTTON_ARROW_PATH_INIT:
		optionsString = "Arrow Path:";

		// set first 3 buttons to pick a starting point for the arrow path
		for ( int i = 0; i < 3; ++i ) {
			// set first 3 buttons to move to adjacent rooms
			std::stringstream ss;
			ss.str( std::string() );
			ss << "Room " << rooms[willy.currentRoom].nearbyRooms[i] + 1;
			buttons[i].setVisible( GL_TRUE );
			buttons[i].setText( ss.str() );
			buttons[i].setOnClickFunction( [=] () {
				stateChanged = GL_TRUE;
				willy.setArrowPath( rooms[willy.currentRoom].nearbyRooms[i], GL_TRUE );
				buttonsState = BUTTON_ARROW_PATH;
			} );
		}

		// set fourth button to go back
		buttons[3].setVisible( GL_TRUE );
		buttons[3].setText( "Back" );
		buttons[3].setOnClickFunction( [=] () {
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_MAIN;
		} );
		break;
	case BUTTON_ARROW_PATH:
		optionsString = "Arrow Path:";

		if ( willy.numArrows > 0 ) {
			// set first 3 buttons to pick a path
			for ( int i = 0; i < 3; ++i ) {
				// set first 3 buttons to move to adjacent rooms
				std::stringstream ss;
				ss.str( std::string() );
				ss << "Room " << rooms[willy.arrowPath[willy.arrowPath.size() - 1]].nearbyRooms[i] + 1;
				buttons[i].setVisible( GL_TRUE );
				buttons[i].setText( ss.str() );
				buttons[i].setOnClickFunction( [=] () {
					stateChanged = GL_TRUE;
					willy.setArrowPath( rooms[willy.arrowPath[willy.arrowPath.size() - 1]].nearbyRooms[i] );
				} );
			}
		} else {
			for ( int i = 0; i < 3; ++i ) {
				buttons[i].setVisible( GL_FALSE );
			}
		}
		// set fourth button to shoot arrow
		buttons[3].setVisible( GL_TRUE );
		buttons[3].setText( "Fire Arrow" );
		buttons[3].setOnClickFunction( [=] () {
			stateChanged = GL_TRUE;
			if ( willy.shoot( rooms, &wumpus, textBox ) ) {
				buttonsState = BUTTON_GAME_OVER;
			} else {
				buttonsState = BUTTON_MAIN;
				isWumpusTurn = GL_TRUE;
			}
		} );
		break;
	case BUTTON_GAME_OVER:
		optionsString = "Game Over:";

		for ( int i = 0; i < 4; ++i ) {
			buttons[i].setVisible( GL_FALSE );
		}
		break;
	}
	stateChanged = GL_FALSE;
}