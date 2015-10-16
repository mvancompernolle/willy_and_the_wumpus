#pragma once

#ifndef WUMPUS_H
#define	WUMPUS_H

#include <GL/glew.h>
#include <cstdlib>
#include "Room.h"
#include "Textbox.h"

class Willy;

class Wumpus {
public:
	GLuint			currentRoom;
	GLboolean		isAwake;

					Wumpus();
					~Wumpus();
	GLboolean		update( Room rooms[], const Willy* willy, Textbox textBox );
};

#endif // WUMPUS_H