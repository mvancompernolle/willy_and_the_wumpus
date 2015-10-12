#include "../includes/Button.h"
#include "../includes/ResourceManager.h"
#include <iostream>


Button::Button( glm::vec2 pos, glm::vec2 size )
	: pos(pos), size(size), text(""), fontScale(1.0f), textColor(glm::vec3(0.0f, 0.0f, 1.0f)), state(RELEASED)
{
	pressedTexture = ResourceManager::loadTexture( "button_pressed.png", GL_TRUE, "btn_pressed_default" );
	releasedTexture = ResourceManager::loadTexture( "button_released.png", GL_TRUE, "btn_released_default" );
	hoverTexture = ResourceManager::loadTexture( "button_hover.png", GL_TRUE, "btn_hover_default" );
	fontType = ResourceManager::getFont( "default" );
}

Button::~Button()
{
}

void Button::onClick( glm::vec2 pos ) {
	// check to see if button was click
	if ( isOverButton(pos) ) {
		state = PRESSED;

		if ( onClickFunction ) {
			onClickFunction();
		}
	}
}

void Button::onRelease( glm::vec2 pos ) {
	// perform release function if released over the button
	if ( isOverButton(pos) ) {
		state = HOVER;

		if ( onReleaseFunction ) {
			onReleaseFunction();
		}
	} else {
		state = RELEASED;
	}
}

void Button::onMouseMovement( glm::vec2 pos ) {
	if ( state != PRESSED ) {
		if ( isOverButton( pos ) ) {
			state = HOVER;
		} else {
			state = RELEASED;
		}
	}
}

void Button::setTextures( Texture pressed, Texture released ) {
	pressedTexture = pressed;
	releasedTexture = released;
}

void Button::setTextColor( glm::vec3 color ) {
	textColor = color;
}

void Button::setText( std::string s ) {
	text = s;
}

void Button::render( Graphics& graphics ) {
	// render button texture
	if ( state == PRESSED ) {
		graphics.draw2DTexture( pressedTexture, pos, size, 0.0f );
	} else if ( state == RELEASED ) {
		graphics.draw2DTexture( releasedTexture, pos, size, 0.0f );
	} else {
		graphics.draw2DTexture( hoverTexture, pos, size, 0.0f );
	}

	// render button text
	graphics.renderText( fontType, sfw::string(text.c_str()), pos + size / 2.0f, 1.2f, textColor, CENTERED );
}

void Button::setOnClickFunction( std::function<void()> fcn ) {
	onClickFunction = fcn;
}

void Button::setOnReleaseFunction( std::function<void()> fcn ) {
	onReleaseFunction = fcn;
}

GLboolean Button::isOverButton( glm::vec2 pos ) const {
	return ( pos.x >= this->pos.x && pos.x <= this->pos.x + size.x
		&& pos.y >= this->pos.y && pos.y <= this->pos.y + size.y );
}

