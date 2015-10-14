#pragma once

#ifndef HUNT_THE_WUMPUS_H
#define HUNT_THE_WUMPUS_H

#include <GL/glew.h>
#include "Textbox.h"
#include "Button.h"
#include "Room.h"
#include "Willy.h"
#include "ServiceLocator.h"

class HuntTheWumpus {
public:
	HuntTheWumpus( GLuint width, GLuint height );
	~HuntTheWumpus();
	void render( GLfloat dt );
	void update( GLfloat dt );
private:
	const GLint NUM_ROOMS = 20;
	Room rooms[20];
	Willy willy;
	Textbox textBox;
	Button	buttons[5];
	GLuint wumpusLocation;
	GLboolean wumpusAwake;
	GLuint width, height;

	void moveWumpus( Room room );

};

#endif HUNT_THE_WUMPUS_H