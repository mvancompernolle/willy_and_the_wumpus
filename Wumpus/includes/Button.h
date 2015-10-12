#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "OnClickObserver.h"
#include "Graphics.h"
#include <functional>
#include <string>
#include "TextChar.h"

enum ButtonState {
	PRESSED,
	RELEASED, 
	HOVER
};

class Button : public OnClickObserver {
public:
							Button( glm::vec2 pos, glm::vec2 size );
							~Button();
	virtual void			onClick( glm::vec2 pos );
	virtual void			onRelease( glm::vec2 pos );
	virtual void			onMouseMovement( glm::vec2 pos );
	void					setTextures( Texture pressed, Texture released );
	void					setTextColor( glm::vec3 color );
	void					setText( std::string s );
	void					render( Graphics& graphics );
	void					setOnClickFunction( std::function<void()> fcn );
	void					setOnReleaseFunction( std::function<void()> fcn );
private:
	ButtonState				state;
	std::string				text;
	font					fontType;
	GLfloat					fontScale;
	glm::vec3				textColor;
	glm::vec2				pos, size;
	Texture					releasedTexture, pressedTexture, hoverTexture;

	std::function<void()>	onClickFunction;
	std::function<void()>	onReleaseFunction;

	GLboolean				isOverButton( glm::vec2 pos ) const;
};

#endif // BUTTON_H