#pragma once
#include "../main.hpp"

struct HUD : public CanvasLayer {
	using CanvasLayer::CanvasLayer;
	METHOD(void, show_game_over)
	METHOD(Variant, update_score)
	METHOD(void, show_message)
};
