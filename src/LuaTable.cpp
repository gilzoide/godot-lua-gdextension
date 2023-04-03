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

#include "LuaTable.hpp"
#include "lua_utils.hpp"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;
using namespace godot::internal;

namespace luagdextension {

LuaTable::LuaTable() {
	gde_interface->print_error("LuaTable should never be instantiated manually", __PRETTY_FUNCTION__, __FILE__, __LINE__, true);
}

LuaTable::LuaTable(sol::table&& table) : table(table) {}

LuaTable::LuaTable(const sol::table& table) : table(table) {}

void LuaTable::_bind_methods() {
	ClassDB::bind_method(D_METHOD("to_dictionary"), &LuaTable::to_dictionary);
}

Dictionary LuaTable::to_dictionary() const {
	ERR_FAIL_COND_V_EDMSG(!table.valid(), Dictionary(), "LuaTable does not have a valid table");

	Dictionary dict;
	for (auto it = table.cbegin(); it != table.cend(); ++it) {
		sol::object key, value;
		std::tie(key, value) = *it;
		dict[to_variant(key)] = to_variant(value);
	}
	return dict;
}

}