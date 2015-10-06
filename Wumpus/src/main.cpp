#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint SCREEN_WIDTH = 1920;
GLuint SCREEN_HEIGHT = 1080;
const GLboolean FULL_SCREEN = GL_FALSE;

int main() {
	// init glfw
	GLFWwindow* window = nullptr;
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

	if ( FULL_SCREEN ) {
		GLFWvidmode* mode = (GLFWvidmode*)glfwGetVideoMode( glfwGetPrimaryMonitor() );
		glfwWindowHint( GLFW_RED_BITS, mode->redBits );
		glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
		glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
		glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );

		SCREEN_WIDTH = mode->width;
		SCREEN_HEIGHT = mode->height;
		window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Willy and the Wumpus", glfwGetPrimaryMonitor(), nullptr );
	} else {
		window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Willy and the Wumpus", nullptr, nullptr );
	}
	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 );

	// initialize glew
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	// set desired resolution for the gamek
	GLuint virtualWidth = 1920;
	GLuint virtualHeight = 1080;
	GLfloat targetAspectRatio = virtualWidth / virtualHeight;

	GLuint width = SCREEN_WIDTH;
	GLuint height = (int)( width * targetAspectRatio + 0.5f );
	if ( height > SCREEN_HEIGHT ) {
		height = SCREEN_HEIGHT;
		width = (int)( height * targetAspectRatio + 0.5f );
	}
	glViewport( ( SCREEN_WIDTH / 2.0f ), ( SCREEN_HEIGHT / 2.0f ), width, height );
	glClear( GL_COLOR_BUFFER_BIT );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	// set input callback function

	// start the game loop
	GLfloat dt = 0.0f, lastTime = 0.0f;
	while ( !glfwWindowShouldClose( window ) ) {
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
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		//game->render();

		glfwSwapBuffers( window );
	}

	glfwDestroyWindow( window );
	glfwTerminate();

	system( "pause" );

	return 0;
}