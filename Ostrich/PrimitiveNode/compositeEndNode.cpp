#include "compositeEndNode.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_compositeEndNode {
		public:

			impl_compositeEndNode() {

			}

		};
	}
}


hv::v2::compositeEndNode::compositeEndNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50003, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeEndNode>();

	try {
		this->registerExecutionNode("Exec", hv::v2::searchType::input);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeEndNode::~compositeEndNode() {

}


void hv::v2::compositeEndNode::init() {
	try {

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}

void hv::v2::compositeEndNode::process() {
	try {


	
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}