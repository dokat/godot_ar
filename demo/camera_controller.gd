extends Node

export(NodePath) var sceneNode
export(float) var marker_size = 0.07
export(int) var marker_id = 6
export(float) var scale = 5
var scene = null

var img = Image.new()
var tex = ImageTexture.new()

func _ready():
	if sceneNode != null:
		scene = get_node(sceneNode)
		$ARCamera.open()
		$ARCamera.setMarkerId(marker_id)
		set_process(true)
		get_tree().set_auto_accept_quit(false)
	
func _process(delta):
	if $ARCamera.is_open():
		var pool = $ARCamera.get_picture_buffer(true)
		img.load_jpg_from_buffer(pool)
		tex.create_from_image(img)
		$CanvasLayer/TextureRect.texture = tex
			
		if $ARCamera.isDetected():
			var pos = $ARCamera.getPosition() / (Vector3(-marker_size, marker_size, -marker_size) / scale)
			var orientation = $ARCamera.getOrientation()
		
			scene.transform = Transform(orientation, pos)
			
func _notification(what):
	if what == MainLoop.NOTIFICATION_WM_QUIT_REQUEST:
		set_process(false)
		set_physics_process(false)
		print("Quiting camera controller")
		$ARCamera.release()
		get_tree().quit()