#include "Player.hpp"
#include "../Mobs/Mobs.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math_defs.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/variant_internal.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/kinematic_collision3d.hpp>

using namespace godot;

Player::Player() {
	// Initialize any variables here.
	speed = 14;
	fall_speed = 75;
	jump_impulse = 20;
	bounce_impulse = 16;
}

Player::~Player() {
	// Add your cleanup here.
}

uint8_t Player::get_speed(void) {
	return speed;
}

uint8_t Player::get_fall_speed(void) {
	return fall_speed;
}

uint8_t Player::get_jump_impulse(void) {
	return jump_impulse;
}

uint8_t Player::get_bounce_impulse(void) {
	return bounce_impulse;
}

void Player::set_speed(uint8_t p_value) {
	speed = p_value;
}

void Player::set_fall_speed(uint8_t p_value) {
	fall_speed = p_value;
}

void Player::set_jump_impulse(uint8_t p_value) {
	jump_impulse = p_value;
}

void Player::set_bounce_impulse(uint8_t p_value) {
	bounce_impulse = p_value;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
	ClassDB::bind_method(D_METHOD("get_fall_speed"), &Player::get_fall_speed);
	ClassDB::bind_method(D_METHOD("get_jump_impulse"), &Player::get_jump_impulse);
	ClassDB::bind_method(D_METHOD("get_bounce_impulse"), &Player::get_bounce_impulse);

	ClassDB::bind_method(D_METHOD("set_speed"), &Player::set_speed);
	ClassDB::bind_method(D_METHOD("set_fall_speed"), &Player::set_fall_speed);
	ClassDB::bind_method(D_METHOD("set_jump_impulse"), &Player::set_jump_impulse);
	ClassDB::bind_method(D_METHOD("set_bounce_impulse"), &Player::set_bounce_impulse);

	ClassDB::bind_method(D_METHOD("die"), &Player::die);

	ADD_SIGNAL(MethodInfo("hit", PropertyInfo()));
	ADD_PROPERTY(PropertyInfo(Variant::INT, "speed", PROPERTY_HINT_RANGE, "0,255,1"), "set_speed", "get_speed");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "fall_speed", PROPERTY_HINT_RANGE, "0,255,1"), "set_fall_speed", "get_fall_speed");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "jump_impulse", PROPERTY_HINT_RANGE, "0,255,1"), "set_jump_impulse", "get_jump_impulse");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "bounce_impulse", PROPERTY_HINT_RANGE, "0,255,1"), "set_bounce_impulse", "get_bounce_impulse");
}

void Player::_ready(void) {
	input = Input::get_singleton();
	Pivot = get_node<Node3D>("Pivot");
	APlayer = get_node<AnimationPlayer>("AnimationPlayer");

	get_node<Area3D>("MobDetector")->connect("body_entered", Callable(this, "die"));
	connect("hit", Callable(get_node<Node>("/root/Main"), "player_killed"));
}

void Player::_physics_process(double delta) {
	static Vector3 velocity = Vector3(0, 0, 0);
	Vector3 direction = Vector3(0, 0, 0);

	if (input->is_action_pressed("move_right")) {
		direction.x += 1;
	}

	if (input->is_action_pressed("move_left")) {
		direction.x -= 1;
	}

	if (input->is_action_pressed("move_down")) {
		direction.z += 1;
	}

	if (input->is_action_pressed("move_up")) {
		direction.z -= 1;
	}

	if (direction != Vector3(0, 0, 0)) {
		direction.normalize();
		Pivot->set_basis(Basis::looking_at(direction));
		APlayer->set_speed_scale(4);
	} else {
		APlayer->set_speed_scale(1);
	}

	velocity.x = direction.x * speed;
	velocity.z = direction.z * speed;

	if (!is_on_floor()) {
		velocity.y = velocity.y - (fall_speed * delta);
	}

	set_velocity(velocity);
	move_and_slide();

	if (is_on_floor() && input->is_action_just_pressed("jump")) {
		velocity.y = jump_impulse;
	}

	for (uint8_t i = 0; i < get_slide_collision_count(); i++) {
		Ref<KinematicCollision3D> collision = get_slide_collision(i);
		Mob* CollisionNode = cast_to<Mob>(collision->get_collider());

		if (CollisionNode == nullptr) {
			continue;
		}

		if (CollisionNode->is_in_group("Mobs")) {
			if (Vector3(0, 1, 0).dot(collision->get_normal()) > 0.1) {
				CollisionNode->squash();
				velocity.y = bounce_impulse;
				break;
			}
		}
	}
	Vector3 rotation = Pivot->get_rotation();
	rotation.x = Math_PI / 6 * get_velocity().y / jump_impulse;
	Pivot->set_rotation(rotation);
}

void Player::die(Node3D* body) {
	emit_signal("hit");
	queue_free();
}
