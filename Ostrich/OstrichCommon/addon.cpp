#include "addon.h"


#include "iconstructor.h"
#include "macro.h"


#include <unordered_map>

namespace hv {
	namespace v2 {
		class impl_addon {
		public:

			std::unordered_map<int, std::shared_ptr<hv::v2::ivarConstructor>> _var_constructor_table;
			std::unordered_map<int, std::shared_ptr<hv::v2::iconstConstructor>> _const_constructor_table;

			std::vector<std::shared_ptr<hv::v2::nodeInfo>> _information;

			impl_addon() {

			}

			~impl_addon() {

			}

		};
	}


}


hv::v2::addon::addon() {
	this->_instance = std::make_unique<hv::v2::impl_addon>();
}

hv::v2::addon::~addon() {

}

bool hv::v2::addon::exist(int type) {

	bool existVarConstructor = false;
	bool existConstConstructor = false;


	if (this->_instance->_var_constructor_table.find(type) != this->_instance->_var_constructor_table.end()) {
		existVarConstructor = true;
	}

	if (this->_instance->_const_constructor_table.find(type) != this->_instance->_const_constructor_table.end()) {
		existConstConstructor = true;
	}


	if (existVarConstructor == true || existConstConstructor == true)
		return true;


	return false;
}



//varConstructor
std::shared_ptr<hv::v2::ivarConstructor> hv::v2::addon::varConstructor(int type) {

	if (this->_instance->_var_constructor_table.find(type) == this->_instance->_var_constructor_table.end()) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type is not exist");
		throw hv::v2::oexception(message);
	}

	try {

		return this->_instance->_var_constructor_table[type];

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
}

void hv::v2::addon::varConstructor(int type, std::shared_ptr<hv::v2::ivarConstructor> _constructor) {

	if (this->_instance->_var_constructor_table.find(type) != this->_instance->_var_constructor_table.end()) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type already exist in this addon");
		throw hv::v2::oexception(message);
	}

	this->_instance->_var_constructor_table[type] = _constructor;
}


//constConstructor
std::shared_ptr<hv::v2::iconstConstructor> hv::v2::addon::constConstructor(int type) {

	if (this->_instance->_const_constructor_table.find(type) == this->_instance->_const_constructor_table.end()) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type is not exist");
		throw hv::v2::oexception(message);
	}

	try {

		return this->_instance->_const_constructor_table[type];

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
}

void hv::v2::addon::constConstructor(int type, std::shared_ptr<hv::v2::iconstConstructor> _constructor) {

	if (this->_instance->_const_constructor_table.find(type) != this->_instance->_const_constructor_table.end()) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type already exist in this addon");
		throw hv::v2::oexception(message);
	}

	this->_instance->_const_constructor_table[type] = _constructor;
}




void  hv::v2::addon::information(std::shared_ptr<hv::v2::nodeInfo> info) {
	this->_instance->_information.push_back(info);
}

std::shared_ptr<hv::v2::addon> hv::v2::addon::createAddon() {
	std::shared_ptr<hv::v2::addon> _addon(new hv::v2::addon());
	return _addon;
}

std::vector<std::shared_ptr<hv::v2::nodeInfo>> hv::v2::addon::information() {
	return this->_instance->_information;
}