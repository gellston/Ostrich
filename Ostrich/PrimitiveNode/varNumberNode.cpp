#include "varNumberNode.h"
#include "commonException.h"
#include "constNumberNode.h"

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


	try {
		this->registerNode("input", 1, hv::v2::searchType::input);
		this->registerNode("output", 1, hv::v2::searchType::output);

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

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

		auto input = this->search<hv::v2::constNumberNode>("input", 1, hv::v2::searchType::input);
		auto output = this->search<hv::v2::constNumberNode>("output", 1, hv::v2::searchType::output);


		output->data(input->data());


	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}