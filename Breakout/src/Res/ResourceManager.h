#pragma once

#include "Core.h"
#include "Log.h"

#include <map>
#include <string>
#include <filesystem>

#include "Graphics/Texture.h"
#include "Graphics/Shader.h"


namespace Breakout {

	/*
		Layout for shader files in storage:

		{projectName}/Resources/ShaderName/ShaderName.fs.glsl
		{projectName}/Resources/ShaderName/ShaderName.gs.glsl
		{projectName}/Resources/ShaderName/ShaderName.vs.glsl
	*/


	struct ShaderFileBundle
	{
		const char* fShaderFile;
		const char* gShaderFile = nullptr;
		const char* vShaderFile;
	};



	class ResourceManager
	{
	public:
		static std::map<std::string, Shader> s_Shaders;
		static std::map<std::string, Texture2D> s_Textures;

		static void InitShaders();
		static void InitTextures();

		static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
		static Shader GetShader(std::string name);

		static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
		static Texture2D GetTexture(std::string name);

		static void Clear();
	private:
		ResourceManager() {}

		static void InitShaderBundle(const std::filesystem::directory_entry& entry, std::string name);

		static Shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
		static Texture2D LoadTextureFromFile(const char* file, bool alpha);
	};


}

