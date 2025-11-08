#include "Mobs.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Mob::Mob() {
	// Initialize any variables here.
}

Mob::~Mob() {
	// Add your cleanup here.
}

void Mob::_bind_methods() {
	ClassDB::bind_method(D_METHOD("off_screen_delete"), &Mob::off_screen_delete);
}

void Mob::_ready(void) {
	AnimatedSprite2D* Sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	VisibleOnScreenNotifier2D* VisibleNotifier = get_node<VisibleOnScreenNotifier2D>("VisibleOnScreenNotifier2D");
	PackedStringArray AnimationNames = Sprite->get_sprite_frames()->get_animation_names();
	Sprite->set_animation(AnimationNames.get(rand() % AnimationNames.size()));
	Sprite->play();
	VisibleNotifier->connect("screen_exited", Callable(this, "off_screen_delete"));
}

void Mob::off_screen_delete(void) {
	queue_free();
}
