#include "../main.hpp"
#include "../Player/Player.hpp"
#include "../HUD/HUD.hpp"
#include <cmath>

static std::string mob_scene_string = "";
static uint16_t score;
// qalc "floatvalue(pi, 64)"
const double PI = 3.141592653589793115997963468544185161590576171875;

SANDBOXED_PROPERTIES(1, {
	.name = "mob scene",
	.type = Variant::STRING,
	.getter = []() -> Variant { return mob_scene_string; },
	.setter = [](Variant value) -> Variant { return mob_scene_string = value.as_std_string(); },
	.default_value = mob_scene_string
})

extern "C" Variant _ready(void) {
	if(!is_editor()) {
		Node Main = get_node();
		Node2D Player = get_node("Player");
		CanvasLayer hud = get_node("HUD");
		Player.connect(Main, "hit", "game_over");
		hud.connect(Main, "start_game", "new_game");

		get_node<Timer>("StartTimer").connect(Main, "timeout", "start_timeout");
		get_node<Timer>("ScoreTimer").connect(Main, "timeout", "score_inc");
		get_node<Timer>("MobTimer").connect(Main, "timeout", "mob_spawn");
	}
	return Nil;
}

extern "C" void game_over(void) {
	get_node<Timer>("ScoreTimer").stop();
	get_node<Timer>("MobTimer").stop();
	get_node<HUD>("HUD").show_game_over();
	get_node<AudioStreamPlayer>("Music").stop();
	get_node<AudioStreamPlayer>("DeathSound").play();
}

extern "C" void new_game(void) {
	score = 0;
	get_tree().call_group("mobs", "queue_free");
	Vector2 StartPosition = get_node<Marker2D>("StartPosition").get_position();
	get_node<Player>("Player").start(StartPosition);
	get_node<Timer>("StartTimer").start();
	HUD hud = get_node("HUD");
	hud.update_score(score);
	hud.show_message("Get Ready");
	get_node<AudioStreamPlayer>("Music").play();
}

extern "C" void start_timeout(void) {
	get_node<Timer>("MobTimer").start();
	get_node<Timer>("ScoreTimer").start();
}

extern "C" void score_inc(void) {
	score += 1;
	get_node<HUD>("HUD").update_score(score);
}

extern "C" void mob_spawn(void) {
	PackedScene mob_scene = load<PackedScene>("res://" + mob_scene_string);
	RigidBody2D mob_instance = mob_scene.instantiate();
	PathFollow2D spawn_location = get_node("MobPath/MobSpawnLocation");
	spawn_location.set_progress_ratio(drand48());
	mob_instance.set_position(spawn_location.get_position());

	double direction = spawn_location.get_rotation() + PI / 2;
	direction += frand_range(0.0, fabs(-PI/4) + PI/4);
	mob_instance.set_rotation(direction);

	Vector2 velocity = Vector2(rand_range(150, 250), 0.0);
	mob_instance.set_linear_velocity(velocity.rotated(direction));

	get_node().add_child(mob_instance);
}

int main(void) {}
