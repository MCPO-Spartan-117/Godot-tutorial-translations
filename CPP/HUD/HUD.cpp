#include "HUD.hpp"
#include "godot_cpp/classes/scene_tree_timer.hpp"
#include <godot_cpp/core/class_db.hpp>

#include <unistd.h>
#include <string>

using namespace godot;

void HUD::_bind_methods() {
	ClassDB::bind_method(D_METHOD("show_message"), &HUD::show_message);
	ClassDB::bind_method(D_METHOD("show_game_over"), &HUD::show_game_over);
	ClassDB::bind_method(D_METHOD("update_score"), &HUD::update_score);
	ClassDB::bind_method(D_METHOD("start_button"), &HUD::start_button);
	ClassDB::bind_method(D_METHOD("message_timeout"), &HUD::message_timeout);

	ADD_SIGNAL(MethodInfo("start_game", PropertyInfo()));
}

HUD::HUD() {
	// Initialize any variables here.
	Timerwait = 0;
}

HUD::~HUD() {
	// Add your cleanup here.
}

void HUD::_ready(void) {
	Tree = get_tree();
	ScoreLabel = get_node<Label>("ScoreLabel");
	Message = get_node<Label>("Message");
	StartButton = get_node<Button>("StartButton");
	MessageTimer = get_node<Timer>("MessageTimer");

	StartButton->connect("pressed", Callable(this, "start_button"));
	MessageTimer->connect("timeout", Callable(this, "message_timeout"));
}

void HUD::show_message(String message) {
	Message->set_text(message);
	Message->show();
	MessageTimer->start();
}

void HUD::show_game_over(void) {
	//Nodes can only be accessed on the main thread, have to use call_deferred.
	call_deferred("show_message", "Game Over");
	Timerwait = 1;
	while (Timerwait) {
		usleep(20);
	}

	Message->call_deferred("set_text", "Dodge the Creeps!");
	Message->call_deferred("show");

	Ref<SceneTreeTimer> temp = Tree->create_timer(1.0);
	while (temp->get_time_left() > 0) {
		usleep(20);
	}
	StartButton->call_deferred("show");
}

void HUD::update_score(uint16_t val) {
	ScoreLabel->set_text(std::to_string(val).c_str());
}

void HUD::start_button(void) {
	StartButton->hide();
	emit_signal("start_game");
}

void HUD::message_timeout(void) {
	Message->hide();
	Timerwait = 0;
}
