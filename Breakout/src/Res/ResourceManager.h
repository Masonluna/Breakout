#pragma once

#include "Core.h"
#include "Log.h"

#include <map>
#include <string>

#include "Graphics/Texture.h"
#include "Graphics/Shader.h"


namespace Breakout {



	class ResourceManager
	{
	public:
		static std::map<std::string, Shader> s_Shaders;
		static std::map<std::string, Texture2D> s_Textures;

		static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
		static Shader GetShader(std::string name);

		static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
		static Texture2D GetTexture(std::string name);

		static void Clear();
	private:
		ResourceManager() {}
		static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFIle = nullptr);
		static Texture2D LoadTextureFromFile(const char* file, bool alpha);
	};


}

