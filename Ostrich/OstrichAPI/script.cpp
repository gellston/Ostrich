
#include "script.h"
#include "context.h"

#include <unordered_map>
#include <map>
#include <filesystem>

namespace hv {
	namespace v2 {
		class impl_script {


		public:
			
			std::map<std::string, std::shared_ptr<hv::v2::icontext>> _contextes;
			std::string _addon_path;

			impl_script() {
				this->_addon_path = "";

			}


		};
	}
}



hv::v2::script::script() {
	try {
		_instance = std::make_unique<hv::v2::impl_script>();
	}
	catch (std::exception e) {
		throw e;
	}
}

hv::v2::script::~script() {
	this->_instance->_contextes.clear();
}

std::shared_ptr<hv::v2::icompositeNode> hv::v2::script::search(std::string context_name, std::size_t uid) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		return this->_instance->_contextes[context_name]->search(uid);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
std::shared_ptr<hv::v2::icompositeNode> hv::v2::script::search(std::string context_name, std::string name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		return this->_instance->_contextes[context_name]->search(name);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}


bool hv::v2::script::checkConnectability(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			return false;
		}

		return this->_instance->_contextes[context_name]->checkConnectability(sourceUID, sourceName, targetUID, targetName);
	}
	catch (hv::v2::oexception e) {
		return false;
	}
	catch (std::exception e) {
		return false;
	}
}


void hv::v2::script::connect(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->connect(sourceUID, sourceName, targetUID, targetName);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::connect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->connect(sourceNode, sourceName, targetNode, targetName);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::disconnect(std::string context_name, std::string name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->disconnect(name);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::disconnect(std::string context_name, std::size_t targetUID, std::string targetName) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->disconnect(targetUID, targetName);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->disconnect(targetNode, targetName);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::disconnect(std::string context_name, std::size_t targetUID) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->disconnect(targetUID);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->disconnect(targetNode);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

std::shared_ptr<hv::v2::icompositeNode> hv::v2::script::addNode(std::string context_name, std::string name, int objetType) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		return this->_instance->_contextes[context_name]->addNode(name, objetType);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::removeNode(std::string context_name, std::size_t uid) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->removeNode(uid);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::removeNode(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> node) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->removeNode(node);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::removeNode(std::string context_name, std::string name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->removeNode(name);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::verification(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->verification();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::clear(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->clear();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::loadLibrary(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->loadLibrary();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::unloadLibrary(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->unloadLibrary();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::loadLibrary() {
	try {
		for (auto& context : this->_instance->_contextes) {
			context.second->loadLibrary();
		}
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::unloadLibrary() {
	try {
		for (auto& context : this->_instance->_contextes) {
			context.second->unloadLibrary();
		}
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::setAddonPath(std::string path) {

	if (std::filesystem::exists(path) == false) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Addon path is not exists");
		throw hv::v2::oexception(message);
	}

	this->_instance->_addon_path = path;
}

std::vector<hv::v2::addon_info> hv::v2::script::addonInfo(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
		}

		return this->_instance->_contextes[context_name]->addonInfo();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

std::vector<std::shared_ptr<hv::v2::iaddon>> hv::v2::script::addons(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		return this->_instance->_contextes[context_name]->addons();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::load(std::string context_name, std::string path) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->load(path);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::save(std::string context_name, std::string path) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->save(path);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::initNodes(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->initNodes();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::run(std::string context_name, std::size_t uid) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->run(uid);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::run(std::string context_name, int objectType, std::string name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->run(objectType, name);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}
void hv::v2::script::run(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->run();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}


void hv::v2::script::createContext(std::string name) {

	try {

		if (name.length() == 0) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid context name");
			throw hv::v2::oexception(message);
		}


		if (this->_instance->_contextes.find(name) != this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is already exists");
			throw hv::v2::oexception(message);
		}

		auto context = std::make_shared<hv::v2::context>();
		context->setAddonPath(this->_instance->_addon_path);
		context->loadLibrary();

		this->_instance->_contextes[name] = context;

	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::renameContext(std::string sourceName, std::string targetName) {

	try {

		if (sourceName.length() == 0 || targetName.length() == 0) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid context name");
			throw hv::v2::oexception(message);
		}


		if (this->_instance->_contextes.find(sourceName) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "source context is not exists");
			throw hv::v2::oexception(message);
		}

		if (this->_instance->_contextes.find(targetName) != this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "target context is already exists");
			throw hv::v2::oexception(message);
		}



		auto context = this->_instance->_contextes[sourceName];
		this->_instance->_contextes.erase(sourceName);
		this->_instance->_contextes[targetName] = context;

	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}

void hv::v2::script::removeContext(std::string name) {
	try {

		if (name.length() == 0) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid context name");
			throw hv::v2::oexception(message);
		}


		if (this->_instance->_contextes.find(name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "source context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[name]->unloadLibrary();
		this->_instance->_contextes.erase(name);


	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::copyContext(std::string sourceName, std::string targetName) {
	try {


		if (sourceName.length() == 0 || targetName.length() == 0) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid context name");
			throw hv::v2::oexception(message);
		}

		if (this->_instance->_contextes.find(sourceName) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "source context is not exists");
			throw hv::v2::oexception(message);
		}

		if (this->_instance->_contextes.find(targetName) != this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "target context is already exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[targetName] = this->_instance->_contextes[sourceName]->clone();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

std::string hv::v2::script::serialization(std::string context) {
	try {
		if (this->_instance->_contextes.find(context) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}


		return this->_instance->_contextes[context]->serialization();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::script::deserialization(std::string context, std::string jsonContext) {
	try {
		if (this->_instance->_contextes.find(context) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}
		this->_instance->_contextes[context]->deserialization(jsonContext);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}