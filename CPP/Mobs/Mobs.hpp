#pragma once

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/character_body3d.hpp>

namespace godot {
	class Mob : public CharacterBody3D {
		GDCLASS(Mob, CharacterBody3D)

	protected:
		static void _bind_methods(void);

	private:
		uint8_t min_speed;
		uint8_t max_speed;

	public:
		Mob(void);
		~Mob(void) override;

		void _ready(void) override;
		void _physics_process(double delta) override;

		uint8_t get_min_speed(void);
		uint8_t get_max_speed(void);

		void set_min_speed(uint8_t p_value);
		void set_max_speed(uint8_t p_value);

		void init(Vector3 start_pos, Vector3 player_pos);
		void off_screen_delete(void);
		void squash(void);

		RandomNumberGenerator* RNG;
	};
}
