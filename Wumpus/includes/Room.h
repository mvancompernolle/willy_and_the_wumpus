#pragma once

#ifndef ROOM_H
#define ROOM_H

#include <GL/glew.h>
#include <initializer_list>

struct Room {
	GLuint nearbyRooms[3];
	GLboolean hasBat;
	GLboolean hasHole;

	Room( const std::initializer_list<GLuint>& rooms ) : hasBat( GL_FALSE ), hasHole( GL_FALSE ) {
		int i = 0;
		for ( auto room : rooms ) {
			nearbyRooms[i] = room;
			++i;
		}
	}
};

#endif // ROOM_H