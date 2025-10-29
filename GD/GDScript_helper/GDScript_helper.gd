extends Node

func _ready() -> void:
	pass

func _process(delta: float) -> void:
	pass

func message_helper():
	var parent = get_parent()
	var timervar = get_node("../MessageTimer")
	parent.emit_signal("message_funct1")
	await timervar.timeout
	parent.emit_signal("message_funct2")
	await get_tree().create_timer(1.0).timeout
	parent.emit_signal("message_funct3")
