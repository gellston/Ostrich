#include "varNumberNode.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		class impl_varNumberNode {
		public:

			impl_varNumberNode() {

			}

		};
	}
}


hv::v2::varNumberNode::varNumberNode(std::string name, hv::v2::ihandle* context) : hv::v2::varNode(name, 50001,  context) {

	this->_instance = std::unique_ptr<hv::v2::impl_varNumberNode>();

}

hv::v2::varNumberNode::~varNumberNode() {

}


void hv::v2::varNumberNode::init() {
	try {

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}

void hv::v2::varNumberNode::process() {

	try {

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}