
#include "diagram.h"
#include "context.h"

#include <unordered_map>
#include <map>
#include <filesystem>

namespace hv {
	namespace v2 {
		class impl_diagram {


		public:
			
			std::map<std::string, std::shared_ptr<hv::v2::icontext>> _contextes;
			std::string _addon_path;


			int _executionDelay;

			impl_diagram() {
				this->_addon_path = "";
				this->_executionDelay = 0;

			}


		};
	}
}



hv::v2::diagram::diagram() {
	try {
		_instance = std::make_unique<hv::v2::impl_diagram>();
	}
	catch (std::exception e) {
		throw e;
	}
}

hv::v2::diagram::~diagram() {
	this->_instance->_contextes.clear();
}



void hv::v2::diagram::registerProcessCompleteEvent(std::string context_name, std::function<void(int nodeType, std::size_t composite_uid)> eventHandler) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->registerProcessCompleteEvent(eventHandler);

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
void hv::v2::diagram::registerConstChangedEvent(std::string context_name, std::function<void(int nodeType, std::size_t constUID)> eventHandler) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->registerConstChangedEvent(eventHandler);

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

void hv::v2::diagram::registerProcessStartEvent(std::string context_name, std::function<void(int nodeType, std::size_t constUID)> eventHandler) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->registerProcessStartEvent(eventHandler);

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

void hv::v2::diagram::registerErrorEvent(std::string context_name, std::function<void(int nodeType, std::size_t composuteUID, const char * message)> eventHandler) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->registerErrorEvent(eventHandler);


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


void hv::v2::diagram::resetProcessStartEvent(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->resetProcessStartEvent();

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


void hv::v2::diagram::resetProcessCompleteEvent(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->resetProcessCompleteEvent();

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
void hv::v2::diagram::resetConstChangedEvent(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->resetConstChangedEvent();

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


void hv::v2::diagram::resetErrorEvent(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->resetErrorEvent();
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

void hv::v2::diagram::updateAllConstNode(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->updateAllConstNode();

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





std::shared_ptr<hv::v2::icompositeNode> hv::v2::diagram::search(std::string context_name, std::size_t uid) {
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
std::shared_ptr<hv::v2::icompositeNode> hv::v2::diagram::search(std::string context_name, std::string name) {
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


bool hv::v2::diagram::checkConnectability(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {
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


void hv::v2::diagram::connect(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {
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
void hv::v2::diagram::connect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {
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

void hv::v2::diagram::disconnect(std::string context_name, std::string name) {
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
void hv::v2::diagram::disconnect(std::string context_name, std::size_t targetUID, std::string targetName) {
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
void hv::v2::diagram::disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {
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
void hv::v2::diagram::disconnect(std::string context_name, std::size_t targetUID) {
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
void hv::v2::diagram::disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode) {
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

std::shared_ptr<hv::v2::icompositeNode> hv::v2::diagram::addNode(std::string context_name, std::string name, int objetType) {
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
void hv::v2::diagram::removeNode(std::string context_name, std::size_t uid) {
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
void hv::v2::diagram::removeNode(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> node) {
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
void hv::v2::diagram::removeNode(std::string context_name, std::string name) {
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

std::shared_ptr<hv::v2::iconstNode> hv::v2::diagram::constNode(std::string context_name, std::size_t uid) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		return this->_instance->_contextes[context_name]->constNode(uid);
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

void hv::v2::diagram::verification(std::string context_name) {
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
void hv::v2::diagram::clear(std::string context_name) {
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
void hv::v2::diagram::loadLibrary(std::string context_name) {
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
void hv::v2::diagram::unloadLibrary(std::string context_name) {
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
void hv::v2::diagram::loadLibrary() {
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
void hv::v2::diagram::unloadLibrary() {
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
void hv::v2::diagram::setAddonPath(std::string path) {

	if (std::filesystem::exists(path) == false) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Addon path is not exists");
		throw hv::v2::oexception(message);
	}

	this->_instance->_addon_path = path;
}


void hv::v2::diagram::executionDelay(int ms) {
	this->_instance->_executionDelay = ms;

	for (auto& context : this->_instance->_contextes) {
		context.second->executionDelay(this->_instance->_executionDelay);
	}
}

int hv::v2::diagram::executionDelay() {
	return this->_instance->_executionDelay;
}

std::vector<hv::v2::addon_info> hv::v2::diagram::addonInfo(std::string context_name) {
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

std::vector<std::shared_ptr<hv::v2::iaddon>> hv::v2::diagram::addons(std::string context_name) {
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

void hv::v2::diagram::load(std::string context_name, std::string path) {
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
void hv::v2::diagram::save(std::string context_name, std::string path) {
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
void hv::v2::diagram::initNodes(std::string context_name) {
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
void hv::v2::diagram::run(std::string context_name, std::size_t uid) {
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
void hv::v2::diagram::run(std::string context_name, int objectType, std::string name) {
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
void hv::v2::diagram::run(std::string context_name) {
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

void hv::v2::diagram::stop(std::string context_name) {
	try {
		if (this->_instance->_contextes.find(context_name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is not exists");
			throw hv::v2::oexception(message);
		}

		this->_instance->_contextes[context_name]->stop();

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



std::shared_ptr<hv::v2::icontext> hv::v2::diagram::context(std::string name) {


	try {
		if (this->_instance->_contextes.find(name) == this->_instance->_contextes.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "context is already exists");
			throw hv::v2::oexception(message);
		}
		return this->_instance->_contextes[name];
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

void hv::v2::diagram::createContext(std::string name) {

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

void hv::v2::diagram::renameContext(std::string sourceName, std::string targetName) {

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

void hv::v2::diagram::removeContext(std::string name) {
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

void hv::v2::diagram::copyContext(std::string sourceName, std::string targetName) {
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

std::string hv::v2::diagram::serialization(std::string context) {
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

void hv::v2::diagram::deserialization(std::string context, std::string jsonContext) {
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