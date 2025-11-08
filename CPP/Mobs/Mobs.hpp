#pragma once

#include <godot_cpp/classes/rigid_body2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier2d.hpp>

namespace godot {
	class Mob : public RigidBody2D {
		GDCLASS(Mob, RigidBody2D)

	protected:
		static void _bind_methods(void);
		//static Ref<AnimatedSprite2D> aSprite;

	public:
		Mob(void);
		~Mob(void) override;

		void _ready(void) override;
		void off_screen_delete(void);
	};
}
