#include "compositeSleepNode.h"
#include "commonException.h"
#include "constNumberNode.h"


#include <chrono>
#include <thread>

namespace hv {
	namespace v2 {
		class impl_compositeSleepNode {
		public:

			impl_compositeSleepNode() {

			}

		};
	}
}


hv::v2::compositeSleepNode::compositeSleepNode(std::string name, hv::v2::ihandle* context) : hv::v2::compositeNode(name, 50005, context) {

	this->_instance = std::unique_ptr<hv::v2::impl_compositeSleepNode>();


	try {


		this->registerExecutionNode("Exec", hv::v2::searchType::input);
		this->registerExecutionNode("Exec", hv::v2::searchType::output);



		this->registerNode("us", 2, hv::v2::searchType::input);


	}
	catch (hv::v2::oexception e) {
		throw e;
	}
	catch (std::exception e) {
		throw e;
	}

}

hv::v2::compositeSleepNode::~compositeSleepNode() {

}


void hv::v2::compositeSleepNode::init() {
	START_ERROR_HANDLE()

	END_ERROR_HANDLE(__FUNCTION__, __LINE__);
}

void hv::v2::compositeSleepNode::process() {

	START_ERROR_HANDLE()


	auto time = this->search<hv::v2::constNumberNode>("us", 2, hv::v2::searchType::input);
	auto execution = this->execution("Exec");


	std::this_thread::sleep_for(std::chrono::milliseconds((long long)time->data()));

	execution->process();

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)

}