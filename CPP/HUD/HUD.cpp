#include "HUD.hpp"
#include "../../GD/GDScript_helper/GDScript_helper.hpp"

extern "C" Variant _ready(void) {
	if(!is_editor()) {
		Node hud = get_node();
		hud.add_user_signal("start_game");
		get_node<Button>("StartButton").connect(hud, "pressed", "start_button");

		// show_game_over signals
		hud.add_user_signal("message_funct1");
		hud.add_user_signal("message_funct2");
		hud.add_user_signal("message_funct3");
		hud.connect(hud, "message_funct1", "show_game_over_one");
		hud.connect(hud, "message_funct2", "show_game_over_two");
		hud.connect(hud, "message_funct3", "show_game_over_three");
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
	get_node<GDScript_helper>("GDScript_helper").message_helper();
}

extern "C" void show_game_over_one(void) {
	show_message("Game Over");
}

extern "C" void show_game_over_two(void) {
	Label label = get_node("Message");
	label.set_text("Dodge the Creeps!");
	label.show();
}

extern "C" void show_game_over_three(void) {
	get_node<Button>("StartButton").show();
}

// Externally called function must return a Variant, even if Nil
extern "C" Variant update_score(uint16_t score) {
	get_node<Label>("ScoreLabel").set_text(std::to_string(score));
	return Nil;
}

extern "C" void start_button(void) {
	get_node<Button>("StartButton").hide();
	get_node().emit_signal("start_game");
}

int main() {}
