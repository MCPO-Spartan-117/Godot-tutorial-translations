#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include "godot_cpp/classes/collision_shape2d.hpp"
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot {
	class Player : public Area2D {
		GDCLASS(Player, Area2D)

	protected:
		static void _bind_methods(void);
		//static Ref<AnimatedSprite2D> aSprite;

	private:
		double speed;
		Vector2 screen_size;
		AnimatedSprite2D* SpriteNode;
		CollisionShape2D* CollisionNode;
		Input* input;

	public:
		Player(void);
		~Player(void) override;

		double get_speed(void);
		void set_speed(double val);

		void _ready(void) override;
		void _process(double delta) override;
		void damage(Node2D* body);
		void start(Vector2 pos);
	};
}
