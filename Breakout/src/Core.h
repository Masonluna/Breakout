#pragma once

#include <glad/glad.h>

#define BK_OPTIMIZE 0

namespace Breakout {
	void GLClearError();
	bool GLLogCall(const char* function, const char* file, int line);

#define ASSERT(X) if (!(x)) __debugbreak();

#if BK_OPTIMIZE

#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

}