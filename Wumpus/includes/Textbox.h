#pragma once

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "TextChar.h"

class Graphics;

struct StringToken{
	std::string str;
	GLfloat xPos;
	GLuint lineNum;
	StringToken( std::string s, GLfloat x, GLuint line ) {
		str = s;
		xPos = x;
		lineNum = line;
	}
};

class Textbox {
public:
								Textbox( glm::vec2 pos, glm::vec2 size, GLfloat borderSize, const font& fontType, GLuint fontSize = 24 );
								~Textbox();
	void						addText( std::string newText );
	void						addNewLine();
	void						setPadding( GLfloat horizontal, GLfloat vertical );
	void						setTextColor( glm::vec3 color );
	void						setLineSpacing( GLfloat spacing );
	void						setBorderColor( glm::vec3 color );
	void						setBackgroundColor( glm::vec3 color );
	void						render( Graphics& graphics );
private:
	glm::vec2					size;
	glm::vec2					pos;
	std::vector<StringToken>	tokens;
	font						fontType;
	GLfloat						paddingHorizontal, paddingVertical;
	GLfloat						borderSize, fontSize, lineSpacing;
	glm::vec3					textColor, borderColor, backgroundColor;
	GLfloat						currHorizontalOffset;
	GLuint						currentLineNumber, firstLineInView;

	GLfloat						getStringWidth( const std::string& str ) const;
	GLuint						getNumLinesThatFit() const;
	GLuint						getFirstTokenOnLine( GLuint line );
};

#endif // TEXTBOX_H