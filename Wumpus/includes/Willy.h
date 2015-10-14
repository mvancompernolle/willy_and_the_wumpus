#pragma once

#ifndef WILLY_H
#define	WILLY_H

#include <GL/glew.h>
#include "Room.h"
#include "Textbox.h"

class Willy {
public:
	GLboolean isAlive;
	GLuint currentRoom;
	GLuint numArrows;

	Willy();
	~Willy();
	void move( Room rooms[], GLuint selectedRoom, Textbox& textBox );
	void shoot( Room rooms[] );
private:
};

#endif // WILLY_H

