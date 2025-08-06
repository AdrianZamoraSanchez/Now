#pragma once
#include <string>
#include <unordered_map>

enum class Type {
	type_int, 
	type_float,
	type_char, 
	type_string,
	type_void, 
	type_bool
};

/* Translation functions */
Type getTypeFromString(const std::string& typeStr);
std::string getStringFromType(Type type);
