#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../includes/GLFWGraphics.h"
#include "../includes/GLFWInput.h"
#include "../includes/ResourceManager.h"
#include "../includes/ServiceLocator.h"
#include "../includes/irrKlangAudio.h"
#include "../includes/HuntTheWumpus.h"

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

	// initialize services
	input = new GLFWInput();
	GLFWGraphics* gr = new GLFWGraphics( "Willy and the Wumpus", 1800, 980 );
	Graphics *graphics = gr;
	Audio* audio = new irrKlangAudio();

	ServiceLocator::provideGraphics( graphics );
	ServiceLocator::provideInput( input );
	ServiceLocator::provideAudio( audio );

	// load default font
	ResourceManager::loadFont( "times_new_roman.ttf", "default", 36.0f );

	// initialize mouse and keyboard
	glfwSetInputMode( gr->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	glfwSetCursorPosCallback( gr->getWindow(), cursorPosCallBack );
	glfwSetMouseButtonCallback( gr->getWindow(), mouseButtonCallBack );
	glfwSetScrollCallback( gr->getWindow(), scrollCallBack );
	glfwSetKeyCallback( gr->getWindow(), keyCallBack );

	// create game
	HuntTheWumpus* game = new HuntTheWumpus( gr->getDimensions().x, gr->getDimensions().y );

	// start the game loop
	GLfloat dt = 0.0f, lastTime = 0.0f;
	while ( graphics->windowIsValid() ) {
		// calculate dt
		GLfloat currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;
		glfwPollEvents();

		// keep dt small
		if ( dt > 0.0333f ) {
			dt = 0.0333f;
		}

		game->update( dt );

		// render the game
		glClear( GL_COLOR_BUFFER_BIT );

		game->render( dt );

		graphics->swapBuffers();
	}

	delete graphics;
	delete input;
	delete audio;

	system( "pause" );

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