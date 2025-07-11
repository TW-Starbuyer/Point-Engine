#pragma once

#include "defs.hpp"

class WindowManager
{
public:
	Window window;
	WindowManager(std::string program_name, int width, int height);
};