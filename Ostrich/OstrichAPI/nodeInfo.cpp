#include "nodeInfo.h"


namespace hv {
	namespace v2 {
		class impl_nodeInfo {
		public:
			impl_nodeInfo() {
				this->name = "";
				this->category = "";
				this->type = -1;
			}

			~impl_nodeInfo() {

			}

			std::string name;
			std::string category;
			int type;

		};
	}
}


hv::v2::nodeInfo::nodeInfo(std::string name, std::shared_ptr<hv::v2::argument> arg) {


	try {
		this->_instance = std::make_unique<hv::v2::impl_nodeInfo>();
		this->_instance->name = name;
		this->_instance->category = arg->get<std::string>("category");
		this->_instance->type = arg->get<int>("type");
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}

hv::v2::nodeInfo::~nodeInfo() {

}

std::string hv::v2::nodeInfo::category() {
	return this->_instance->category;
}

std::string hv::v2::nodeInfo::name() {
	return this->_instance->name;
}

int hv::v2::nodeInfo::type() {

	return this->_instance->type;
}