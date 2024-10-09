#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"

class ResourceManager
{
public:
	// resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map < std::string, Texture2D> Textures;
	// load and generate shader program from file
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	// retrieve stored shader
	static Shader GetShader(std::string name);
	// load and generate texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	// retrieve stored texture
	static Texture2D GetTexture(std::string name);
	// de-allocate all loaded resources
	static void Clear();
private:
	// Singleton requirements
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	ResourceManager& operator=(const ResourceManager&);
	// Helper methods for file IO
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

