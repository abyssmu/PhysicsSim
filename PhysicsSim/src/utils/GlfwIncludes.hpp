/**
* @file GlfwIncludes.hpp
* @brief
* Header file to include the necessary GLFW and OpenGL headers.
*/

#pragma once

#ifndef _GLFWANDDEBUG_
#define _GLFWANDDEBUG_

#define GL_SILENCE_DEPRECATION
#ifdef IMGUI_IMPL_OPENGL_ES2
#include <GLES2/gl2.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#endif