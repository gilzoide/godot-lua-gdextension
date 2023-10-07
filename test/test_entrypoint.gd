extends SceneTree

const LUA_TEST_DIR = "res://lua_tests"
const GDSCRIPT_TEST_DIR = "res://gdscript_tests"

func _initialize():
	var all_success = true
	
	for lua_script in DirAccess.get_files_at(LUA_TEST_DIR):
		var lua_state = LuaState.new()
		lua_state.open_libraries()
		
		var file_name = str(LUA_TEST_DIR, "/", lua_script)
		var result = lua_state.do_file(file_name)
		if result is LuaError:
			all_success = false
			printerr("🗴 ", lua_script, ": ", result.message)
		else:
			print("✓ ", lua_script)

	for gdscript in DirAccess.get_files_at(GDSCRIPT_TEST_DIR):
		print("> ", gdscript, ":")
		var file_name = str(GDSCRIPT_TEST_DIR, "/", gdscript)
		var obj = load(file_name).new()
		for method in obj.get_method_list():
			var method_name = method.name
			if method_name.begins_with("test"):
				if not obj.call(method_name):
					all_success = false
					printerr("  🗴 ", method_name)
				else:
					print("  ✓ ", method_name)
	
	quit(0 if all_success else -1)
