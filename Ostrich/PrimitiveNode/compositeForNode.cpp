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
	START_ERROR_HANDLE()

		auto index = this->search<hv::v2::constNumberNode>("index", 2, hv::v2::searchType::output);
		index->data(0);

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}

hv::v2::resultType hv::v2::compositeForNode::process() {

	START_ERROR_HANDLE()

		auto count = this->search<hv::v2::constNumberNode>("count", 2, hv::v2::searchType::input);
		auto index = this->search<hv::v2::constNumberNode>("index", 2, hv::v2::searchType::output);

		auto loop = this->execution("Loop");
		auto complete = this->execution("Complete");
		auto _max_iternation = count->data();
		for (double _index = 0; _index < _max_iternation; _index += 1.0) {
			try {

				index->data(_index);
				this->updateConst(index->type(), index->uid());
				
				auto result = loop->call();
				switch (result)
				{
				case hv::v2::resultType::continue_:
					continue;
					break;
				case hv::v2::resultType::break_:
					break;
					break;
				case hv::v2::resultType::exit:
					return hv::v2::resultType::exit;
					break;
				case hv::v2::resultType::done:
					break;
				default:
					break;
				}
			}
			catch (hv::v2::oexception e) {
				throw e;
			}
			catch (std::exception e) {
				throw e;
			}
		}

		return complete->call();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)

}
