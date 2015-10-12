#pragma once

// Reference: http://www.learnopengl.com/#!In-Practice/2D-Game/Render-text

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"
#include "string.h"
#include "TextChar.h"
#include "TextAlignment.h"

class TextRenderer {
public:
	Shader						shader;

								TextRenderer( GLuint width, GLuint height );
								~TextRenderer();
	void						renderText( const font& characters, sfw::string text, glm::vec2 pos, GLfloat scale, glm::vec3 color = glm::vec3( 1.0f ), TEXT_ALIGNMENT alignment = LEFT_ALIGNED );
private:
	GLuint						VAO, VBO;
};

#endif TEXT_RENDERER_H
