#include "compositeNode.h"

#include "macro.h"
#include "commonException.h"
#include "icontext.h"
#include "raii.h"


#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <thread>

namespace hv {
	namespace v2 {
		class impl_compositeNode {
		public:

			int _depth;
			std::size_t _uid;
			bool _isFreezed;
			bool _isEventNode;
			bool _isCustomNode;
			bool _hasError;


			std::unordered_map<std::string, std::shared_ptr<hv::v2::iconstNode>> _inputNodes;
			std::unordered_map<std::string, std::shared_ptr<hv::v2::iconstNode>> _outputNodes;
			std::unordered_map<std::string, std::shared_ptr<hv::v2::iconstNode>> _results;


			hv::v2::icontext * _context;


			impl_compositeNode() {

				this->_depth = 0;
				this->_uid = 0;

				this->_isFreezed = false;
				this->_isEventNode = false;
				this->_isCustomNode = false;
				this->_context = nullptr;

				this->_hasError = false;
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

	this->_instance->_inputNodes.clear();
	this->_instance->_outputNodes.clear();
	this->_instance->_results.clear();

	this->_instance->_inputNodes.rehash(0);
	this->_instance->_outputNodes.rehash(0);
	this->_instance->_results.rehash(0);

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

bool hv::v2::compositeNode::isCustomNode() {
	return this->_instance->_isCustomNode;
}

void hv::v2::compositeNode::isCustomNode(bool check) {
	this->_instance->_isCustomNode = check;
}

int hv::v2::compositeNode::depth() {
	return this->_instance->_depth;
}

void hv::v2::compositeNode::depth(int value) {
	this->_instance->_depth = value;

}

bool hv::v2::compositeNode::hasError() {
	return this->_instance->_hasError;
}

void hv::v2::compositeNode::hasError(bool error) {
	this->_instance->_hasError = error;
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


hv::v2::resultType hv::v2::compositeNode::call() {

	if (this->_instance->_context == nullptr) {
		this->hasError(true);
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		this->_instance->_context->onError(this->type(), this->uid(), message.data());
		throw hv::v2::oexception(message);
	}

	try {

		this->hasError(false);

		//Process start check
		this->_instance->_context->onProcessStart(this->type(), this->uid());

		//Process complte check with raii
		hv::v2::raii raii([&]() {
			this->_instance->_context->onProcessComplete(this->type(), this->uid());
		});

		if (this->_instance->_context->isStop(9999) == true)
			return hv::v2::resultType::exit;

		std::this_thread::sleep_for(std::chrono::milliseconds(this->_instance->_context->executionDelay()));
		auto result = this->process();

		//Const Node output updating
		for (auto & constNode : this->_instance->_outputNodes) {
			this->_instance->_context->onConstChanged(constNode.second->type(), constNode.second->uid());
		}

		return result;
	}
	catch (hv::v2::oexception e) {
		this->hasError(true);
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		this->_instance->_context->onError(this->type(), this->uid(), message.data());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::compositeNode::updateConst(int nodeType, std::size_t uid) {

	if (this->_instance->_context == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null context exception");
		throw hv::v2::oexception(message);
	}

	START_ERROR_HANDLE();
	this->_instance->_context->onConstChanged(nodeType, uid);

	END_ERROR_HANDLE(__FUNCTION__, __LINE__);
}



bool hv::v2::compositeNode::checkSourceUID(std::size_t uid) {
	for (auto node : this->_instance->_inputNodes) {
		if (node.second->isMultiple() == false) {
			if (node.second->sourceUID() == uid && node.second->isConnected() == true)
				return true;
		}
		else {
			auto multipleNodes = node.second->multipleSourceNode();
			if (node.second->isConnected() == true) {
				for (auto& multiNode : multipleNodes) {
					auto _uid = std::get<0>(multiNode);
					if (_uid == uid)
						return true;
				}
			}
		}
	}

	return false;
}


std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::inputs() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> nodes;

	for (auto& node : this->_instance->_inputNodes) {
		nodes.push_back(node.second);
	}

	std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<hv::v2::iconstNode> &first,
										     const std::shared_ptr<hv::v2::iconstNode> &second) {
			return first->index() < second->index();
	});

	return nodes;

}





std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::outputs() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> nodes;

	for (auto& node : this->_instance->_outputNodes) {
		nodes.push_back(node.second);
	}

	std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<hv::v2::iconstNode>& first,
											 const std::shared_ptr<hv::v2::iconstNode>& second) {
			return first->index() < second->index();
	});

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

void hv::v2::compositeNode::replaceInputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs) {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& node : this->_instance->_inputNodes) {
		group.push_back(node.second);
	}
	this->_instance->_context->removeConstNodeGroup(group, 9999);
	this->_instance->_inputNodes.clear();
	this->_instance->_inputNodes.rehash(0);

	for (auto& input : inputs) {
		this->_instance->_inputNodes[input->name()] = input;
	}
}

void hv::v2::compositeNode::replaceOuputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs) {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& node : this->_instance->_outputNodes) {
		group.push_back(node.second);
	}
	this->_instance->_context->removeConstNodeGroup(group, 9999);
	this->_instance->_outputNodes.clear();
	this->_instance->_outputNodes.rehash(0);

	for (auto& output : outputs) {
		this->_instance->_outputNodes[output->name()] = output;
	}
}

std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::inputClone() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& constNode : this->_instance->_inputNodes) {
		group.push_back(constNode.second->clone());
	}

	return group;
}
std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::outputClone() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& constNode : this->_instance->_outputNodes) {
		group.push_back(constNode.second->clone());
	}

	return group;
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

std::vector<std::size_t> hv::v2::compositeNode::inputConstUID() {
	std::vector<std::size_t> uid;

	for (auto node : this->_instance->_inputNodes) {
		uid.push_back(node.second->uid());
	}

	return uid;
}

std::vector<std::size_t> hv::v2::compositeNode::outputConstUID() {
	std::vector<std::size_t> uid;

	for (auto node : this->_instance->_outputNodes) {
		uid.push_back(node.second->uid());
	}

	return uid;
}

std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::searchMultipleNode(std::string key, int objectType, hv::v2::searchType type) {

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

			if (constNode->isMultiple() == false) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Its single node, can't use searchMultipleNode function");
				throw hv::v2::oexception(message);
			}

			std::vector<std::shared_ptr<hv::v2::iconstNode>> result;
			if (constNode->isConnected() == false) {
				result.push_back(constNode);
				return result;
			}

			auto multipleInfo = constNode->multipleSourceNode();

			for (auto & _multipleInfo : multipleInfo) {
				auto _uid = std::get<0>(_multipleInfo);
				auto _name = std::get<1>(_multipleInfo);
				auto connectedConstNode = this->_instance->_context->find(_uid, _name, this->depth(), 9999);
				result.push_back(connectedConstNode);
			}

			return result;

			break;
		}
		case hv::v2::searchType::output: {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "searchMultipleNode function is not for output");
			throw hv::v2::oexception(message);
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

			if (constNode->isMultiple() == true) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "It's multiple node, can't use search function");
				throw hv::v2::oexception(message);
			}


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
		case hv::v2::searchType::result: {
			if (this->_instance->_results.find(key) == this->_instance->_results.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Name is not exist");
				throw hv::v2::oexception(message);
			}

			auto constNode = this->_instance->_results[key];
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
			node->index((int)this->_instance->_inputNodes.size() + 1);
			this->_instance->_inputNodes[key] = node;
			break;
		}
			
		case hv::v2::searchType::output: {
			if (this->_instance->_outputNodes.find(key) != this->_instance->_outputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			auto node = this->_instance->_context->create(key, objectType, 9999);
			node->index((int)this->_instance->_outputNodes.size() + 1);
			this->_instance->_outputNodes[key] = node;
			break;
		}
		case hv::v2::searchType::result: {
			if (this->_instance->_results.find(key) != this->_instance->_results.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			auto node = this->_instance->_context->create(key, objectType, 9999);
			node->index((int)this->_instance->_results.size() + 1);
			this->_instance->_results[key] = node;
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


void hv::v2::compositeNode::registerMultipleNode(std::string key, int objectType, hv::v2::searchType type) {

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
			node->index((int)this->_instance->_inputNodes.size() + 1);
			node->isMultiple(true);
			this->_instance->_inputNodes[key] = node;
			break;
		}

		case hv::v2::searchType::output: {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "It's multiple node, can't use searchMultipleNode function");
			throw hv::v2::oexception(message);
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
			node->index((int)this->_instance->_inputNodes.size() + 1);
			this->_instance->_inputNodes[key] = node;
			break;
		}

		case hv::v2::searchType::output: {
			if (this->_instance->_outputNodes.find(key) != this->_instance->_outputNodes.end()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Exist node key");
				throw hv::v2::oexception(message);
			}
			

			auto node = this->_instance->_context->create(key, (int)hv::v2::objectType::CONST_EXECUTION, 9999);
			node->index((int)this->_instance->_outputNodes.size() + 1);
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



std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::results() {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> nodes;

	for (auto& node : this->_instance->_results) {
		nodes.push_back(node.second);
	}

	std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<hv::v2::iconstNode>& first,
		const std::shared_ptr<hv::v2::iconstNode>& second) {
			return first->index() < second->index();
	});

	return nodes;

}


std::shared_ptr<hv::v2::iconstNode> hv::v2::compositeNode::result(std::string key) {
	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_results.find(key) == this->_instance->_results.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid result key");
		throw hv::v2::oexception(message);
	}

	auto constNode = this->_instance->_results[key];
	return constNode;
}


void hv::v2::compositeNode::replaceResults(std::vector<std::shared_ptr<hv::v2::iconstNode>> result) {

	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& node : this->_instance->_results) {
		group.push_back(node.second);
	}
	this->_instance->_context->removeConstNodeGroup(group, 9999);
	this->_instance->_results.clear();
	this->_instance->_results.rehash(0);

	for (auto& input : result) {
		this->_instance->_results[input->name()] = input;
	}
}

std::vector<std::shared_ptr<hv::v2::iconstNode>> hv::v2::compositeNode::resultsClone() {
	std::vector<std::shared_ptr<hv::v2::iconstNode>> group;
	for (auto& constNode : this->_instance->_results) {
		group.push_back(constNode.second->clone());
	}

	return group;
}




void hv::v2::compositeNode::removeConstNode(std::string key, hv::v2::searchType type) {



	if (this->isCustomNode() == false) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "its not custom node.");
		throw hv::v2::oexception(message);
	}


	try {

		switch (type)
		{
		case hv::v2::searchType::input:{
			auto constNode = this->input(key);
			this->_instance->_context->removeConstNode(constNode, 9999);
			this->_instance->_inputNodes.erase(key);
			break;
		}
		case hv::v2::searchType::output:{
			auto constNode = this->output(key);
			this->_instance->_context->removeConstNode(constNode, 9999);
			this->_instance->_outputNodes.erase(key);
			break;
		}
		case hv::v2::searchType::result: {
			auto constNode = this->result(key);
			this->_instance->_context->removeConstNode(constNode, 9999);
			this->_instance->_results.erase(key);

			break;
		}
		default:
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid search type");
			throw hv::v2::oexception(message);
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



void hv::v2::compositeNode::addConstNode(std::string key, int objectType, hv::v2::searchType type) {
	try {

		if (this->isCustomNode() == false) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "its not custom node.");
			throw hv::v2::oexception(message);
		}

		this->registerNode(key, objectType, type);

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
void hv::v2::compositeNode::addConstMultipleNode(std::string key, int objectType, hv::v2::searchType type) {
	try {


		if (this->isCustomNode() == false) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "its not custom node.");
			throw hv::v2::oexception(message);
		}

		this->registerMultipleNode(key, objectType, type);

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
void hv::v2::compositeNode::addConstExecutionNode(std::string key, int objecType, hv::v2::searchType type) {
	try {

		if (this->isCustomNode() == false) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "its not custom node.");
			throw hv::v2::oexception(message);
		}

		this->registerExecutionNode(key, type);

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