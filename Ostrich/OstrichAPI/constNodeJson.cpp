#include "constNodeJson.h"
#include "commonException.h"

#include <nlohmann/json.hpp>

namespace hv {
	namespace v2 {
		class impl_constNodeJson {
		public:
			nlohmann::json _json;
		};
	}
}


hv::v2::constNodeJson::constNodeJson(std::string json) {
	try {
		this->_instance = std::make_unique<hv::v2::impl_constNodeJson>();
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

hv::v2::constNodeJson::~constNodeJson() {

}

void hv::v2::constNodeJson::add(std::string key, int integer) {
	this->_instance->_json[key] = integer;
}

void hv::v2::constNodeJson::add(std::string key, double number) {
	this->_instance->_json[key] = number;
}

void hv::v2::constNodeJson::add(std::string key, std::string content) {
	this->_instance->_json[key] = content;
}



double hv::v2::constNodeJson::number(std::string key) {
	return this->_instance->_json[key].get<double>();
}
int hv::v2::constNodeJson::integer(std::string key) {
	return this->_instance->_json[key].get<int>();
}
std::string hv::v2::constNodeJson::context(std::string key) {
	return this->_instance->_json[key].get<std::string>();
}