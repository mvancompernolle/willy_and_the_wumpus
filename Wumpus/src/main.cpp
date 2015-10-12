#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../includes/GLFWGraphics.h"
#include "../includes/GLFWInput.h"
#include "../includes/ResourceManager.h"
#include "../includes/Textbox.h"
#include "../includes/Button.h"

// input callbacks
void keyCallBack( GLFWwindow* window, GLint key, GLint scanCode, GLint action, GLint mode );
void cursorPosCallBack( GLFWwindow* window, GLdouble xPos, GLdouble yPos );
void mouseButtonCallBack( GLFWwindow* window, GLint button, GLint action, GLint mods );


Input* input;


int main() {
	// set resource paths
	ResourceManager::setShaderPath( "resources/shaders/" );
	ResourceManager::setTexturePath( "resources/textures/" );
	ResourceManager::setPath( "fonts", "resources/fonts/" );
	ResourceManager::setPath( "sounds", "resources/sounds/" );

	// initialize services
	input = new GLFWInput();
	GLFWGraphics* gr = new GLFWGraphics( "Willy and the Wumpus", 1920, 1080 );
	Graphics *graphics = gr;

	// load default font
	ResourceManager::loadFont( "FreeSans.ttf", "default", 36.0f );

	Textbox textBox( glm::vec2(20.0f), glm::vec2(1000.0f), 2, ResourceManager::getFont("default"), 36.0f);
	textBox.setBorderColor( glm::vec3( 1.0f, 0.0f, 0.0f ) );
	textBox.setTextColor( glm::vec3( 0.2, .5, 0.5 ) );
	textBox.addText( "Starting the Sentence: hello there I am a prickly pair and i really do not care." );
	textBox.addText( "hello there I am a prickly pair and i really do not care." );
	textBox.addText( "hello there I am a prickly pair and i really do not care." );
	textBox.addText( "hello there I am a prickly pair and i really do not care." );
	textBox.addNewLine();

	Textbox textBox2( glm::vec2( 1200.0f, 100.0f ), glm::vec2( 315.0f ), 2, ResourceManager::getFont( "default" ), 36.0f );
	textBox2.addText( "hi" );

	Button btn( glm::vec2( 1200, 500 ), glm::vec2( 300, 100 ) );
	btn.setText( "Im a button" );
	std::string letter = "Omg life is so crazy...";
	btn.setOnClickFunction( [&] () {
		textBox.addText( letter );
		textBox2.addText(letter);
	} );
	input->addOnClickObserver( &btn );

	// initialize mouse and keyboard
	glfwSetInputMode( gr->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	glfwSetCursorPosCallback( gr->getWindow(), cursorPosCallBack );
	glfwSetMouseButtonCallback( gr->getWindow(), mouseButtonCallBack );
	glfwSetKeyCallback( gr->getWindow(), keyCallBack );

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

		// process input
		//game->processInput(dt);

		// update game state
		//game->update(dt);

		// render the game
		glClear( GL_COLOR_BUFFER_BIT );

		//game->render();
		//graphics->renderText( "OCRAEXT.TTF", "hello there", glm::vec2( 100, 100 ), 2.0f, glm::vec3( 1.0f ) );
		//graphics->draw2DBox( glm::vec2( 100.0f ), glm::vec2( 200.0f ), glm::vec3(1.0f) );
		textBox.render( *graphics );
		textBox2.render( *graphics );
		btn.render( *graphics );
		//graphics->renderText( ResourceManager::getFont( "default" )
			//ResourceManager::loadFont( "OCRAEXT.TTF", "blah", 24 ), "Matthew VanCompernolle", glm::vec2( 900, 0 ), 1.0f, glm::vec3( 0.0, 1.0, 0.0 ), CENTERED );

		graphics->swapBuffers();
	}

	delete graphics;
	delete input;

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
	if ( action == GLFW_PRESS ) {
		input->setKeyPressed( button );
	} else {
		input->setKeyReleased( button );
	}
}