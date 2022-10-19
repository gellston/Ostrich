#include "compositeStartNode.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_compositeStartNode {
		public:

			impl_compositeStartNode() {

			}

		};
	}
}


hv::v2::compositeStartNode::compositeStartNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50002,  context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeStartNode>();

	this->isEventNode(true);

	try {
		this->registerExecutionNode("Exec", hv::v2::searchType::output);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeStartNode ::~compositeStartNode() {

}


void hv::v2::compositeStartNode::init() {
	START_ERROR_HANDLE()

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeStartNode::process() {
	START_ERROR_HANDLE()

		auto execution = this->execution("Exec");
		return execution->process();


	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}