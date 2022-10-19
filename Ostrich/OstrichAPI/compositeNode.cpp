#include "compositeNode.h"

#include "macro.h"
#include "commonException.h"
#include "icontext.h"



#include <unordered_map>



namespace hv {
	namespace v2 {
		class impl_compositeNode {
		public:

			int _depth;
			std::size_t _uid;
			bool _isFreezed;
			bool _isEventNode;


			std::unordered_map<std::string, std::shared_ptr<hv::v2::iconstNode>> _inputNodes;
			std::unordered_map<std::string, std::shared_ptr<hv::v2::iconstNode>> _outputNodes;



			hv::v2::icontext * _context;


			impl_compositeNode() {

				this->_depth = 0;
				this->_uid = 0;

				this->_isFreezed = false;
				this->_isEventNode = false;
				this->_context = nullptr;
			}


		};
	}
}

hv::v2::compositeNode::compositeNode(std::string value, int type, hv::v2::ihandle * context) : hv::v2::node(value, type) {

	this->_instance = std::make_unique<hv::v2::impl_compositeNode>();

	if (context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid node context");
		throw hv::v2::oexception(message);
	}

	this->_instance->_context = (hv::v2::icontext *)context;
}

hv::v2::compositeNode::~compositeNode() {


}




std::string hv::v2::compositeNode::name() {

	return hv::v2::node::name();
}



int hv::v2::compositeNode::type() {
	return hv::v2::node::type();
}


std::size_t hv::v2::compositeNode::uid() {
	return hv::v2::node::uid();
}
void hv::v2::compositeNode::uid(std::size_t value) {
	hv::v2::node::uid(value);
}


bool hv::v2::compositeNode::isFreezed() {
	return this->_instance->_isFreezed;
}

void hv::v2::compositeNode::isFreezed(bool value) {
	this->_instance->_isFreezed = value;
}


bool hv::v2::compositeNode::isEventNode() {
	return this->_instance->_isEventNode;
}

void hv::v2::compositeNode::isEventNode(bool check) {
	this->_instance->_isEventNode = check;
}


int hv::v2::compositeNode::depth() {
	return this->_instance->_depth;
}

void hv::v2::compositeNode::depth(int value) {
	this->_instance->_depth = value;

}

bool hv::v2::compositeNode::isConnected() {
	for (auto node : this->_instance->_inputNodes) {
		if (node.second->isConnected() == true)
			return true;
	}

	return false;
}

bool hv::v2::compositeNode::isConditionalNode() {

	for (auto& node : this->_instance->_inputNodes) {
		if (node.second->type() == (int)hv::v2::objectType::CONST_EXECUTION)
			return true;
	}

	for (auto& node : this->_instance->_outputNodes) {
		if (node.second->type() == (int)hv::v2::objectType::CONST_EXECUTION)
			return true;
	}

	return false;
}


bool hv::v2::compositeNode::checkSourceUID(std::size_t uid) {
	for (auto node : this->_instance->_inputNodes) {
		if (node.second->sourceUID() == uid && node.second->isConnected() == true)
			return true;
	}

	return false;
}


std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::inputs() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> nodes;

	for (auto& node : this->_instance->_inputNodes) {
		nodes.push_back(node.second);
	}

	return nodes;

}

std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::outputs() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> nodes;

	for (auto& node : this->_instance->_outputNodes) {
		nodes.push_back(node.second);
	}

	return nodes;
}

std::shared_ptr<hv::v2::iconstNode> hv::v2::compositeNode::input(std::string key) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_inputNodes.find(key) == this->_instance->_inputNodes.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid output key");
		throw hv::v2::oexception(message);
	}

	auto constNode = this->_instance->_inputNodes[key];
	return constNode;
}

std::shared_ptr<hv::v2::iconstNode> hv::v2::compositeNode::output(std::string key) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	
	if (this->_instance->_outputNodes.find(key) == this->_instance->_outputNodes.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid output key");
		throw hv::v2::oexception(message);
	}

	auto constNode = this->_instance->_outputNodes[key];
	return constNode;
}

std::vector<std::size_t> hv::v2::compositeNode::constUID() {
	std::vector<std::size_t> uid;

	for (auto node : this->_instance->_inputNodes) {
		uid.push_back(node.second->uid());
	}

	for (auto node : this->_instance->_outputNodes) {
		uid.push_back(node.second->uid());
	}

	return uid;
}



std::shared_ptr<hv::v2::iconstNode> hv::v2::compositeNode::search(std::string key, int objectType, hv::v2::searchType type) {


	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (objectType <= (int)hv::v2::objectType::CONST_NODE && objectType >= (int)hv::v2::objectType::COMPOSITE_NODE) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid object type");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		throw hv::v2::oexception(message);
	}


	try {

		switch (type)
		{
		case hv::v2::searchType::input: {
			if (this->_instance->_inputNodes.find(key) == this->_instance->_inputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Name is not exist");
				throw hv::v2::oexception(message);
			}
			auto constNode = this->_instance->_inputNodes[key];
			if (constNode->isConnected() == false) {
				return constNode;
			}

			auto sourceUID = constNode->sourceUID();
			auto sourceName = constNode->sourceName();


			auto connectedConstNode = this->_instance->_context->find(sourceUID, sourceName, this->depth(), 9999);
			return connectedConstNode;

			break;
		}
		case hv::v2::searchType::output: {
			if (this->_instance->_outputNodes.find(key) == this->_instance->_outputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Name is not exist");
				throw hv::v2::oexception(message);
			}

			auto constNode = this->_instance->_outputNodes[key];
			return constNode;
			break;
		}

		default:
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid search type");
			throw hv::v2::oexception(message);
			break;
		}

	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}


void hv::v2::compositeNode::registerNode(std::string key, int objectType, hv::v2::searchType type) {


	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (objectType <= (int)hv::v2::objectType::CONST_NODE && objectType >= (int)hv::v2::objectType::COMPOSITE_NODE) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid object type");
		throw hv::v2::oexception(message);
	}


	if (this->_instance->_context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		throw hv::v2::oexception(message);

	}

	try {
		switch (type)
		{
		case hv::v2::searchType::input: {
			if (this->_instance->_inputNodes.find(key) != this->_instance->_inputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			auto node = this->_instance->_context->create(key, objectType, 9999);
			this->_instance->_inputNodes[key] = node;
			break;
		}
			
		case hv::v2::searchType::output: {
			if (this->_instance->_outputNodes.find(key) != this->_instance->_outputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			auto node = this->_instance->_context->create(key, objectType, 9999);
			this->_instance->_outputNodes[key] = node;
			break;
		}
		default:
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid search type");
			throw hv::v2::oexception(message);
			break;
		}
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}

void hv::v2::compositeNode::registerExecutionNode(std::string key, hv::v2::searchType type) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		throw hv::v2::oexception(message);

	}

	try {
		switch (type)
		{
		case hv::v2::searchType::input: {
			if (this->_instance->_inputNodes.find(key) != this->_instance->_inputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}

			auto node = this->_instance->_context->create(key, (int)hv::v2::objectType::CONST_EXECUTION, 9999);
			this->_instance->_inputNodes[key] = node;
			break;
		}

		case hv::v2::searchType::output: {
			if (this->_instance->_outputNodes.find(key) != this->_instance->_outputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			

			auto node = this->_instance->_context->create(key, (int)hv::v2::objectType::CONST_EXECUTION, 9999);
			this->_instance->_outputNodes[key] = node;
			break;
		}
		default:
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid search type");
			throw hv::v2::oexception(message);
			break;
		}
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}


std::shared_ptr<hv::v2::irunable> hv::v2::compositeNode::execution(std::string key) {

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		throw hv::v2::oexception(message);

	}

	try {

		return this->_instance->_context->findExecution(this->uid(), key, this->depth(), 9999);
		
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}

