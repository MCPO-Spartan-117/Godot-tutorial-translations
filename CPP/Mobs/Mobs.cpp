#include "../main.hpp"

extern "C" Variant _ready(void) {
	if(!is_editor()) {
		RigidBody2D Mob = get_node();
		VisibleOnScreenNotifier2D offscreennode = get_node("VisibleOnScreenNotifier2D");
		AnimatedSprite2D Sprite = get_node("AnimatedSprite2D");
		SpriteFrames Frames = cast_to<SpriteFrames>(Sprite.get_sprite_frames());
		std::vector<std::basic_string<char>> FrameNames = Frames.get_animation_names().fetch();
		Sprite.set_animation(FrameNames[rand() % FrameNames.size()]);
		Sprite.play();
		offscreennode.connect(Mob, "screen_exited", "off_screen_delete");
	}
	return Nil;
}

extern "C" Variant _process(double delta) {
	return Nil;
}

extern "C" void off_screen_delete(void) {
	RigidBody2D Mob = get_node();
	Mob.queue_free();
}

int main(void) {

}
