#pragma once

#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/path_follow2d.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/audio_stream_player2d.hpp>
#include "../Player/Player.hpp"
#include "../HUD/HUD.hpp"

namespace godot {
	class Main : public Node {
		GDCLASS(Main, Node)

	protected:
		static void _bind_methods(void);

	private:
		RandomNumberGenerator* RNG;
		ResourceLoader* Loader;
		Ref<PackedScene> Mob_Scene;
		String Mob_Scene_String;
		SceneTree* Tree;
		Marker2D* StartPosition;
		PathFollow2D* MobSpawnLocation;
		Timer* StartTimer;
		Timer* ScoreTimer;
		Timer* MobTimer;
		class HUD* HUD;
		class Player* Player;
		AudioStreamPlayer2D* Music;
		AudioStreamPlayer2D* DeathSound;
		uint16_t score;

	public:
		Main(void);
		~Main(void) override;

		String get_scene(void);
		void set_scene(String val);

		void _ready(void) override;
		void game_over_temp(void);
		void game_over(void);
		void new_game(void);
		void start_timeout(void);
		void score_inc(void);
		void mob_spawn(void);
	};
}
