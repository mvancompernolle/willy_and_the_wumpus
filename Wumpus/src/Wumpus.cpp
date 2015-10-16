#include "../includes/Wumpus.h"
#include "../includes/Willy.h"


Wumpus::Wumpus()
	: currentRoom(0), isAwake(GL_FALSE)
{
}


Wumpus::~Wumpus()
{
}

GLboolean Wumpus::update( Room rooms[], const Willy* willy, Textbox textBox ) {
	// potentially move the wumpus if it is awake
	if ( isAwake ) {
		int random = rand() % 4;
		if ( random < 3 ) {
			currentRoom = rooms[currentRoom].nearbyRooms[random];

			if ( currentRoom == willy->currentRoom ) {
				textBox.addText( "The Wumpus ran into your room and ate you! You lose!", COLOR_NEGATIVE, GL_TRUE );
				return GL_TRUE;
			} else if ( willy->canSmellWumpus( rooms, this, willy->currentRoom, -1, 0 ) ) {
				textBox.addText( "The Wumpus must be moving. A horrible stench has started to come from a nearby room...", COLOR_INFO, GL_TRUE );
			}
		}
	}
	return GL_FALSE;
}
