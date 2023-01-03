#include "compositeSumNumberNode.h"
#include "commonException.h"
#include "constNumberNode.h"

namespace hv {
	namespace v2 {
		class impl_compositeSumNumberNode {
		public:

			impl_compositeSumNumberNode() {

			}

		};
	}
}


hv::v2::compositeSumNumberNode::compositeSumNumberNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50007, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeSumNumberNode>();

	try {

		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerExecutionNode("Exec", hv::v2::searchType::output);
		this->registerMultipleNode("x", 2, hv::v2::searchType::input);
		this->registerNode("y", 2, hv::v2::searchType::output);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeSumNumberNode::~compositeSumNumberNode() {

}


void hv::v2::compositeSumNumberNode::init() {
	START_ERROR_HANDLE()
		auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);
		y->data(0);
	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeSumNumberNode::process() {

	START_ERROR_HANDLE()

		auto multipleX = this->searchMultipleNode<hv::v2::constNumberNode>("x", 2, hv::v2::searchType::input);
		auto y = this->search<hv::v2::constNumberNode>("y", 2, hv::v2::searchType::output);

		double sum = 0;

		for (auto component : multipleX) {
			sum += component->data();
		}

		y->data(sum);
		this->updateConst(y->type(), y->uid());

		auto execution = this->execution("Exec");
		return execution->call();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

