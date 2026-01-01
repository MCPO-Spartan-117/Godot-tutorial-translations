#pragma once

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/animation_player.hpp>

namespace godot {
	class Player : public CharacterBody3D {
		GDCLASS(Player, CharacterBody3D)

	protected:
		static void _bind_methods(void);

	private:
		Input* input;
		Node3D* Pivot;
		AnimationPlayer* APlayer;

		uint8_t speed;
		uint8_t fall_speed;
		uint8_t jump_impulse;
		uint8_t bounce_impulse;

	public:
		Player(void);
		~Player(void) override;

		void _ready(void) override;
		void _physics_process(double delta) override;

		uint8_t get_speed(void);
		uint8_t get_fall_speed(void);
		uint8_t get_jump_impulse(void);
		uint8_t get_bounce_impulse(void);

		void set_speed(uint8_t);
		void set_fall_speed(uint8_t);
		void set_jump_impulse(uint8_t);
		void set_bounce_impulse(uint8_t);

		void die(Node3D* body);
	};
}
