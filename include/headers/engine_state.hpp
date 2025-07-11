#pragma once

#include "stl_headers.hpp"

struct EngineState
{
	std::shared_ptr<bool> engine_quit = std::make_shared<bool>(false);
	std::shared_ptr<bool> editor_mode = std::make_shared<bool>(true);
};