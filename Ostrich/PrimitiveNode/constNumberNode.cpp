// PrimitiveNode.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "constNumberNode.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		class impl_constNumberNode {
		public:
			double _value;

			impl_constNumberNode() {
				_value = 0;
			}
		};
	}
}


hv::v2::constNumberNode::constNumberNode(std::string name) : hv::v2::constNode(name, 2){


		this->_instance = std::make_unique<hv::v2::impl_constNumberNode>();

}

hv::v2::constNumberNode::~constNumberNode() {

}

void hv::v2::constNumberNode::init() {
	START_ERROR_HANDLE()

	END_ERROR_HANDLE(__FUNCTION__, __LINE__)
}


double hv::v2::constNumberNode::data() {
	return this->_instance->_value;
}

void hv::v2::constNumberNode::data(double value) {
	this->_instance->_value = value;
}


std::string hv::v2::constNumberNode::serialization() {

	return std::to_string(this->_instance->_value);
}

void hv::v2::constNumberNode::deserialization(std::string value) {
	this->_instance->_value = std::stod(value);
}
