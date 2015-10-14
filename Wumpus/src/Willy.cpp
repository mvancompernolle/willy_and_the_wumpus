#include "../includes/Willy.h"
#include <iostream>
#include <sstream>

Willy::Willy() : isAlive(GL_TRUE), numArrows(5){
}


Willy::~Willy() {
}

void Willy::move( Room rooms[], GLuint selectedRoom, Textbox& textBox ) {
	// set willy's current room
	currentRoom = selectedRoom;

	std::stringstream ss;
	ss << "You moved into room " << selectedRoom << "!";
	textBox.addText(ss.str(), GL_TRUE);
	ss.str( std::string() );

	// check to see if something happened to willy
	if ( rooms[currentRoom].hasWumpus ) {
		// you died
		isAlive = GL_FALSE;
		ss << "You were smashed, cooked, eaten, and excremented by the Wumpus! That means you died...";
		textBox.addText( ss.str(), GL_TRUE );
	} else if ( rooms[currentRoom].hasBat ) {
		// bat carried you to random room
		ss << "You were carried by a really big bat...";
		textBox.addText( ss.str(), GL_TRUE );
		move( rooms, rand() % 20, textBox );
	} else if ( rooms[currentRoom].hasHole ) {
		// you died
		isAlive = GL_FALSE;
		ss << "You fell down a hole and you aren't a bird! You dead...";
		textBox.addText( ss.str(), GL_TRUE );
	}
}

void Willy::shoot( Room rooms[] ) {

}