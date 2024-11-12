#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

namespace Breakout {


	std::map<std::string, Texture2D>    ResourceManager::s_Textures;
	std::map<std::string, Shader>       ResourceManager::s_Shaders;

	Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
	{
		s_Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return s_Shaders[name];
	}

	Shader ResourceManager::GetShader(std::string name)
	{
		return s_Shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
	{
		s_Textures[name] = LoadTextureFromFile(file, alpha);
		return s_Textures[name];
	}

	Texture2D ResourceManager::GetTexture(std::string name)
	{
		return s_Textures[name];
	}

	void ResourceManager::Clear()
	{
		for (auto i : s_Shaders)
			GLCall(glDeleteProgram(i.second.m_ID));
		for (auto i : s_Textures)
			GLCall(glDeleteTextures(1, &i.second.m_ID));
	}



	Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{
			// open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::exception e)
		{
			BK_ERROR("Failed to read shader files");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		const char* gShaderCode = geometryCode.c_str();
		// 2. now create shader object from source code
		Shader shader;
		shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
		return shader;
	}

	Texture2D ResourceManager::LoadTextureFromFile(const char* file, bool alpha)
	{
		Texture2D texture;
		if (alpha) {
			texture.m_InternalFormat = GL_RGBA;
			texture.m_ImageFormat = GL_RGBA;
		}

		int width, height, numChannels;
		unsigned char* data = stbi_load(file, &width, &height, &numChannels, 0);

		texture.Generate(width, height, data);
		stbi_image_free(data);
		return texture;
	}
}