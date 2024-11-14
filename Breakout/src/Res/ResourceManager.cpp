#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

namespace Breakout {

	const char* SHADERS_PATH = "Resources\\Shaders";
	const char* TEXTURES_PATH = "Resources\\Textures";

	std::map<std::string, Texture2D>    ResourceManager::s_Textures;
	std::map<std::string, Shader>       ResourceManager::s_Shaders;

	void ResourceManager::InitShaders()
	{
		std::string path = SHADERS_PATH; // Should be replaced by some constant
		for (const std::filesystem::directory_entry& dir : std::filesystem::directory_iterator(path)) {
			std::string name;
			name = dir.path().string().substr(dir.path().string().find_last_of('\\') + 1);
			InitShaderBundle(dir, name);

		}
	}

	void ResourceManager::InitTextures()
	{
		std::string path = TEXTURES_PATH;
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			std::string name = entry.path().string().substr(entry.path().string().find_last_of('\\') + 1);

			BK_TRACE("CALL::LOADTEXTURE::ARGS\n     FILE = {0}\n    ALPHA = true\n     NAME = {1}", entry.path().string().c_str(), name);
			// LoadTexture(entry.path().string().c_str(), true, name); // We're assuming all textures have an alpha component.
		}
	}

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

	void ResourceManager::InitShaderBundle(const std::filesystem::directory_entry& dir, std::string name)
	{
		std::string vertexPath;
		std::string fragmentPath;
		std::string gShaderPath;

		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dir.path())) {
			std::string entryPath = entry.path().string();

			if (!entryPath.substr(entryPath.length() - 7).compare("vs.glsl")) {
				vertexPath = entryPath;
			}
			else if (!entryPath.substr(entryPath.length() - 7).compare("fs.glsl")) {
				fragmentPath = entryPath;
			}
			else if (!entryPath.substr(entryPath.length() - 7).compare("gs.glsl")) {
				gShaderPath = entryPath;
			}

		}

		if (gShaderPath.empty()) {
			// LoadShader(vertexPath.c_str(), fragmentPath.c_str(), nullptr, name);
			BK_TRACE("CALL::LOADSHADER::ARGS\n    VSHADERFILE = {0}\n    FSHADERFILE = {1}\n    GSHADERFILE = nullptr\n           NAME = {2}",
				vertexPath.c_str(), fragmentPath.c_str(), name);
		}
		else {
			// LoadShader(vertexPath.c_str(), fragmentPath.c_str(), gShaderPath.c_str(), name);
			BK_TRACE("CALL::LOADSHADER::ARGS\n    VSHADERFILE = {0}\n    FSHADERFILE = {1}\n    GSHADERFILE = {2}\n           NAME = {3}",
				vertexPath.c_str(), fragmentPath.c_str(), gShaderPath.c_str(), name);
		}
	}


	Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();

			vertexShaderFile.close();
			fragmentShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

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