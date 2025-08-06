#include "Type.h"
#include <stdexcept>

const std::unordered_map<std::string, Type> codeToTypes = {
	{"int", Type::type_int},
	{"float", Type::type_float},
	{"char", Type::type_char},
	{"string", Type::type_string},
	{"void", Type::type_void},
	{"bool", Type::type_bool}
};

/* Translation functions */
Type getTypeFromString(const std::string& typeStr) {
    auto it = codeToTypes.find(typeStr);

    if (it != codeToTypes.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Invalid type");
    }
}

std::string getStringFromType(Type type) {
    switch (type) {
        case Type::type_int: return "int";
        case Type::type_float: return "float"; 
        case Type::type_char: return "char";
        case Type::type_string: return "string";
		case Type::type_void: return "void";
        case Type::type_bool: return "bool";
        default: return "unknown";
    }
}
