#pragma once

#include "defs.hpp"


inline std::tuple<int, int> GetWindowDimensions(Window window)
{
	int width;
	int height;

	SDL_GetWindowSize(window.SDLwindow, &width, &height);

	return std::make_tuple(width, height);
}
