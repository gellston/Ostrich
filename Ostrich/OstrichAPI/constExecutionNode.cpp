// PrimitiveNode.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//


#include "constExecutionNode.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		class impl_constExecutionNode {
		public:
			double _value;

			impl_constExecutionNode() {
				_value = 0;
			}
		};
	}
}


hv::v2::constExecutionNode::constExecutionNode(std::string name) : hv::v2::constNode(name, (int)hv::v2::objectType::CONST_EXECUTION) {


	this->_instance = std::make_unique<hv::v2::impl_constExecutionNode>();

}

hv::v2::constExecutionNode::~constExecutionNode() {

}

void hv::v2::constExecutionNode::init() {

}

std::shared_ptr<hv::v2::iconstNode> hv::v2::constExecutionNode::clone() {
	auto object = std::make_shared<hv::v2::constExecutionNode>(this->name());
	object->uid(this->uid());
	object->isConnected(this->isConnected());
	object->sourceName(this->sourceName());
	object->sourceUID(this->sourceUID());
	object->index(this->index());
	return object;
}