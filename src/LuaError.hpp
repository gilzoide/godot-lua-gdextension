/**
 * Copyright (C) 2023 Gil Barbosa Reis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __LUA_ERROR_HPP__
#define __LUA_ERROR_HPP__

#include <godot_cpp/classes/ref_counted.hpp>
#include <sol/sol.hpp>

using namespace godot;

namespace luagdextension {

class LuaError : public RefCounted {
	GDCLASS(LuaError, RefCounted);

protected:
	static void _bind_methods();

public:
	enum Status {
		OK = LUA_OK,
		YIELDED = LUA_YIELD,
		RUNTIME = LUA_ERRRUN,
		MEMORY = LUA_ERRMEM,
		HANDLER = LUA_ERRERR,
		GC = LUA_ERRGCMM,
		SYNTAX = LUA_ERRSYNTAX,
		FILE = LUA_ERRFILE,
	};

	String get_message() const;
	void set_message(const String& message);

	Status get_status() const;
	void set_status(Status status);

private:
	Status status;
	String message;
};

}
VARIANT_ENUM_CAST(luagdextension::LuaError::Status);

#endif