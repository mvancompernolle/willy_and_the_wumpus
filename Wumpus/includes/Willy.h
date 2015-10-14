#pragma once

#ifndef WILLY_H
#define	WILLY_H

#include <GL/glew.h>
#include "Room.h"
#include "Button.h"

class Willy {
public:
	GLboolean isAlive;
	GLuint currentRoom;
	GLuint numArrows;

	Willy();
	~Willy();
	void move( Room rooms[], Button buttons[], GLuint selectedRoom );
	void shoot( Room rooms[], Button buttons[] );
private:
};

#endif // WILLY_H

