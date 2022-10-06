// PrimitiveNode.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include "constNumberNode.h"


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


hv::v2::constNumberNode::constNumberNode(std::string name) : hv::v2::constNode(name, 1){


		this->_instance = std::make_unique<hv::v2::impl_constNumberNode>();

}

hv::v2::constNumberNode::~constNumberNode() {

}

void hv::v2::constNumberNode::init() {

}

double hv::v2::constNumberNode::data() {
	return this->_instance->_value;
}

void hv::v2::constNumberNode::data(double value) {
	this->_instance->_value = value;
}