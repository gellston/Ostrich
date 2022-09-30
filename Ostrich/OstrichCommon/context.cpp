#include "context.h"
#include "commonException.h"


#include <unordered_map>
#include <Windows.h>


namespace hv {
	namespace v2 {

		class impl_context {
		public:

			std::unordered_map < std::size_t, std::shared_ptr<hv::v2::ivarNode>> _node_look_up_table;
			std::unordered_map<std::string, HMODULE> _addon_handles;


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

std::shared_ptr<hv::v2::inode> hv::v2::context::search(std::size_t uid) {


	return nullptr;
}

std::shared_ptr<hv::v2::inode> hv::v2::context::search(std::string nick) {

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



void hv::v2::context::registerAddon(std::shared_ptr<hv::v2::iaddon> addon) {

}