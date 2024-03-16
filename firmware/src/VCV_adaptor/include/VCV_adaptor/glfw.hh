#pragma once

struct GLFWwindow {};

inline const char *glfwGetClipboardString(GLFWwindow *) {
	return nullptr;
}

inline void glfwSetClipboardString(GLFWwindow *, char *) {
}
