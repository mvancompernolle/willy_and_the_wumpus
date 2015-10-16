#pragma once

#ifndef CONSTS_H
#define CONSTS_H

#include <glm/glm.hpp>

enum STATE { SPLASH, MAIN_INIT, MAIN, PLAY, GAME, EXIT };

#define COLOR_INFO glm::vec3(0.0f, 0.0f, 1.0f)
#define COLOR_ACTION glm::vec3(0.0f)
#define	COLOR_NEGATIVE glm::vec3(0.5f, 0.0f, 0.0f)
#define	COLOR_POSITIVE glm::vec3(0.0f, 0.5f, 0.0f)

#endif // CONSTS_H