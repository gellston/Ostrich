#include "compositeAddNumberNode.h"
#include "commonException.h"
#include "constNumberNode.h"

namespace hv {
	namespace v2 {
		class impl_compositeAddNumberNode {
		public:

			impl_compositeAddNumberNode() {

			}

		};
	}
}


hv::v2::compositeAddNumberNode::compositeAddNumberNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50006, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeAddNumberNode>();

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

hv::v2::compositeAddNumberNode::~compositeAddNumberNode() {

}


void hv::v2::compositeAddNumberNode::init() {
	START_ERROR_HANDLE()
		auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);
		y->data(0);
	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeAddNumberNode::process() {

	START_ERROR_HANDLE()

		auto x1 = this->search<hv::v2::constNumberNode>("x1", 2, hv::v2::searchType::input);
		auto x2 = this->search<hv::v2::constNumberNode>("x2", 2, hv::v2::searchType::input);
		auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);

		y->data(x1->data() + x2->data());

		this->update();

		auto execution = this->execution("Exec");
		return execution->call();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)

}

