#pragma once

#ifndef WILLY_H
#define	WILLY_H

#include <GL/glew.h>
#include <vector>
#include "Room.h"
#include "Textbox.h"
#include "Consts.h"

class Wumpus;

class Willy {
public:
	GLuint				currentRoom;
	GLuint				numArrows;
	std::vector<GLuint> arrowPath;

						Willy();
						~Willy();
	GLboolean			move( Room rooms[], GLuint selectedRoom, Wumpus* wumpus, Textbox& textBox );
	GLboolean			shoot( Room rooms[], Wumpus* wumpus, Textbox& textBox );
	void				setArrowPath( GLuint roomNum, GLboolean resetPath = GL_FALSE );
	GLboolean			canSmellWumpus( Room rooms[], const Wumpus* wumpus, GLuint room, GLuint prevRoom, GLuint roomsAway ) const;

private:
};

#endif // WILLY_H

