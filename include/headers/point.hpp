#pragma once

#include "stl_headers.hpp"
#include "third_party.hpp"

#include "core.hpp"
#include "interface.hpp"


#include "editor.hpp"
#include "scripting_engine.hpp"


class Point
{
	public:
		EngineState POINT_engine_state;
		Core			core;
		Interface		intr;
		ScriptingEngine scripting;
		Editor			T_editor;

		Point();
		void Run();
		void Restart();
		void Quit();
};
