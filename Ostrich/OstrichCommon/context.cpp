#include "context.h"


namespace hv {
	namespace v2 {

		class impl_context {
		public:

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