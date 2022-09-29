#include "node.h"


#include "macro.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_node {
		public:
			std::string _name;
			std::string _nick;
			int _type;

			impl_node() {
				_name = "";
				_type = -1;
				_nick = "";

			}
		};
	}
}


hv::v2::node::node(std::string value, int type){


	this->_instance = std::make_unique<hv::v2::impl_node>();



	if (value.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid node name");
		throw hv::v2::oexception(message);
	}

	if (type > (int)hv::v2::objectType::VAR_NODE && type < (int)hv::v2::objectType::DEVICE_NODE) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid object type");
		throw hv::v2::oexception(message);
	}



	this->_instance->_type = type;
	this->_instance->_name = value;

}

hv::v2::node::~node() {

}


std::string hv::v2::node::name() {

	return this->_instance->_name;
}



int hv::v2::node::type() {
	return this->_instance->_type;
}


std::string hv::v2::node::nick() {
	return this->_instance->_nick;
}

void hv::v2::node::nick(std::string value) {

	if (value.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid nick name");
		throw hv::v2::oexception(message);
	}
	this->_instance->_nick = value;
}