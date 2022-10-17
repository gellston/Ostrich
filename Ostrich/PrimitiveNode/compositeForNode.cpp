#include "compositeForNode.h"
#include "commonException.h"
#include "constNumberNode.h"


namespace hv {
	namespace v2 {
		class impl_compositeForNode {
		public:

			impl_compositeForNode() {

			}

		};
	}
}


hv::v2::compositeForNode::compositeForNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50004, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeForNode>();

	try {
		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerNode("count", 2, hv::v2::searchType::input);


		this->registerExecutionNode("Loop", hv::v2::searchType::output);
		this->registerExecutionNode("Complete", hv::v2::searchType::output);
		this->registerNode("index", 2, hv::v2::searchType::output);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeForNode::~compositeForNode() {

}


void hv::v2::compositeForNode::init() {
	try {

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}

void hv::v2::compositeForNode::process() {

	try {

		auto count = this->search<hv::v2::constNumberNode>("count", 2, hv::v2::searchType::input);
		auto index = this->search<hv::v2::constNumberNode>("index", 2, hv::v2::searchType::output);

		auto loop = this->execution("Loop");
		auto complete = this->execution("Complete");
		auto _max_iternation = count->data();
		for (double _index = 0; _index < _max_iternation; _index+= 1.0) {
			try {
				std::cout << "for loop counting : " << _index << std::endl;
				index->data(_index);
				loop->process();
			}
			catch (hv::v2::oexception e) {
				throw e;
			}
			catch (std::exception e) {
				throw e;
			}
		}

		complete->process();

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}
}