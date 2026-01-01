#include "Mobs.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math_defs.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/visible_on_screen_notifier3d.hpp>

using namespace godot;

Mob::Mob() {
	// Initialize any variables here.
	min_speed = 10;
	max_speed = 18;
}

Mob::~Mob() {
	// Add your cleanup here.
}

uint8_t Mob::get_min_speed(void) {
	return min_speed;
}

uint8_t Mob::get_max_speed(void) {
	return max_speed;
}

void Mob::set_min_speed(uint8_t p_value) {
	min_speed = p_value;
}

void Mob::set_max_speed(uint8_t p_value) {
	max_speed = p_value;
}

void Mob::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_min_speed"), &Mob::get_min_speed);
	ClassDB::bind_method(D_METHOD("get_max_speed"), &Mob::get_max_speed);

	ClassDB::bind_method(D_METHOD("set_min_speed"), &Mob::set_min_speed);
	ClassDB::bind_method(D_METHOD("set_max_speed"), &Mob::set_max_speed);

	ClassDB::bind_method(D_METHOD("initialize"), &Mob::init);
	ClassDB::bind_method(D_METHOD("off_screen_delete"), &Mob::off_screen_delete);
	ClassDB::bind_method(D_METHOD("squash"), &Mob::squash);

	ADD_SIGNAL(MethodInfo("squashed", PropertyInfo()));
	ADD_PROPERTY(PropertyInfo(Variant::INT, "min_speed", PROPERTY_HINT_RANGE, "0,255,1"), "set_min_speed", "get_min_speed");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_speed", PROPERTY_HINT_RANGE, "0,255,1"), "set_max_speed", "get_max_speed");
}

void Mob::_ready(void) {
	get_node<VisibleOnScreenNotifier3D>("VisibleOnScreenNotifier3D")->connect("screen_exited", Callable(this, "off_screen_delete"));
}

void Mob::_physics_process(double delta) {
	move_and_slide();
}

void Mob::init(Vector3 start_pos, Vector3 player_pos) {
	const double tempPI = Math_PI / 4;

	look_at_from_position(start_pos, player_pos, Vector3(0, 1, 0));
	float rotate = RNG->randf_range(-tempPI, tempPI);
	rotate_y(rotate);

	int8_t random_speed = RNG->randi_range(min_speed, max_speed);
	set_velocity(Vector3(Vector3(0, 0, -1) * random_speed).rotated(Vector3(0, 1, 0), get_rotation().y));
	get_node<AnimationPlayer>("AnimationPlayer")->set_speed_scale(random_speed / min_speed);
}

void Mob::off_screen_delete(void) {
	queue_free();
}

void Mob::squash(void) {
	emit_signal("squashed");
	queue_free();
}
