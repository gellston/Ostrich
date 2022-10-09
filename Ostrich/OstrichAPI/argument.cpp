#include "argument.h"
#include "macro.h"

#include <map>
#include <fmt/core.h>
#include <iostream>


namespace hv {
	namespace v2 {
		class impl_argument {
		public:
			std::map<std::string, hv::v2::arg> table;
			impl_argument() {

			}

			~impl_argument() {

			}
		};

		struct variant_string_converter {
			variant_string_converter() {}

			std::string operator()(std::string value) {
				return value;
			}
			std::string operator()(bool value) {
				return value == true ? "true" : "false";
			}
			std::string operator()(int value) {
				return std::to_string(value);
			}
			std::string operator()(double value) {
				return std::to_string(value);
			}
		};
	}
}


hv::v2::argument::argument() : _instance(new hv::v2::impl_argument()) {

}

hv::v2::argument::argument(std::initializer_list<std::tuple<std::string, hv::v2::arg>> list) : _instance(new hv::v2::impl_argument()) {

}

hv::v2::argument::~argument() {

}



template<> double hv::v2::argument::get(std::string key) {
	try {

		if (this->_instance->table.find(key) == this->_instance->table.end()) {

			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Key is not exists");
			throw  hv::v2::oexception(message);
		}

		return std::get<double>(this->_instance->table[key]);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw  hv::v2::oexception(message);
	}
}

template<> int hv::v2::argument::get(std::string key) {
	try {

		if (this->_instance->table.find(key) == this->_instance->table.end()) {

			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Key is not exists");
			throw  hv::v2::oexception(message);
		}

		return std::get<int>(this->_instance->table[key]);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw  hv::v2::oexception(message);
	}
}

template<> std::string hv::v2::argument::get(std::string key) {
	try {

		if (this->_instance->table.find(key) == this->_instance->table.end()) {

			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Key is not exists");
			throw  hv::v2::oexception(message);
		}

		return std::get<std::string>(this->_instance->table[key]);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw  hv::v2::oexception(message);
	}
}

template<> bool hv::v2::argument::get(std::string key) {
	try {

		if (this->_instance->table.find(key) == this->_instance->table.end()) {

			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Key is not exists");
			throw  hv::v2::oexception(message);
		}

		return std::get<bool>(this->_instance->table[key]);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw  hv::v2::oexception(message);
	}
}


template<> void hv::v2::argument::add(std::string key, double value) {
	try {
		this->_instance->table[key] = value;
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw hv::v2::oexception(message);
	}
}

template<> void hv::v2::argument::add(std::string key, int value) {
	try {
		this->_instance->table[key] = value;
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw hv::v2::oexception(message);
	}
}

template<> void hv::v2::argument::add(std::string key, std::string value) {
	try {
		this->_instance->table[key] = value;
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw hv::v2::oexception(message);
	}
}

template<> void hv::v2::argument::add(std::string key, bool value) {
	try {
		this->_instance->table[key] = value;
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw hv::v2::oexception(message);
	}
}

template<> void hv::v2::argument::add(std::string key, const char* value) {
	try {
		this->_instance->table[key] = std::string(value);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key or access");
		throw hv::v2::oexception(message);
	}
}

std::string hv::v2::argument::parse() {

	std::string content = "";

	content += "{\n";
	for (auto& pair : this->_instance->table) {
		std::string key = pair.first;
		std::string value = std::visit(hv::v2::variant_string_converter{}, pair.second);
		std::string temp = fmt::format("\t[{0},{1}]", key, value);
		temp += "\n";
		content += temp;
	}
	content += "}\n";

	return content;
}

void hv::v2::argument::print() {
	std::string content = "";

	content += "{\n";
	for (auto& pair : this->_instance->table) {
		std::string key = pair.first;
		std::string value = std::visit(hv::v2::variant_string_converter{}, pair.second);
		std::string temp = fmt::format("\t[{0},{1}]", key, value);
		temp += "\n";
		content += temp;
	}
	content += "}\n";

	std::cout << content << std::endl;
}