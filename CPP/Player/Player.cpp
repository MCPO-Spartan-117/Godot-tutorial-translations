#include "Player.hpp"

static float speed = 400.0;
static Vector2 screen_size;

extern "C" Variant _ready(void) {
	if (!is_editor()) {
		Player Player = get_node();
		screen_size = Player.get_viewport_rect().size;
		Player.add_user_signal("hit");
		Player.connect(Player, "body_entered", "damage");
		Player.hide();
	}
	return Nil;
}

extern "C" Variant _process(double delta) {
	if (!is_editor()) {
		Player Player = get_node();
		AnimatedSprite2D Sprite = get_node("AnimatedSprite2D");
		Input input = Input::get_singleton();
		Vector2 velocity = Vector2(0.0, 0.0);

		if (input.is_action_pressed("move_right")) {
			velocity.x += 1;
		} else if (input.is_action_pressed("move_left")) {
			velocity.x -= 1;
		}

		if (input.is_action_pressed("move_up")) {
			velocity.y -= 1;
		} else if (input.is_action_pressed("move_down")) {
			velocity.y += 1;
		}

		if (velocity.length() > 0) {
			velocity = velocity.normalized() * speed;
			Sprite.play();
			if (velocity.x != 0) {
				Sprite.set_animation("walk");
				Sprite.set_flip_v(false);
				Sprite.set_flip_h(velocity.x < 0);
			} else if (velocity.y != 0) {
				Sprite.set_animation("up");
				Sprite.set_flip_v(velocity.y > 0);
			}
		} else {
			Sprite.stop();
		}

		Vector2 cur_position = Player.get_position();
		Vector2 new_position = cur_position + (velocity * delta);
		Vector2 clamp_position = new_position.clamp(Vector2(0.0, 0.0), screen_size);
		Player.set_position(clamp_position);
	}
	return Nil;
}

extern "C" void damage(void) {
	Player Player = get_node();
	CollisionShape2D collision = get_node("CollisionShape2D");
	Player.hide();
	Player.emit_signal("hit");
	collision.set_deferred("disabled", true);
}

extern "C" void start(Vector2 pos) {
	Player Player = get_node();
	CollisionShape2D collision = get_node("CollisionShape2D");
	Player.set_position(pos);
	Player.show();
	collision.set_disabled(false);
}

int main(void) {
ADD_PROPERTY(speed, Variant::FLOAT)
}
