#pragma once
#include "core.hpp"

class Editor
{
	public:
		Editor(Core& core);

		void Update(Core& core, EngineState& engine_state);
		void InitializeUI(Core& core);
		void UpdateUI(Core& core, EngineState& engine_state);
		void StyleUI();
		void DrawUI();

};