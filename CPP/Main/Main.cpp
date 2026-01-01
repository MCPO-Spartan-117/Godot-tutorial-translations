#include "Main.hpp"
#include "../Mobs/Mobs.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math_defs.hpp>

using namespace godot;

Main::Main() {
	// Initialize any variables here.
	Loader = ResourceLoader::get_singleton();
	RNG = memnew(RandomNumberGenerator);
	Mob_Scene_String = "";
}

Main::~Main() {
	// Add your cleanup here.
}

String Main::get_scene(void) {
	return Mob_Scene_String;
}

void Main::set_scene(String p_value) {
	Mob_Scene_String = p_value;
}

void Main::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_scene"), &Main::get_scene);

	ClassDB::bind_method(D_METHOD("set_scene"), &Main::set_scene);

	ClassDB::bind_method(D_METHOD("mob_spawn"), &Main::mob_spawn);
	ClassDB::bind_method(D_METHOD("player_killed"), &Main::player_killed);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "Mob_Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene", "get_scene");
}

void Main::_ready(void) {
	Tree = get_tree();
	UI_Score = get_node<Label>("UserInterface/ScoreLabel");
	UI_Retry = get_node<ColorRect>("UserInterface/Retry");
	MobTimer = get_node<Timer>("MobTimer");
	MobPath = get_node<PathFollow3D>("SpawnPath/SpawnLocation");
	Player = get_node<CharacterBody3D>("Player");

	Mob_Scene = Loader->load("res://Scenes/" + Mob_Scene_String, "PackedScene");

	MobTimer->connect("timeout", Callable(this, "mob_spawn"));
	UI_Retry->hide();
}

void Main::_unhandled_input(const Ref<InputEvent> event) {
	if (event->is_action_pressed("ui_accept") && UI_Retry->is_visible()) {
		Tree->reload_current_scene();
	}
}

void Main::mob_spawn(void) {
	Mob* mob = cast_to<Mob>(Mob_Scene->instantiate());

	MobPath->set_progress_ratio(RNG->randf());

	mob->RNG = RNG;
	mob->init(MobPath->get_position(), Player->get_position());

	add_child(mob);

	mob->connect("squashed", Callable(UI_Score, "score_inc"));
}

void Main::player_killed(void) {
	MobTimer->stop();
	UI_Retry->show();
}
