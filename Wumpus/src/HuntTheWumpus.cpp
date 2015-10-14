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
	buttonsState( BUTTON_MAIN )
{
	// initialize text box
	textBox.setPadding( 24.0f, 24.0f );
	textBox.setBorderColor( glm::vec3( 0.2f, 0.4f, 0.8f ) );

	// initialize buttons
	GLfloat spaceBetween = 0.05f * height;
	GLfloat buttonYSize = ( ( 0.8f * height - 4 * spaceBetween ) / 5.0f );
	for ( int i = 0; i < 5; ++i ) {
		buttons[i].setSize( glm::vec2( width * 0.2f, buttonYSize ) );
		buttons[i].setPos( glm::vec2( width * 0.75f, ( 0.1f * height + buttonYSize * i + spaceBetween * i ) ) );
	}

	buttons[4].setText( "Quit" );
	buttons[4].setOnClickFunction( [&]() {
		willy.isAlive = GL_FALSE;
	} );

	// init random
	srand( time( NULL ) );
}

HuntTheWumpus::~HuntTheWumpus() {
}

void HuntTheWumpus::init() {
	// init textbox
	textBox.clear();
	textBox.addText( "Welcome to Willy and the Wumpus!", GL_TRUE );
	textBox.addText( "-------------------------------------------------------------------", GL_TRUE );
	textBox.addText( "It plays just like regular Hunt the Wumpus, but your name is Willy!", GL_TRUE );
	ServiceLocator::getInput().addOnClickObserver( &textBox );
	ServiceLocator::getInput().addOnScrollObserver( &textBox );

	// set listeners for buttons
	for ( int i = 0; i < 5; ++i ) {
		ServiceLocator::getInput().addOnClickObserver( &buttons[i] );
	}

	// initialize rooms
	willy = Willy();
	for ( int i = 0; i < 20; ++i ) {
		rooms[i].hasBat = rooms[i].hasHole = rooms[i].hasWumpus = GL_FALSE;
	}

	// randomly choose where 2 bats are, 2 holes are, and the wumpus is
	int room = rand() % 20;
	rooms[room].hasWumpus = GL_TRUE;
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
	room = rand() % 20;
	while ( rooms[room].hasBat || rooms[room].hasWumpus || rooms[room].hasHole ) {
		room = rand() % 20;
	}
	willy.currentRoom = room;
}

void HuntTheWumpus::render( GLfloat dt ) {
	// render textBox
	textBox.render( ServiceLocator::getGraphics() );

	// render buttons
	for ( int i = 0; i < 5; ++i ) {
		buttons[i].render( ServiceLocator::getGraphics() );
	}
}

STATE HuntTheWumpus::update( GLfloat dt ) {
	if ( stateChanged ) {
		setOnClickFunctions();
	}

	if ( willy.isAlive && willy.numArrows > 0 ) {
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

void HuntTheWumpus::moveWumpus( Room room ) {

}

void HuntTheWumpus::setOnClickFunctions() {
	switch ( buttonsState ) {
	case BUTTON_MAIN:
		// set button 0 to go to move menu
		buttons[0].setText( "Move Willy" );
		buttons[0].setOnClickFunction( [&]() {
			// set fourth button to go back
			buttons[3].isVisible = GL_TRUE;
			buttons[3].setText( "Back" );
			buttons[3].setOnClickFunction( [&]() {
				buttons[0].setText( "Move Willy" );
				buttons[1].setText( "Shoot an arrow" );
				buttons[2].isVisible = GL_FALSE;
				buttons[3].isVisible = GL_FALSE;
				stateChanged = GL_TRUE;
				buttonsState = BUTTON_MAIN;
			} );

			// setup buttons to move to adjacent rooms
			std::stringstream ss;
			for ( int i = 2; i >= 0; --i ) {
				// set first 3 buttons to move to adjacent rooms
				ss.str( std::string() );
				ss << "Room " << rooms[willy.currentRoom].nearbyRooms[i];
				buttons[i].isVisible = GL_TRUE;
				buttons[i].setText( ss.str() );
				stateChanged = GL_TRUE;
				buttonsState = BUTTON_MOVE;
			}
		} );
		// set button 1 to go to shoot arrow menu
		buttons[1].setText( "Shoot an arrow" );
		buttons[1].setOnClickFunction( [&]() {
			for ( int i = 0; i < 3; ++i ) {
				// when clicked, set first 3 buttons to move to adjacent rooms
				std::stringstream ss;
				ss.str( std::string() );
				ss << "Room " << rooms[willy.currentRoom].nearbyRooms[i];
				buttons[i].isVisible = GL_TRUE;
				buttons[i].setText( ss.str() );
				stateChanged = GL_TRUE;
				buttonsState = BUTTON_SHOOT;
			}
		} );
		// hide buttons 2 and 3
		buttons[2].isVisible = GL_FALSE;
		buttons[3].isVisible = GL_FALSE;
		break;
	case BUTTON_MOVE:
		for ( int i = 0; i < 3; ++i ) {
			// when clicked, set first 3 buttons to move to a new set of adjacent rooms
			buttons[i].setOnClickFunction( [&]() {
				willy.move( rooms, rooms[willy.currentRoom].nearbyRooms[i], textBox );
			} ); 
			for ( int j = 0; j < 3; ++j ) {
				std::stringstream ss;
				ss.str( std::string() );
				ss << "Room " << rooms[willy.currentRoom].nearbyRooms[j];
				buttons[j].setText( ss.str() );
			}
			stateChanged = GL_TRUE;
			buttonsState = BUTTON_MOVE;
		}
		break;
	case BUTTON_SHOOT:
		break;
	}
}