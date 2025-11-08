#include "Main.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/math_defs.hpp>

#include <thread>

using namespace godot;

Main::Main() {
	// Initialize any variables here.
	score = 0;
	Mob_Scene_String = "";
}

Main::~Main() {
	// Add your cleanup here.
}

void Main::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_scene"), &Main::get_scene);
	ClassDB::bind_method(D_METHOD("set_scene"), &Main::set_scene);

	ClassDB::bind_method(D_METHOD("game_over"), &Main::game_over);
	ClassDB::bind_method(D_METHOD("new_game"), &Main::new_game);
	ClassDB::bind_method(D_METHOD("start_timeout"), &Main::start_timeout);
	ClassDB::bind_method(D_METHOD("score_inc"), &Main::score_inc);
	ClassDB::bind_method(D_METHOD("mob_spawn"), &Main::mob_spawn);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "Mob_Scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_scene", "get_scene");
}

String Main::get_scene(void) {
	return Mob_Scene_String;
}

void Main::set_scene(String val) {
	Mob_Scene_String = val;
}

void Main::_ready(void) {
	RNG = memnew(RandomNumberGenerator);
	Loader = ResourceLoader::get_singleton();
	Mob_Scene = Loader->load("res://Scenes/" + Mob_Scene_String, "PackedScene");
	Tree = get_tree();
	StartPosition = get_node<Marker2D>("StartPosition");
	StartTimer = get_node<Timer>("StartTimer");
	ScoreTimer = get_node<Timer>("ScoreTimer");
	MobTimer = get_node<Timer>("MobTimer");
	MobSpawnLocation = get_node<PathFollow2D>("MobPath/MobSpawnLocation");
	HUD = reinterpret_cast<class HUD*>(get_node<CanvasLayer>("HUD"));
	Player = reinterpret_cast<class Player*>(get_node<Area2D>("Player"));
	Music = get_node<AudioStreamPlayer2D>("Music");
	DeathSound = get_node<AudioStreamPlayer2D>("DeathSound");

	StartTimer->connect("timeout", Callable(this, "start_timeout"));
	ScoreTimer->connect("timeout", Callable(this, "score_inc"));
	MobTimer->connect("timeout", Callable(this, "mob_spawn"));
	Player->connect("hit", Callable(this, "game_over"));
	HUD->connect("start_game", Callable(this, "new_game"));
}

void Main::game_over(void) {
	ScoreTimer->stop();
	MobTimer->stop();
	std::thread HUDthread([this]() {
		HUD->show_game_over();
	});
	HUDthread.detach();
	Music->stop();
	DeathSound->play();
}

void Main::new_game(void) {
	score = 0;
	Tree->call_group("mobs", "queue_free");
	Player->start(StartPosition->get_position());
	StartTimer->start();
	HUD->update_score(score);
	HUD->show_message("Get Ready");
	Music->play();
}

void Main::start_timeout(void) {
	MobTimer->start();
	ScoreTimer->start();
}

void Main::score_inc(void) {
	score += 1;
	HUD->update_score(score);
}

void Main::mob_spawn(void) {
	RigidBody2D* mob_instance = cast_to<RigidBody2D>(Mob_Scene->instantiate());
	MobSpawnLocation->set_progress_ratio(RNG->randf());
	mob_instance->set_position(MobSpawnLocation->get_position());

	double direction = MobSpawnLocation->get_rotation() + Math_PI / 2;
	const double PI_temp = Math_PI / 4;
	direction += RNG->randf_range(-PI_temp, PI_temp);
	mob_instance->set_rotation(direction);

	Vector2 velocity = Vector2(RNG->randi_range(150.0, 250.0), 0.0);
	mob_instance->set_linear_velocity(velocity.rotated(direction));

	add_child(mob_instance);
}
