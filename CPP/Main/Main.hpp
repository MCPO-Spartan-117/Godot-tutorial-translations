#pragma once

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/path_follow3d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/color_rect.hpp>

namespace godot {
	class Main : public Node {
		GDCLASS(Main, Node)

	protected:
		static void _bind_methods(void);

	private:
		SceneTree* Tree;
		Label* UI_Score;
		ColorRect* UI_Retry;
		Timer* MobTimer;
		PathFollow3D* MobPath;
		Ref<PackedScene> Mob_Scene;
		String Mob_Scene_String;
		CharacterBody3D* Player;

	public:
		Main(void);
		~Main(void) override;

		String get_scene(void);

		void set_scene(String p_value);

		void _ready(void) override;
		void _unhandled_input(const Ref<InputEvent> event);
		void mob_spawn(void);
		void player_killed(void);

		RandomNumberGenerator* RNG;
		ResourceLoader* Loader;
	};
}
