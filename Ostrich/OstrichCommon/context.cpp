#include "context.h"
#include "commonException.h"
#include "macro.h"


#include <unordered_map>
#include <Windows.h>
#include <random>
#include <algorithm>


namespace hv {
	namespace v2 {

		class impl_context {
		public:

			std::unordered_map< std::size_t, std::shared_ptr<hv::v2::ivarNode>> _var_node_look_up_table;
			std::unordered_map<std::size_t, std::shared_ptr<hv::v2::iconstNode>> _const_node_loook_up_table;

			std::unordered_map<std::string, HMODULE> _addon_handles;
			std::vector<hv::v2::addon_info> _addon_info;
			std::string _libraryPath;
			std::vector<std::shared_ptr<hv::v2::iaddon>> _addons;

			unsigned int _max_task_count;


			impl_context() {

			}


			~impl_context() {

			}

		};
	}
}


hv::v2::context::context() {


	this->_instance = std::make_unique<hv::v2::impl_context>();



}

hv::v2::context::~context() {

}

std::shared_ptr<hv::v2::ivarNode> hv::v2::context::search(std::size_t uid) {


	return nullptr;
}

std::shared_ptr<hv::v2::ivarNode> hv::v2::context::search(std::string nick) {

	return nullptr;
}


void hv::v2::context::connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {


}
void hv::v2::context::connect(std::shared_ptr<hv::v2::ivarNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) {


}

void hv::v2::context::disonnect(std::string nick) {


}
void hv::v2::context::disconnect(std::size_t targetUID, std::string targetName) {


}
void hv::v2::context::disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) {


}
void hv::v2::context::disconnect(std::size_t targetUID) {


}
void hv::v2::context::disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode) {


}



std::shared_ptr<hv::v2::ivarNode> hv::v2::context::addNode(std::string name, int objectType) {


	return nullptr;
}
void hv::v2::context::removeNode(std::size_t uid) {


}
void hv::v2::context::removeNode(std::shared_ptr<hv::v2::ivarNode> node) {


}
void hv::v2::context::removeNode(std::string nick) {


}

void hv::v2::context::verification() {


}
void hv::v2::context::clear() {


}

int hv::v2::context::maxDepth() {

	return 0;
}
void hv::v2::context::maxDepth(int value) {


}

std::string hv::v2::context::serialization() {

	return "";

}
void hv::v2::context::deserialization(std::string value) {


}


void hv::v2::context::loadLibrary() {

}

void hv::v2::context::unloadLibrary() {

}

void hv::v2::context::setAddonPath(std::string path) {

}

std::vector<hv::v2::addon_info> hv::v2::context::addonInfo() {
	std::vector<hv::v2::addon_info> temp;

	return temp;
}

std::vector<std::shared_ptr<hv::v2::iaddon>> hv::v2::context::addons() {
	std::vector<std::shared_ptr<hv::v2::iaddon>> temp;
	return temp;
}



void hv::v2::context::load(std::string context, hv::v2::contentType contentType) {

}

void hv::v2::context::save(std::string path) {

}

void hv::v2::context::initNodes() {

}

void hv::v2::context::setMaxTaskCount(int num) {

}

void hv::v2::context::run(hv::v2::syncType sync) {

}



// Private Function

std::size_t hv::v2::context::generate_const_unique_key() {
	std::random_device rd;
	std::mt19937_64 mersenne(rd());
	std::uniform_int_distribution<unsigned long long int> dice(1, INT64_MAX);


	unsigned long long unique_id = 0;

	do {
		unique_id = dice(rd);
		if (unique_id == 0)
			continue;
	} while (this->_instance->_const_node_loook_up_table.find(unique_id) != this->_instance->_const_node_loook_up_table.end());


	return unique_id;
}


std::size_t hv::v2::context::generate_var_unique_key() {

	std::random_device rd;
	std::mt19937_64 mersenne(rd());
	std::uniform_int_distribution<unsigned long long int> dice(1, INT64_MAX);


	unsigned long long unique_id = 0;

	do {
		unique_id = dice(rd);
		if (unique_id == 0)
			continue;
	} while (this->_instance->_var_node_look_up_table.find(unique_id) != this->_instance->_var_node_look_up_table.end());


	return unique_id;
}




// Node Special Lock Down
void hv::v2::context::registerAddon(std::shared_ptr<hv::v2::iaddon> addon, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (addon == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid addon.");
		throw hv::v2::oexception(message);
	}


	this->_instance->_addons.push_back(addon);

}




std::shared_ptr<hv::v2::iconstNode> hv::v2::context::create(std::string name, int objectType, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (name.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}


	try {
		for (auto addon : this->_instance->_addons) {
			if (addon->exist(objectType) == true) {

				auto uid = this->generate_const_unique_key();
				auto constructor = addon->constConstructor(objectType);
				auto node = constructor->create(name);
				node->uid(uid);

				return node;
			}
		}

		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Can't find object type");
		throw hv::v2::oexception(message);

	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}


std::shared_ptr<hv::v2::iconstNode> hv::v2::context::find(std::size_t uid, std::string name, int depth, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (name.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_var_node_look_up_table.find(uid) == this->_instance->_var_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "uid is not exist");
		throw hv::v2::oexception(message);
	}


	try {

		auto node = this->_instance->_var_node_look_up_table[uid];

		if (node->depth() >= depth) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invaliid graph depth");
			throw hv::v2::oexception(message);
		}

		auto const_output = node->output(name);

		return const_output;
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}


}