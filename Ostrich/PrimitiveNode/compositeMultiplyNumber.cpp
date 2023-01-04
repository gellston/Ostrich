#include "compositeMultiplyNumberNode.h"
#include "commonException.h"
#include "constNumberNode.h"

namespace hv {
	namespace v2 {
		class impl_compositeMultiplyNumberNode {
		public:

			impl_compositeMultiplyNumberNode() {

			}

		};
	}
}


hv::v2::compositeMultiplyNumberNode::compositeMultiplyNumberNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50009, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeMultiplyNumberNode>();

	try {

		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerExecutionNode("Exec", hv::v2::searchType::output);


		this->registerNode("x1", 2, hv::v2::searchType::input);
		this->registerNode("x2", 2, hv::v2::searchType::input);
		this->registerNode("y", 2, hv::v2::searchType::output);

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeMultiplyNumberNode::~compositeMultiplyNumberNode() {

}


void hv::v2::compositeMultiplyNumberNode::init() {
	START_ERROR_HANDLE()
		auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);
	y->data(0);
	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeMultiplyNumberNode::process() {

	START_ERROR_HANDLE()

	auto x1 = this->search<hv::v2::constNumberNode>("x1", 2, hv::v2::searchType::input);
	auto x2 = this->search<hv::v2::constNumberNode>("x2", 2, hv::v2::searchType::input);
	auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);

	y->data(x1->data() * x2->data());

	this->updateConst(y->type(), y->uid());

	auto execution = this->execution("Exec");
	return execution->call();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)

}

