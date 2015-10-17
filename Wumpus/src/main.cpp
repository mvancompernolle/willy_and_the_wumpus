#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include "../includes/GLFWGraphics.h"
#include "../includes/GLFWInput.h"
#include "../includes/ResourceManager.h"
#include "../includes/ServiceLocator.h"
#include "../includes/irrKlangAudio.h"
#include "../includes/HuntTheWumpus.h"
#include "../includes/MainMenu.h"
#include "../includes/Splash.h"
#include "../includes/Rules.h"
#include "../includes/consts.h"

// input callbacks
void keyCallBack( GLFWwindow* window, GLint key, GLint scanCode, GLint action, GLint mode );
void cursorPosCallBack( GLFWwindow* window, GLdouble xPos, GLdouble yPos );
void mouseButtonCallBack( GLFWwindow* window, GLint button, GLint action, GLint mods );
void scrollCallBack( GLFWwindow* window, GLdouble xOffset, GLdouble yOffset );

Input* input;

int main() {
	// set resource paths
	ResourceManager::setShaderPath( "resources/shaders/" );
	ResourceManager::setTexturePath( "resources/textures/" );
	ResourceManager::setPath( "fonts", "resources/fonts/" );
	ResourceManager::setPath( "sounds", "resources/sounds/" );
	ResourceManager::setPath( "text", "resources/text/" );

	// initialize services
	input = new GLFWInput();
	GLFWGraphics* gr = new GLFWGraphics( "Willy and the Wumpus" );
	Graphics *graphics = gr;
	Audio* audio = new irrKlangAudio();

	ServiceLocator::provideGraphics( graphics );
	ServiceLocator::provideInput( input );
	ServiceLocator::provideAudio( audio );

	// load default font
	ResourceManager::loadFont( "FreeSans.ttf", "default", 36.0f );

	// initialize mouse and keyboard
	glfwSetInputMode( gr->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	glfwSetCursorPosCallback( gr->getWindow(), cursorPosCallBack );
	glfwSetMouseButtonCallback( gr->getWindow(), mouseButtonCallBack );
	glfwSetScrollCallback( gr->getWindow(), scrollCallBack );
	glfwSetKeyCallback( gr->getWindow(), keyCallBack );

	// create game
	STATE current = SPLASH;
	HuntTheWumpus* game = new HuntTheWumpus( gr->getDimensions().x, gr->getDimensions().y );
	MainMenu menu( gr->getDimensions().x, gr->getDimensions().y );
	Splash splash( gr->getDimensions().x, gr->getDimensions().y );
	Rules rules( gr->getDimensions().x, gr->getDimensions().y );

	// start the game loop
	GLfloat dt = 0.0f, lastTime = 0.0f;
	GLboolean running = GL_TRUE;
	while ( graphics->windowIsValid() && running ) {
		// calculate dt
		GLfloat currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();

		// keep dt small
		if ( dt > 0.0333f ) {
			dt = 0.0333f;
		}

		// render the game
		glClear( GL_COLOR_BUFFER_BIT );

		switch ( current ) {
		case SPLASH:
			current = splash.update( dt );
			splash.render();
			break;

		case MAIN_INIT:
			menu.init();
		case MAIN:
			current = menu.getMenuState();
			menu.render( dt );
			if ( current == RULES_INIT ) {
				rules.setPrevState( MAIN_INIT );
			}
			break;

		case RULES_INIT:
			rules.init();
		case RULES:
			current = rules.update();
			rules.render();
			// if continuing game, resync game input
			if ( current == GAME ) {
				game->syncInput();
			}
			break;

		case PLAY:
			game->init();
		case GAME:
			current = game->update( dt );
			game->render( dt );
			if ( current == RULES_INIT ) {
				rules.setPrevState( GAME );
			}
			break;

		case EXIT:
			// show simple credits then exit
			ServiceLocator::getGraphics().renderText( ResourceManager::getFont( "default" ), "Thank you for playing!", glm::vec2( gr->getDimensions().x, gr->getDimensions().y ) / 2.0f,
				3.0f, glm::vec3( 1.0f ), HOR_CENTERED, VERT_CENTERED );
			graphics->swapBuffers();
			Sleep(3000);
			running = GL_FALSE;
			break;
		}

		graphics->swapBuffers();
	}

	//delete graphics;
	delete input;
	delete graphics;
	delete audio;
	delete game;

	return 0;
}

void keyCallBack( GLFWwindow* window, GLint key, GLint scanCode, GLint action, GLint mode ) {
	if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS ) {
		glfwSetWindowShouldClose( window, GL_TRUE );
	}
	if ( key >= 0 && key < 1024 ) {
		if ( action == GLFW_PRESS ) {
			input->setKeyPressed( key );
		} else if ( action == GLFW_RELEASE ) {
			input->setKeyReleased( key );
		}
	}
}

void cursorPosCallBack( GLFWwindow* window, GLdouble xPos, GLdouble yPos ) {
	input->setMousePos( xPos, yPos );
}

void mouseButtonCallBack( GLFWwindow* window, GLint button, GLint action, GLint mods ) {
	if ( action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1 ) {
		input->setMouseButtonClicked( button );
	} else if ( action == GLFW_PRESS ) {
		input->setKeyPressed( button );
	} else {
		input->setKeyReleased( button );
	}
}

void scrollCallBack( GLFWwindow* window, GLdouble xOffset, GLdouble yOffset ) {
	input->scrollOffset( xOffset, yOffset );
}