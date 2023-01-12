#include "commonException.h"
#include "compositeRandomNoiseImageNode.h"
#include "constImageNode.h"

#include <random>

namespace hv {
	namespace v2 {
		class impl_compositeRandomNoiseImageNode {
		public:

			impl_compositeRandomNoiseImageNode() {

			}

		};
	}
}


hv::v2::compositeRandomNoiseImageNode::compositeRandomNoiseImageNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50011, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeRandomNoiseImageNode>();
	try {
		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerExecutionNode("Exec", hv::v2::searchType::output);
		this->registerNode("random", 3, hv::v2::searchType::result);

		auto random = this->search<hv::v2::constImageNode>("random", 3, hv::v2::searchType::result);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}

hv::v2::compositeRandomNoiseImageNode::~compositeRandomNoiseImageNode() {

}


void hv::v2::compositeRandomNoiseImageNode::init() {
	START_ERROR_HANDLE()
		auto random = this->search<hv::v2::constImageNode>("random", 3, hv::v2::searchType::result);
		random->clear();
	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeRandomNoiseImageNode::process() {

	START_ERROR_HANDLE()
		auto random = this->search<hv::v2::constImageNode>("random", 3, hv::v2::searchType::result);
		auto exec = this->execution("Exec");

		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_int_distribution<int> dis(0, 9999);

		if (random->size() != 100000) {
			random->create(100, 100, 1, 1, hv::v2::alignType::normal);

			for (int index = 0; index < 500; index++) {
				unsigned char* buffer = (unsigned char *)random->data();
				buffer[dis(gen)] = 255;
			}
		}

		this->updateConst(3, random->uid());

		return exec->call();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)

}
