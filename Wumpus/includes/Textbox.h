#pragma once

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "TextChar.h"
#include "Button.h"
#include "../includes/ScrollObserver.h"


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

class Textbox : public OnClickObserver, public ScrollObserver {
public:
								Textbox( glm::vec2 pos, glm::vec2 size, GLuint borderSize, const font& fontType, GLfloat fontScale = 1.0f );
								~Textbox();
	void						addText( std::string newText, GLboolean newLine = GL_FALSE );
	void						addNewLine();
	void						setPadding( GLfloat horizontal, GLfloat vertical );
	void						setTextColor( glm::vec3 color );
	void						setLineSpacing( GLfloat spacing );
	void						setBorderColor( glm::vec3 color );
	void						setBackgroundColor( glm::vec3 color );
	void						render( Graphics& graphics );
	virtual	void				onClick( glm::vec2 pos );
	virtual void				onRelease( glm::vec2 pos );
	virtual void				onMouseMovement( glm::vec2 pos );
	virtual void				onHorizontalScroll( GLfloat offset, glm::vec2 pos );
	virtual void				onVerticalScroll( GLfloat offset, glm::vec2 pos );
private:
	glm::vec2					size;
	glm::vec2					pos, btnSize;
	std::vector<StringToken>	tokens;
	font						fontType;
	GLfloat						paddingHorizontal, paddingVertical;
	GLuint						borderSize;
	GLfloat						fontScale, lineSpacing;
	glm::vec3					textColor, borderColor, backgroundColor;
	GLfloat						currHorizontalOffset;
	GLint						currentLineNumber, firstLineInView;
	Button						bScrollUp, bScrollDown, bScrollBar;
	glm::vec2					currentMousePos;
	GLfloat						mouseClickOffset;

	GLfloat						getStringWidth( const std::string& str ) const;
	GLint						getNumLinesThatFit() const;
	GLuint						getFirstTokenOnLine( GLuint line );
	void						updateScrollBar();
	void						dragScrollBar();
	GLboolean					isOverView( glm::vec2 pos ) const;
};

#endif // TEXTBOX_H