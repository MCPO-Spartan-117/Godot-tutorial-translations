#include "Player.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Player::Player() {
	// Initialize any variables here.
	speed = 400.0;
}

Player::~Player() {
	// Add your cleanup here.
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("damage"), &Player::damage);
	ClassDB::bind_method(D_METHOD("start", "pos"), &Player::start);
	ClassDB::bind_method(D_METHOD("get_speed"), &Player::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed"), &Player::set_speed);

	ADD_SIGNAL(MethodInfo("hit", PropertyInfo()));
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,800,5"), "set_speed", "get_speed");
}

double Player::get_speed(void) {
	return speed;
}

void Player::set_speed(double val) {
	speed = val;
}

void Player::_ready(void) {
	SpriteNode = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	CollisionNode = get_node<CollisionShape2D>("CollisionShape2D");
	input = Input::get_singleton();

	screen_size = get_viewport_rect().size;
	connect("body_entered", Callable(this, "damage"));
	hide();
}

void Player::_process(double delta) {
	Vector2 velocity = Vector2(0.0, 0.0);

	if (input->is_action_pressed("move_right")) {
		velocity.x += 1;
	} else if (input->is_action_pressed("move_left")) {
		velocity.x -= 1;
	}

	if (input->is_action_pressed("move_up")) {
		velocity.y -= 1;
	} else if (input->is_action_pressed("move_down")) {
		velocity.y += 1;
	}

	if (velocity.length() > 0) {
		velocity = velocity.normalized() * speed;
		SpriteNode->play();
		if (velocity.x != 0) {
			SpriteNode->set_animation("walk");
			SpriteNode->set_flip_v(false);
			SpriteNode->set_flip_h(velocity.x < 0);
		} else if (velocity.y != 0) {
			SpriteNode->set_animation("up");
			SpriteNode->set_flip_v(velocity.y > 0);
		}
	} else {
		SpriteNode->stop();
	}

	Vector2 cur_position = get_position();
	Vector2 new_position = cur_position + (velocity * delta);
	Vector2 clamp_position = new_position.clamp(Vector2(0.0, 0.0), screen_size);
	set_position(clamp_position);
}

void Player::damage(Node2D* body) {
	hide();
	emit_signal("hit");
	CollisionNode->set_deferred("disabled", true);
}

void Player::start(Vector2 pos) {
	set_position(pos);
	show();
	CollisionNode->set_disabled(false);
}
