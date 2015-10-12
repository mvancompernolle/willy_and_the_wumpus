#pragma once

#ifndef GLFWGRAPHICS_H
#define GLFWGRAPHICS_H

#include "Graphics.h"
#include <GLFW/glfw3.h>
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "BoxRenderer.h"
#include "string.h"

class GLFWGraphics : public Graphics {
public:
						GLFWGraphics( sfw::string windowName ); // fullscreen constructor
						GLFWGraphics( sfw::string windowName, GLuint width, GLuint height ); // set dimensions constructor
						~GLFWGraphics();
	virtual void		setBackgroundColor( glm::vec3 color );
	virtual void		renderText( const font& characters, sfw::string text, glm::vec2 pos, GLfloat scale, glm::vec3 color = glm::vec3( 1.0f ), TEXT_ALIGNMENT alignment = LEFT_ALIGNED );
	virtual void		draw2DTexture( const Texture& texture, glm::vec2 pos, glm::vec2 size, GLfloat rot, glm::vec4 color = glm::vec4( 1.0f ), GLboolean flipH = GL_FALSE );
	virtual void		draw2DBox( glm::vec2 pos, glm::vec2 size, glm::vec3 color, GLfloat rot = 0.0f );
	virtual GLboolean	windowIsValid() const;
	virtual void		swapBuffers();
	GLFWwindow*			getWindow() const;
private:
	GLFWwindow			*window;
	SpriteRenderer		*spriteRenderer;
	TextRenderer		*textRenderer;
	BoxRenderer			*boxRenderer;

	void				init();
};

#endif //GLFWGRAPHICS_H