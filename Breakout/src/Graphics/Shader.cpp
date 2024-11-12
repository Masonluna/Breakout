#include "Log.h"
#include "Shader.h"

Breakout::Shader& Breakout::Shader::Use()
{
	GLCall(glUseProgram(this->m_ID));
	return *this;
}

void Breakout::Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	unsigned int sVertex, sFragment, gShader;

	// ==================== COMPILING SHADERS =====================
	// ============================================================
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(sVertex, 1, &vertexSource, NULL));
	GLCall(glCompileShader(sVertex));
	checkCompileErrors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(sFragment, 1, &fragmentSource, NULL));
	GLCall(glCompileShader(sFragment));
	checkCompileErrors(sFragment, "FRAGMENT");
	
	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		GLCall(glShaderSource(gShader, 1, &geometrySource, NULL));
		GLCall(glCompileShader(gShader));
		checkCompileErrors(gShader, "GEOMETRY");
	}

	// ===================== SHADER PROGRAM =======================
	// ============================================================

	this->m_ID = glCreateProgram();
	GLCall(glAttachShader(this->m_ID, sVertex));
	GLCall(glAttachShader(this->m_ID, sFragment));
	if (geometrySource != nullptr) {
		GLCall(glAttachShader(this->m_ID, gShader));
	}
	GLCall(glLinkProgram(this->m_ID));
	checkCompileErrors(this->m_ID, "PROGRAM");
	GLCall(glDeleteShader(sVertex));
	GLCall(glDeleteShader(sFragment));
	if (geometrySource != nullptr) {
		GLCall(glDeleteShader(gShader));
	}




}

void Breakout::Shader::SetFloat(const char* name, float value, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform1f(glGetUniformLocation(this->m_ID, name), value));
}
void Breakout::Shader::SetInteger(const char* name, int value, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform1i(glGetUniformLocation(this->m_ID, name), value));
}
void Breakout::Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform2f(glGetUniformLocation(this->m_ID, name), x, y));
}
void Breakout::Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform2f(glGetUniformLocation(this->m_ID, name), value.x, value.y));
}
void Breakout::Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform3f(glGetUniformLocation(this->m_ID, name), x, y, z));
}
void Breakout::Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform3f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z));
}
void Breakout::Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform4f(glGetUniformLocation(this->m_ID, name), x, y, z, w));
}
void Breakout::Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniform4f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z, value.w));
}
void Breakout::Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader)
		this->Use();
	GLCall(glUniformMatrix4fv(glGetUniformLocation(this->m_ID, name), 1, false, glm::value_ptr(matrix)));
}

void Breakout::Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		GLCall(glGetShaderiv(object, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(object, 1024, NULL, infoLog));
			BK_ERROR("[SHADER] Compile-time error: Type: {0}\n{1}\n -- --------------------------------------------------- -- \n", type, infoLog);
		}
	}
	else {
		GLCall(glGetProgramiv(object, GL_LINK_STATUS, &success));
		if (!success) {
			GLCall(glGetProgramInfoLog(object, 1024, NULL, infoLog));
			BK_ERROR("[SHADER] Link-time error: Type: {0}\n{1}\n -- --------------------------------------------------- -- \n", type, infoLog);
		}
	}
}
