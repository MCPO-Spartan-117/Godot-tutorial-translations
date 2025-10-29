#include "HUD.hpp"
//#include <unistd.h>

extern "C" Variant _ready(void) {
	if(!is_editor()) {
		Node hud = get_node();
		hud.add_user_signal("start_game");
		get_node<Button>("StartButton").connect(hud, "pressed", "start_button");
		get_node<Timer>("MessageTimer").connect(hud, "timeout", "message_timeout");
	}
	return Nil;
}

extern "C" void show_message(std::string text) {
	Label label = get_node("Message");
	label.set_text(text);
	label.show();
	get_node<Timer>("MessageTimer").start();
}

extern "C" void show_game_over(void) {
	show_message("Game Over");
	//usleep(500);
	//await $MessageTimer.timeout

	Label label = get_node("Message");
	label.set_text("Dodge the Creeps!");
	label.show();

	//sleep(1);
	//await get_tree().create_timer(1.0).timeout
	get_node<Button>("StartButton").show();
}

// this breaks for some reason if not a Variant
extern "C" Variant update_score(uint16_t score) {
	get_node<Label>("ScoreLabel").set_text(std::to_string(score));
	return Nil;
}

extern "C" void start_button(void) {
	get_node<Button>("StartButton").hide();
	get_node().emit_signal("start_game");
}

extern "C" void message_timeout(void) {
	get_node<Label>("Message").hide();
}

int main() {}
