#pragma once

#include "godot_cpp/classes/scene_tree.hpp"
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/button.hpp>

namespace godot {
	class HUD : public CanvasLayer {
		GDCLASS(HUD, CanvasLayer)

	protected:
		static void _bind_methods(void);
		SceneTree* Tree;
		Label* ScoreLabel;
		Label* Message;
		Timer* MessageTimer;
		Button* StartButton;
		bool Timerwait;

	public:
		HUD(void);
		~HUD(void) override;

		void _ready(void) override;
		void show_message(String message);
		void show_game_over(void);
		void update_score(uint16_t val);
		void start_button(void);
		void message_timeout(void);
	};
}
