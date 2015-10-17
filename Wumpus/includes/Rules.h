#pragma once

#ifndef RULES_H
#define RULES_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Consts.h"
#include "Button.h"
#include "Textbox.h"

class Rules {
public:
					Rules( GLuint w, GLuint h );
					~Rules();
	void			init();
	STATE			update();
	void			render();
	void			setPrevState( STATE s );
private:
	GLuint			width, height;
	Textbox			tbRules;
	Button			bBack;
	STATE			current, prevState;
};

#endif // RULES_H