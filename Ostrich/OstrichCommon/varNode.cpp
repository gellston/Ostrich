#include "varNode.h"

#include "macro.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_varNode {
		public:

			int _depth;
			std::size_t _uid;
			bool _inCondition;
			bool _isConditionalNode;


			std::vector<std::shared_ptr<hv::v2::iconstNode>> _inputs;
			std::vector<std::shared_ptr<hv::v2::iconstNode>> _outputs;


			std::shared_ptr<hv::v2::icontext> _context;


			impl_varNode() {

				this->_depth = 0;
				this->_uid = 0;
				this->_depth = -1;

				this->_inCondition = false;
				this->_isConditionalNode = false;
			}


		};
	}
}

hv::v2::varNode::varNode(std::string value, int type, std::shared_ptr<hv::v2::icontext> context) : hv::v2::node(value, type) {

	this->_instance = std::make_unique<hv::v2::impl_varNode>();

	if (context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid node context");
		throw hv::v2::oexception(message);
	}

	this->_instance->_context = context;
}

hv::v2::varNode::~varNode() {


}


bool hv::v2::varNode::inCondition() {
	return this->_instance->_inCondition;

}

void hv::v2::varNode::inCondition(bool value) {
	this->_instance->_inCondition = value;
}



void hv::v2::varNode::isConditionalNode(bool value) {
	this->_instance->_isConditionalNode = value;
}

bool hv::v2::varNode::isConditionalNode() {
	return this->_instance->_isConditionalNode;
}

int hv::v2::varNode::depth() {
	return this->_instance->_depth;
}

void hv::v2::varNode::depth(int value) {
	this->_instance->_depth = value;

}



std::size_t hv::v2::varNode::uid() {
	return this->_instance->_uid;
}

void hv::v2::varNode::uid(std::size_t value) {

	if (value == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid uid");
		throw hv::v2::oexception(message);
	}

	this->_instance->_uid = value;
}


std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::varNode::inputs() {
	return this->_instance->_inputs;
}

std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::varNode::outputs() {
	return this->_instance->_outputs;
}

std::shared_ptr<hv::v2::iconstNode> hv::v2::varNode::input(std::string key) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	std::shared_ptr<hv::v2::iconstNode> temp;

	return temp;
}

std::shared_ptr<hv::v2::iconstNode> hv::v2::varNode::output(std::string key) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	std::shared_ptr<hv::v2::iconstNode> temp;


	return temp;
}



std::shared_ptr<hv::v2::iconstNode> hv::v2::varNode::searchNode(std::string key, int objectType, hv::v2::searchType type) {


	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (objectType > (int)hv::v2::objectType::CONST_NODE && objectType < (int)hv::v2::objectType::VAR_NODE) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid object type");
		throw hv::v2::oexception(message);
	}



	std::shared_ptr<hv::v2::iconstNode> temp;

	return temp;

}


void hv::v2::varNode::registerNode(std::string key, int objectType, hv::v2::searchType type) {


	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (objectType > (int)hv::v2::objectType::CONST_NODE && objectType < (int)hv::v2::objectType::VAR_NODE) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid object type");
		throw hv::v2::oexception(message);
	}


}

