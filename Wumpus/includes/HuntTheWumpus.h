#pragma once

#ifndef HUNT_THE_WUMPUS_H
#define HUNT_THE_WUMPUS_H

#include <GL/glew.h>
#include "Textbox.h"
#include "Button.h"
#include "Room.h"
#include "Willy.h"
#include "Wumpus.h"
#include "ServiceLocator.h"
#include "Consts.h"
#include "string.h"

enum BUTTON_STATE {
	BUTTON_MAIN,
	BUTTON_MOVE,
	BUTTON_ARROW_PATH_INIT,
	BUTTON_ARROW_PATH,
	BUTTON_GAME_OVER
};

class HuntTheWumpus {
public:
						HuntTheWumpus( GLuint width, GLuint height );
						~HuntTheWumpus();
	void				render( GLfloat dt );
	STATE				update( GLfloat dt );
	void				init();
private:
	const GLint			NUM_ROOMS = 20;
	Room				rooms[20];
	Willy				willy;
	Wumpus				wumpus;
	Textbox				textBox;
	Button				buttons[5];
	GLuint				wumpusLocation;
	GLboolean			wumpusAwake;
	GLuint				width, height;
	GLboolean			stateChanged, isWumpusTurn;
	GLboolean			gameOver;
	BUTTON_STATE		buttonsState;
	sfw::string			optionsString;

	void				setOnClickFunctions();
};

#endif HUNT_THE_WUMPUS_H