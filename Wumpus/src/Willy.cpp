#include "../includes/Willy.h"
#include <iostream>
#include <sstream>
#include "../includes/Wumpus.h"
#include "../includes/ServiceLocator.h"
#include "../includes/ResourceManager.h"

Willy::Willy() : numArrows(5){
}


Willy::~Willy() {
}

GLboolean Willy::move( Room rooms[], GLuint selectedRoom, Wumpus* wumpus, Textbox& textBox ) {
	// set willy's current room
	currentRoom = selectedRoom;

	std::stringstream ss;
	ss << "You moved into room " << selectedRoom + 1 << "!";
	ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "willy_move.wav", GL_FALSE );
	textBox.addText(ss.str(), COLOR_ACTION, GL_TRUE);
	ss.str( std::string() );

	// warn the player if there is a pit nearby
	if ( rooms[rooms[currentRoom].nearbyRooms[0]].hasHole
		|| rooms[rooms[currentRoom].nearbyRooms[1]].hasHole
		|| rooms[rooms[currentRoom].nearbyRooms[2]].hasHole ) {
		textBox.addText( "You feel a breeze coming from a nearby room...", COLOR_INFO, GL_TRUE );
	}
	// warn the player if there is a bat nearby
	if ( rooms[rooms[currentRoom].nearbyRooms[0]].hasBat
		|| rooms[rooms[currentRoom].nearbyRooms[1]].hasBat
		|| rooms[rooms[currentRoom].nearbyRooms[2]].hasBat ) {
		textBox.addText( "You hear a super bat shriek in a nearby room...", COLOR_INFO, GL_TRUE );
	}
	// warn player if wumpus is nearby 
	if ( canSmellWumpus( rooms, wumpus, currentRoom, -1, 0 ) && currentRoom != wumpus->currentRoom ) {
		textBox.addText( "You can smell a Wumpus somewhere nearby...", COLOR_INFO, GL_TRUE );
	}

	// check to see if something happened to willy
	if ( currentRoom == wumpus->currentRoom ) {
		// you died
		textBox.addText( "You were smashed, cooked, eaten, and excremented by the Wumpus! That means you died...", COLOR_NEGATIVE, GL_TRUE );
		ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "dying.wav", GL_FALSE );
		return GL_TRUE;
	} else if ( rooms[currentRoom].hasBat ) {
		// bat carried you to random room
		textBox.addText( "You were carried by a super bat...", COLOR_NEGATIVE, GL_TRUE );
		move( rooms, rand() % 20, wumpus, textBox );
	} else if ( rooms[currentRoom].hasHole ) {
		// you died
		textBox.addText( "You fell down a hole and you aren't a bird! You dead...", COLOR_NEGATIVE, GL_TRUE );
		ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "pit.wav", GL_FALSE );
		return GL_TRUE;
	}
	// return false if did not die when moving
	return GL_FALSE;
}

GLboolean Willy::shoot( Room rooms[], Wumpus* wumpus, Textbox& textBox ) {
	textBox.addText( "You fire an arrow!", COLOR_ACTION, GL_TRUE );
	ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "arrow_shot.wav", GL_FALSE );
	GLboolean batHit = GL_FALSE;

	// shoot the arrow according to the selected path
	for ( int i = 0; i < arrowPath.size(); ++i ) {

		std::stringstream ss;
		ss << "The arrow zips into room " << arrowPath[i] + 1 << ".";
		textBox.addText( ss.str(), COLOR_INFO, GL_TRUE );

		// check to see if the arrow hit the wumpus
		if ( arrowPath[i] == wumpus->currentRoom ) {
			textBox.addText( "You shot the Wumpus! You win... murderer...", COLOR_POSITIVE, GL_TRUE );
			ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "dead_wumpus.mp3", GL_FALSE );
			return GL_TRUE;
		} else if ( arrowPath[i] == currentRoom ) {
			textBox.addText( "You shot yourself somehow even though I gave you full control over the arrow's path... you lose!", COLOR_NEGATIVE, GL_TRUE );
			ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "dying.wav", GL_FALSE );
			return GL_TRUE;
		} else if ( rooms[arrowPath[i]].hasBat ) {
			rooms[arrowPath[i]].hasBat = GL_FALSE;
			textBox.addText( "You shot a super bat! Its dead body stinks up the cave even more...", COLOR_POSITIVE, GL_TRUE );
			ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "dead_bat.wav", GL_FALSE );
		}
	}

	if ( !batHit ) {
		textBox.addText( "The arrow drops to the ground and breaks.", COLOR_INFO, GL_TRUE );
		//ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "arrow_landed.wav", GL_FALSE );
	}

	if ( !wumpus->isAwake ) {
		wumpus->isAwake = GL_TRUE;
		textBox.addText( "The Wumpus heard your arrow break and is now awake!!!", COLOR_INFO, GL_TRUE );
		ServiceLocator::getAudio().playSound( ResourceManager::getPath( "sounds" ) + "wumpus_awake.wav", GL_FALSE );
	}

	if ( numArrows <= 0 ) {
		textBox.addText( "You ran out of arrows and can't possibly kill the Wumpus now! Game Over!", COLOR_NEGATIVE, GL_TRUE );
		return GL_TRUE;
	}
	return GL_FALSE;
}

void Willy::setArrowPath( GLuint roomNum, GLboolean resetPath ) {
	if ( resetPath ) {
		arrowPath.clear();
	}
	arrowPath.push_back( roomNum );
	numArrows--;
}

GLboolean Willy::canSmellWumpus( Room rooms[], const Wumpus* wumpus, GLuint room, GLuint prevRoom, GLuint roomsAway ) const {
	if ( roomsAway == 3 ) {
		return GL_FALSE;
	} else if ( room == wumpus->currentRoom ) {
		return GL_TRUE;
	} else {
		GLboolean found = GL_FALSE;
		for ( int i = 0; i < 3; ++i ) {
			if ( rooms[currentRoom].nearbyRooms[i] != prevRoom ) {
				found |= canSmellWumpus( rooms, wumpus, rooms[room].nearbyRooms[i], room, roomsAway + 1 );
			}
		}
		return found;
	}
}
