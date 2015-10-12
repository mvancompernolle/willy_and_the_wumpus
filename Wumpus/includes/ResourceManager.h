#pragma once

// Reference: http://www.learnopengl.com/#!In-Practice/2D-Game/Setting-up

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "Texture.h"
#include "Shader.h"
#include "TextChar.h"

class ResourceManager {
public:
												~ResourceManager();

	static Shader								loadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	static Shader								getShader(std::string name);
	static Texture								loadTexture(const GLchar* file, GLboolean alpha, std::string name);
	static Texture								getTexture(std::string name);
	static font									loadFont( const GLchar* file, std::string name, GLuint size );
	static font									getFont( std::string name );
	static void									setPath( std::string name, std::string path );
	static void									setShaderPath( std::string path );
	static void									setTexturePath( std::string path );
	static std::string							getPath( std::string name );
	static void									clear();


	static std::map<std::string, Shader>		shaders;
	static std::map<std::string, Texture>		textures;
	static std::map<std::string, std::string>	paths;
	static std::map<std::string, font> fonts;
private:
												ResourceManager();
	static Shader								loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);
	static Texture								loadTextureFromFile(const GLchar* file, GLboolean alpha);
	static font									loadFontFromFile( const GLchar* file, GLuint fontSize );
};

#endif //RESOURCE_MANAGER_H