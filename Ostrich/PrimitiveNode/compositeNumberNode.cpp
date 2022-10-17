#include "compositeNumberNode.h"
#include "commonException.h"
#include "constNumberNode.h"

namespace hv {
	namespace v2 {
		class impl_compositeNumberNode {
		public:

			impl_compositeNumberNode() {

			}

		};
	}
}


hv::v2::compositeNumberNode::compositeNumberNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50001,  context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeNumberNode>();


	try {


		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerExecutionNode("Exec", hv::v2::searchType::output);



		this->registerNode("input", 2, hv::v2::searchType::input);
		this->registerNode("output", 2, hv::v2::searchType::output);

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeNumberNode::~compositeNumberNode() {

}


void hv::v2::compositeNumberNode::init() {
	try {

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}

void hv::v2::compositeNumberNode::process() {
	try {

		auto input = this->search<hv::v2::constNumberNode>("input", 2, hv::v2::searchType::input);
		auto output = this->search<hv::v2::constNumberNode>("output", 2, hv::v2::searchType::output);


		output->data(input->data());


		auto execution = this->execution("Exec");
		execution->process();



	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}