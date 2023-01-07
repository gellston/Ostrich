#include "context.h"
#include "commonException.h"
#include "macro.h"
#include "contextStatus.h"
#include "objectType.h"
#include "constExecutionNode.h"

#include <unordered_map>
#include <Windows.h>
#include <random>
#include <algorithm>
#include <filesystem>
#include <future>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <concurrent_vector.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <streambuf>


namespace hv {
	namespace v2 {

		class impl_context {
		public:

			std::unordered_map<std::size_t, std::shared_ptr<hv::v2::icompositeNode>> _composite_node_look_up_table;
			std::unordered_map<std::size_t, std::shared_ptr<hv::v2::iconstNode>> _const_node_loook_up_table;
			std::unordered_map<std::size_t, std::vector<std::shared_ptr<hv::v2::icompositeNode>>> _align_nodes;
			std::unordered_map<int, int> _addon_type_overlap_table;



			std::vector<std::shared_ptr<hv::v2::icompositeNode>> _event_nodes;



			std::unordered_map<std::string, HMODULE> _addon_handles;
			std::vector<hv::v2::addon_info> _addon_info;
			std::string _libraryPath;
			std::vector<std::shared_ptr<hv::v2::iaddon>> _addons;




			int _depth;
			int _executionDelay = 0;

			//Event Handler poiner
			std::function<void(int nodeType, std::size_t composite_uid)> _processCompleteEvent;
			std::function<void(int nodeType, std::size_t constUID)> _constChangedEvent;
			std::function<void(int nodeType, std::size_t composite_uid)> _processStartEvent;
			std::function<void(int nodeType, std::size_t composite_uid, std::string message)> _errorEvent;


			volatile bool _isStop = false;
			

			impl_context() {

				_depth = 0;
				_executionDelay = 0;

				_isStop = false;
			}


			~impl_context() {

			}

		};
	}
}


hv::v2::context::context() {


	this->_instance = std::make_unique<hv::v2::impl_context>();

	this->resetConstChangedEvent();
	this->resetProcessCompleteEvent();
	this->resetProcessStartEvent();
	this->resetErrorEvent();

}

hv::v2::context::~context() {



	try {

		this->resetConstChangedEvent();
		this->resetProcessCompleteEvent();
		this->resetProcessStartEvent();
		this->resetErrorEvent();


		this->unloadLibrary();
	}
	catch (hv::v2::oexception e) {
		std::cout << e.what() << std::endl;
	}
}



void hv::v2::context::onProcessComplete(int nodeType, std::size_t composite_uid) {

	try {
		this->_instance->_processCompleteEvent(nodeType, composite_uid);
	}
	catch (std::exception e) {

	}

}


void hv::v2::context::onProcessStart(int nodeType, std::size_t composite_uid) {
	try {
		this->_instance->_processStartEvent(nodeType, composite_uid);
	}
	catch (std::exception e) {

	}
}




void hv::v2::context::onConstChanged(int nodeType, std::size_t constUID) {

	this->_instance->_constChangedEvent(nodeType, constUID);
}


void hv::v2::context::onError(int nodeType, std::size_t composite_uid, std::string message) {
	this->_instance->_errorEvent(nodeType, composite_uid, message);
}


void hv::v2::context::registerProcessCompleteEvent(std::function<void(int nodeType, std::size_t composite_uid)> eventHandler) {
	this->_instance->_processCompleteEvent = eventHandler;
}
void hv::v2::context::registerConstChangedEvent(std::function<void(int nodeType, std::size_t constUID)> eventHandler) {
	this->_instance->_constChangedEvent = eventHandler;
}

void hv::v2::context::registerProcessStartEvent(std::function<void(int nodeType, std::size_t composite_uid)> eventHandler) {
	this->_instance->_processStartEvent = eventHandler;
}

void hv::v2::context::registerErrorEvent(std::function<void(int nodeType, std::size_t composite_uid, std::string message)> eventHandler) {
	this->_instance->_errorEvent = eventHandler;
}


void hv::v2::context::resetConstChangedEvent() {

	this->_instance->_constChangedEvent=[&](int nodeType, std::size_t constUID){

	};
}

void hv::v2::context::resetProcessCompleteEvent() {
	this->_instance->_processCompleteEvent = [&](int nodeType, std::size_t composite_uid) {

	};
}

void hv::v2::context::resetProcessStartEvent() {
	this->_instance->_processStartEvent = [&](int nodeType, std::size_t composite_uid) {

	};
}

void hv::v2::context::resetErrorEvent() {
	this->_instance->_errorEvent = [&](int nodeType, std::size_t composite_uid, std::string message) {

	};
}

void hv::v2::context::updateAllConstNode() {
	for (auto& node : this->_instance->_const_node_loook_up_table) {
		this->_instance->_constChangedEvent(node.second->type(), node.second->uid());
	}
}


std::shared_ptr<hv::v2::icompositeNode> hv::v2::context::search(std::size_t uid) {
	if (this->_instance->_composite_node_look_up_table.find(uid) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
		throw hv::v2::oexception(message);
	}

	return this->_instance->_composite_node_look_up_table[uid];
}

std::shared_ptr<hv::v2::icompositeNode> hv::v2::context::search(std::string name) {
	bool found = false;
	std::shared_ptr<hv::v2::icompositeNode> temp_node;
	for (auto &node : this->_instance->_composite_node_look_up_table) {
		if (node.second->name() == name) {
			found = true;
			temp_node = node.second;
			break;
		}
	}

	return temp_node;
}


void hv::v2::context::connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {
	


	try {

		auto sourceNode = this->search(sourceUID);
		auto targetNode = this->search(targetUID);

		this->connect(sourceNode, sourceName, targetNode, targetName);

	}
	catch (hv::v2::oexception e) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}


}



void hv::v2::context::connect(std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {

	if (sourceNode == targetNode) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "source and target node are same");
		throw hv::v2::oexception(message);
	}

	if (sourceNode == nullptr || targetNode == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null reference node");
		throw hv::v2::oexception(message);
	}


	try {

		std::stack<std::size_t> current_node_stack;
		auto inputNodes = sourceNode->inputs();

		for (auto& node : inputNodes) {
			if (node->isConnected() == true && node->isMultiple() == false) {
				current_node_stack.push(node->sourceUID());
			}

			if (node->isConnected() == true && node->isMultiple() == true) {
				auto multipleNodes = node->multipleSourceNode();
				for (auto& multipleNode : multipleNodes) {
					auto _uid = std::get<0>(multipleNode);
					current_node_stack.push(_uid);
				}
			}
		}

		while (current_node_stack.empty() != true) {
			auto _currentUID = current_node_stack.top();
			current_node_stack.pop();

			auto _currentSourceNode = this->search(_currentUID);
			if (_currentSourceNode == targetNode) {
				std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Its a circular node relationship");
				throw hv::v2::oexception(message);
			}

			auto _currentInputNodes = _currentSourceNode->inputs();
			for (auto& node : _currentInputNodes) {
				if (node->isConnected() == true && node->isMultiple() == false) {
					current_node_stack.push(node->sourceUID());
				}

				if (node->isConnected() == true && node->isMultiple() == true) {
					auto multipleNodes = node->multipleSourceNode();
					for (auto& multipleNode : multipleNodes) {
						auto _uid = std::get<0>(multipleNode);
						current_node_stack.push(_uid);
					}
				}
			}
		}



		auto sourceConstNode = sourceNode->output(sourceName);
		auto targetConstNode = targetNode->input(targetName);


		if (sourceConstNode->type() != targetConstNode->type()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type is not match");
			throw hv::v2::oexception(message);
		}


		// Flow Node Connection Check
		for (auto& pair : this->_instance->_composite_node_look_up_table) {

			if (pair.second->checkSourceUID(sourceNode->uid()) == true) {
				auto inputs = pair.second->inputs();
				for (auto& input : inputs) {
					if (input->type() == (int)hv::v2::objectType::CONST_EXECUTION) {
						if (input->sourceName() == sourceName && input->isConnected() == true && input->sourceUID() == sourceNode->uid()) {
							auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Execution node already connected");
							throw hv::v2::oexception(message);
						}
					}
				}
			}	
		}
		// Flow Node Connection Check




		if (targetConstNode->isMultiple()) {
			targetConstNode->registerMultipleSourceNode(sourceNode->uid(), sourceName);
			targetConstNode->isConnected(true);
		}
		else {
			targetConstNode->sourceName(sourceName);
			targetConstNode->sourceUID(sourceNode->uid());
			targetConstNode->isConnected(true);
		}

		


		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

		//Search Event Node
		this->searchingEventNode();
		

	}
	catch (hv::v2::oexception e) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}



bool hv::v2::context::checkConnectability(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {

	try {
		auto sourceNode = this->search(sourceUID);
		auto targetNode = this->search(targetUID);


		if (sourceNode == targetNode) {
			return false;
		}

		if (sourceNode == nullptr || targetNode == nullptr) {
			return false;
		}


		try {

			std::stack<std::size_t> current_node_stack;
			auto inputNodes = sourceNode->inputs();

			for (auto& node : inputNodes) {
				if (node->isConnected() == true && node->isMultiple() == false) {
					current_node_stack.push(node->sourceUID());
				}

				if (node->isConnected() == true && node->isMultiple() == true) {
					auto multipleNodes = node->multipleSourceNode();
					for (auto& multipleNode : multipleNodes) {
						auto _uid = std::get<0>(multipleNode);
						current_node_stack.push(_uid);
					}
				}

			}

			while (current_node_stack.empty() != true) {
				auto _currentUID = current_node_stack.top();
				current_node_stack.pop();

				auto _currentSourceNode = this->search(_currentUID);
				if (_currentSourceNode == targetNode) {
					return false;
				}

				auto _currentInputNodes = _currentSourceNode->inputs();
				for (auto& node : _currentInputNodes) {
					if (node->isConnected() == true && node->isMultiple() == false) {
						current_node_stack.push(node->sourceUID());
					}

					if (node->isConnected() == true && node->isMultiple() == true) {
						auto multipleNodes = node->multipleSourceNode();
						for (auto& multipleNode : multipleNodes) {
							auto _uid = std::get<0>(multipleNode);
							current_node_stack.push(_uid);
						}
					}
				}
			}



			auto sourceConstNode = sourceNode->output(sourceName);
			auto targetConstNode = targetNode->input(targetName);


			if (sourceConstNode->type() != targetConstNode->type()) {
				return false;
			}


			// Flow Node Connection Check
			for (auto& pair : this->_instance->_composite_node_look_up_table) {

				if (pair.second->checkSourceUID(sourceNode->uid()) == true) {
					auto inputs = pair.second->inputs();
					for (auto& input : inputs) {
						if (input->type() == (int)hv::v2::objectType::CONST_EXECUTION) {
							if (input->sourceName() == sourceName && input->isConnected() == true && input->sourceUID() == sourceNode->uid()) {
								return false;
							}
						}
					}
				}
			}
			// Flow Node Connection Check

		}
		catch (hv::v2::oexception e) {
			return false;
		}
	}
	catch (std::exception e) {
		return false;
	}

	return true;
}


void hv::v2::context::disconnect(std::string name) {

	try {
		for (auto node : this->_instance->_composite_node_look_up_table) {
			if (node.second->name() == name) {
				auto inputs = node.second->inputs();
				for (auto input : inputs) {
					input->clearMultipleSourceNode();
					input->isConnected(false);
				}

				//Depth 정렬
				this->sortingDepth();

				//Depth 순으로 그룹핑
				this->groupingDepth();

				//Search Event Node
				this->searchingEventNode();
			}
		}
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}

void hv::v2::context::disconnect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) {


	if (this->_instance->_composite_node_look_up_table.find(targetUID) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
		throw hv::v2::oexception(message);
	}

	try {


		for (auto node : this->_instance->_composite_node_look_up_table) {
			if (node.second->uid() == targetUID) {
				auto inputs = node.second->inputs();
				for (auto input : inputs) {
					if (input->name() == targetName && input->isMultiple() == true) {
						input->unRegisterMultipleSourceNode(sourceUID, sourceName);
						auto multipleNode = input->multipleSourceNode();
						if (multipleNode.size() == 0) {
							input->isConnected(false);
						}
					}

					if (input->name() == targetName && input->isMultiple() == false) {
						input->isConnected(false);
					}
				}

				//Depth 정렬
				this->sortingDepth();

				//Depth 순으로 그룹핑
				this->groupingDepth();

				//Search Event Node
				this->searchingEventNode();
			}
		}
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}

void hv::v2::context::disconnect(std::size_t targetUID, std::string targetName) {

	if (this->_instance->_composite_node_look_up_table.find(targetUID) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
		throw hv::v2::oexception(message);
	}

	try {
		auto node = this->_instance->_composite_node_look_up_table[targetUID];
		auto constNode = node->input(targetName);
		constNode->isConnected(false);

		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

		//Search Event Node
		this->searchingEventNode();

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
}
void hv::v2::context::disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) {

	if (targetNode == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null pointer exception");
		throw hv::v2::oexception(message);
	}

	try {
		this->disconnect(targetNode->uid(), targetName);
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}
void hv::v2::context::disconnect(std::size_t targetUID) {

	if (this->_instance->_composite_node_look_up_table.find(targetUID) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Uid is not exist");
		throw hv::v2::oexception(message);
	}

	try {
		auto node = this->_instance->_composite_node_look_up_table[targetUID];
		auto inputs = node->inputs();
		for (auto input : inputs) {
			input->clearMultipleSourceNode();
			input->isConnected(false);
		}

		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

		//Search Event Node
		this->searchingEventNode();

	}
	catch (hv::v2::oexception e) {
		throw e;
	}
}


void hv::v2::context::disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode) {

	if (targetNode == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null pointer exception");
		throw hv::v2::oexception(message);
	}

	try {
		this->disconnect(targetNode->uid());
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}


std::shared_ptr<hv::v2::iconstNode> hv::v2::context::constNode(std::size_t uid) {
	try {
		if (this->_instance->_const_node_loook_up_table.find(uid) == this->_instance->_const_node_loook_up_table.end()) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Can't find const node");
			throw hv::v2::oexception(message);
		}


		return this->_instance->_const_node_loook_up_table[uid];
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}



std::shared_ptr<hv::v2::icompositeNode> hv::v2::context::addNode(std::string name, int objectType) {
	try {
		for (auto& addon : this->_instance->_addons) {
			if (addon->exist(objectType) == true) {
				auto constructor = addon->compositeConstructor(objectType);
				auto node = constructor->create(name, this);

				auto uid = this->generate_var_unique_key();

				node->uid(uid);
				node->depth(1);

				this->_instance->_composite_node_look_up_table[uid] = node;


				//Depth 정렬
				this->sortingDepth();

				//Depth 순으로 그룹핑
				this->groupingDepth();

				//Search Event Node
				this->searchingEventNode();

				return node;
			}
		}

		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Object tpye not exists");
		throw hv::v2::oexception(message);

	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::context::removeNode(std::size_t uid) {


	try {
		this->disconnect(uid);


		auto node = this->_instance->_composite_node_look_up_table[uid];
		auto uids = node->constUID();

		for (auto uid : uids)
			this->_instance->_const_node_loook_up_table.erase(uid);

		this->_instance->_composite_node_look_up_table.erase(uid);

		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

		//Search Event Node
		this->searchingEventNode();
	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}
void hv::v2::context::removeNode(std::shared_ptr<hv::v2::icompositeNode> node) {

	if (node == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Null pointer exception");
		throw hv::v2::oexception(message);
	}


	try {
		this->removeNode(node->uid());

	}
	catch (hv::v2::oexception e) {
		throw e;
	}

}
void hv::v2::context::removeNode(std::string name) {


	std::vector<std::size_t> _uid;

	for (auto node : this->_instance->_composite_node_look_up_table) {
		if (node.second->name() == name) {
			_uid.push_back(node.second->uid());
		}
	}


	for (auto uid : _uid) {
		try {
			this->removeNode(uid);
		}
		catch (hv::v2::oexception e) {

		}
	}

}

void hv::v2::context::verification() {

	std::cout << "+====================================+" << std::endl;
	for (int depth = 1; depth <= this->_instance->_depth; depth++) {

		std::cout << "+ depth : " << depth << std::endl;
		for (auto node : this->_instance->_align_nodes[depth]) {
			std::cout << "\tname:";
			std::cout << node->name() << ",";
			std::cout << "uid:";
			std::cout << node->uid() << ",";
			std::cout << "type:";
			std::cout << node->type() << std::endl;
		}

	}
	std::cout << "+====================================+" << std::endl;
}
void hv::v2::context::clear() {
	this->_instance->_composite_node_look_up_table.clear();
	this->_instance->_composite_node_look_up_table.rehash(0);
	this->_instance->_const_node_loook_up_table.clear();
	this->_instance->_const_node_loook_up_table.rehash(0);
	this->clearMaxDepth();
}

int hv::v2::context::maxDepth() {
	return this->_instance->_depth;
}


void  hv::v2::context::groupingDepth() {
	this->_instance->_align_nodes.clear();
	for (std::size_t depth = 1; depth <= this->maxDepth(); depth++) {
		for (auto& pair : this->_instance->_composite_node_look_up_table) {
			if (depth == pair.second->depth()) {
				this->_instance->_align_nodes[depth].push_back(pair.second);
			}
		}
	}

}

void hv::v2::context::sortingDepth() {

	std::stack<std::shared_ptr<hv::v2::icompositeNode>> current_node_stack;
	for (auto node : this->_instance->_composite_node_look_up_table) {
		if (node.second->isConnected() == false) {
			node.second->depth(1);
			current_node_stack.push(node.second);
			this->_instance->_depth = 1;
		}
	}

	while (current_node_stack.empty() != true) {
		auto _currentNode = current_node_stack.top();
		current_node_stack.pop();

		for (auto node : this->_instance->_composite_node_look_up_table) {
			if (node.second->checkSourceUID(_currentNode->uid()) == true) {
				auto currentDepth = _currentNode->depth() + 1;
				if(this->_instance->_depth < currentDepth)
					this->_instance->_depth = currentDepth;
				node.second->depth(currentDepth);
				current_node_stack.push(node.second);
			}
		}
	}
}

void hv::v2::context::searchingEventNode() {
	this->_instance->_event_nodes.clear();
	
	for (auto node : this->_instance->_composite_node_look_up_table) {
		if (node.second->isEventNode() == true) {
			this->_instance->_event_nodes.push_back(node.second);
		}
	}
}

std::string hv::v2::context::serialization() {
	
	try {


		std::vector<std::pair<std::size_t, std::shared_ptr<hv::v2::icompositeNode>>> composite_node_vector(this->_instance->_composite_node_look_up_table.begin(),
																										   this->_instance->_composite_node_look_up_table.end());

		std::sort(composite_node_vector.begin(), composite_node_vector.end());


		nlohmann::json context;
		for (auto& node : composite_node_vector) {
			nlohmann::json composite_node = {
				{"name", node.second->name()},
				{"type", node.second->type()},
				{"uid", node.first},
				{"isFreezed", node.second->isFreezed()}
			};

			//Input Node Serialization
			auto inputs = node.second->inputs();
			for (auto& input : inputs) {
				nlohmann::json input_json = {
					{"name", input->name()},
					{"type", input->type()},
					{"uid", input->uid()},
					{"isConnected", input->isConnected()},
					{"isMultiple", input->isMultiple()},
					{"sourceName", input->sourceName()},
					{"sourceUID", input->sourceUID()},
					{"index", input->index()},
					{"multipleSourceNode", input->multipleSourceNode()},
					{"data", input->serialization()}
				};
				composite_node["inputs"].push_back(input_json);
			}
			//Output Node Serialization
			auto outputs = node.second->outputs();
			for (auto& output : outputs) {
				nlohmann::json output_json = {
					{"name", output->name()},
					{"type", output->type()},
					{"uid", output->uid()},
					{"index", output->index()}
				};
				composite_node["outputs"].push_back(output_json);
			}
			context.push_back(composite_node);
		}

		return context.dump(4);
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
void hv::v2::context::deserialization(std::string value) {
	try {
		nlohmann::json context = nlohmann::json::parse(value);

		this->_instance->_const_node_loook_up_table.clear();
		this->_instance->_const_node_loook_up_table.rehash(0);

		this->_instance->_composite_node_look_up_table.clear();
		this->_instance->_composite_node_look_up_table.rehash(0);

		for (auto& node : context) {
			auto name = node["name"].get<std::string>();
			auto type = node["type"].get<int>();
			auto uid = node["uid"].get<std::size_t>();
			auto isFreezed = node["isFreezed"].get<bool>();


			auto createdNode = this->addNode(name, type);
			this->_instance->_composite_node_look_up_table.erase(createdNode->uid()); //기존 UId 삭제



			createdNode->uid(uid); //객체 UID변경 
			this->_instance->_composite_node_look_up_table[uid] = createdNode; //새로운 UID로 객체 등록 


			this->removeConstNodeGroup(createdNode->inputs(), 9999);
			this->removeConstNodeGroup(createdNode->outputs(), 9999);

			//Inputs Replacement
			std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs;
			for (auto& input : node["inputs"]) {
				auto isConnected = input["isConnected"].get<bool>();
				auto isMultiple = input["isMultiple"].get<bool>();
				auto constNodeName = input["name"].get<std::string>();
				auto constNodeType = input["type"].get<int>();
				auto constNodeUID = input["uid"].get<std::size_t>();
				auto sourceName = input["sourceName"].get<std::string>();
				auto sourceUID = input["sourceUID"].get<std::size_t>();
				auto index = input["index"].get<int>();
				auto data = input["data"].get<std::string>();
				auto multipleSourceNode = input["multipleSourceNode"].get<std::vector<std::tuple<std::size_t, std::string>>>();


				auto createdConstNode = this->create(constNodeName, constNodeType, 9999);
				this->_instance->_const_node_loook_up_table.erase(createdConstNode->uid()); //기존 UID 삭제

				createdConstNode->uid(constNodeUID); //UID 갱신
				this->_instance->_const_node_loook_up_table[constNodeUID] = createdConstNode;
				
				createdConstNode->sourceName(sourceName);
				createdConstNode->sourceUID(sourceUID);
				createdConstNode->isConnected(isConnected);
				createdConstNode->index(index);
				createdConstNode->isMultiple(isMultiple);
				createdConstNode->multipleSourceNode(multipleSourceNode);
				createdConstNode->deserialization(data);
				inputs.push_back(createdConstNode);
			}
			createdNode->replaceInputs(inputs);

			//Outputs Replacement
			std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs;
			for (auto& output : node["outputs"]) {
				auto constNodeName = output["name"].get<std::string>();
				auto constNodeType = output["type"].get<int>();
				auto constNodeUID = output["uid"].get<std::size_t>();
				auto constNodeIndex = output["index"].get<int>();

				auto createdConstNode = this->create(constNodeName, constNodeType, 9999);
				this->_instance->_const_node_loook_up_table.erase(createdConstNode->uid()); //기존 UID 삭제

				createdConstNode->uid(constNodeUID); //UID 갱신
				this->_instance->_const_node_loook_up_table[constNodeUID] = createdConstNode;

				createdConstNode->index(constNodeIndex);

				outputs.push_back(createdConstNode);
			}
			createdNode->replaceOuputs(outputs);
		}


		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

		//Search Event Node
		this->searchingEventNode();
		
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

void hv::v2::context::save(std::string path) {
	try {
		auto json_context = this->serialization();

		std::ofstream jsonFile(path);
		if (jsonFile.is_open()) {
			jsonFile << json_context;
			jsonFile.close();
		}

	}
	catch (hv::v2::oexception e) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}

void hv::v2::context::load(std::string path) {
	try {

		std::ifstream text_file(path);
		if (text_file.is_open()) {
			std::string json_content((std::istreambuf_iterator<char>(text_file)), std::istreambuf_iterator<char>());
			this->deserialization(json_content);
			text_file.close();
		}
	}
	catch (hv::v2::oexception e) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
}



void hv::v2::context::setAddonPath(std::string path) {

	if (std::filesystem::exists(path) == false) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Addon path is not exists");
		throw hv::v2::oexception(message);
	}


	this->_instance->_libraryPath = path;


}

void hv::v2::context::clearMaxDepth() {
	this->_instance->_depth = 0;
}

void hv::v2::context::loadLibrary() {

	if (this->_instance->_addon_handles.size() > 0) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "library is arealdy loaded");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_libraryPath.length() == 0) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid library path.");
		throw hv::v2::oexception(message);
	}


	std::vector<std::string> error_message;

	for (const auto& entry : std::filesystem::directory_iterator(this->_instance->_libraryPath)) {
		if (entry.path().extension().string() == ".dll") {
			std::string filePath = entry.path().string();
			std::string fileName = entry.path().filename().string();

			bool check = false;
			HMODULE module = LoadLibraryA(filePath.c_str());

			if (module != nullptr) {
				try {
					auto addon_version = (const char* (*)())GetProcAddress(module, "ostrich_addon_version");
					auto addon_name = (const char* (*)())GetProcAddress(module, "ostrich_addon_name");
					auto addon_module = (bool (*)())GetProcAddress(module, "ostrich_addon_module_enable");
					auto addon_init = (bool (*)(hv::v2::icontext*))GetProcAddress(module, "ostrich_addon_init");
					auto addon_sanity_check = (bool (*)())GetProcAddress(module, "ostrich_sanity_check");

						
					if (addon_version == nullptr || addon_name == nullptr || addon_module == nullptr || addon_init == nullptr || addon_sanity_check == nullptr) {
						FreeLibrary(module);
						continue;
					}


#ifdef _DEBUG
					if (addon_sanity_check() == true) {
						FreeLibrary(module);
						continue;
					}
#else
					if (addon_sanity_check() == false) {
						std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "sanity check failed");
						error_message.push_back(message);
						FreeLibrary(module);
						continue;
					}
#endif


					if (addon_module() == false) {
						std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "its not proper addon file or invalid version addon");
						error_message.push_back(message);
						FreeLibrary(module);
						continue;
					}

					
					if (addon_init(this) == false) {
						std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "addon init failed");
						error_message.push_back(message);
						FreeLibrary(module);
						continue;
					}



					std::string version = addon_version();
					std::string name = addon_name();

					this->_instance->_addon_handles[fileName] = module;
					this->_instance->_addon_info.push_back({ name, version });
			

				}
				catch (std::exception e) {
					FreeLibrary(module);
					continue;
				}
			}
		}
	}

	if (error_message.size() > 0) {
		std::string message = "";

		for (auto _message : error_message) {
			message += _message;
		}

		std::string full_message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, message);
		throw hv::v2::oexception(message);
	}
}

void hv::v2::context::unloadLibrary() {

	std::vector<std::string> removedKey;

	bool error = false;

	try {

		this->clearMaxDepth();

		this->_instance->_composite_node_look_up_table.clear();
		this->_instance->_const_node_loook_up_table.clear();
		this->_instance->_addons.clear();
		this->_instance->_addon_type_overlap_table.clear();
		this->_instance->_addon_info.clear();
		this->_instance->_align_nodes.clear();
		this->_instance->_event_nodes.clear();

		this->_instance->_composite_node_look_up_table.rehash(0);
		this->_instance->_const_node_loook_up_table.rehash(0);
		this->_instance->_align_nodes.rehash(0);

	
		this->_instance->_addon_type_overlap_table.reserve(0);
		this->_instance->_addon_info.reserve(0);

		std::vector<std::shared_ptr<hv::v2::iaddon>>().swap(this->_instance->_addons);
		std::vector<hv::v2::addon_info>().swap(this->_instance->_addon_info);
		std::vector<std::shared_ptr<hv::v2::icompositeNode>>().swap(this->_instance->_event_nodes);

		for (auto& pair : this->_instance->_addon_handles) {
			if ((bool)FreeLibrary(pair.second) == true) {
				removedKey.push_back(pair.first);
			}
			else {
				error = true;
			}
		}

		for (auto& key : removedKey) {
			this->_instance->_addon_handles.erase(key);
		}

		if (error) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Unexpected error detected. please check addon");
			throw hv::v2::oexception(message);
		}


		this->_instance->_addon_handles.rehash(0);

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

std::vector<hv::v2::addon_info> hv::v2::context::addonInfo() {
	return this->_instance->_addon_info;
}

std::vector<std::shared_ptr<hv::v2::iaddon>> hv::v2::context::addons() {
	return this->_instance->_addons;
}



void hv::v2::context::initNodes() {
	//작업 해야됨.
	for (auto& node : this->_instance->_composite_node_look_up_table) {
		try {
			node.second->init();
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
}




void hv::v2::context::run(std::size_t uid) {

	try {
		this->_instance->_isStop = false;
		this->initNodes();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

	
	for (auto& node : this->_instance->_event_nodes) {
		if (node->uid() == uid) {
			try {
				node->call();
				return;
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
	}
}

void hv::v2::context::run(int objectType, std::string name) {

	try {
		this->_instance->_isStop = false;
		this->initNodes();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

	for (auto& node : this->_instance->_event_nodes) {
		if (node->type() == objectType && node->name() == name) {
			try {
				node->call();
				return;
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
	}
}

void hv::v2::context::run() {

	try {
		this->_instance->_isStop = false;
		this->initNodes();
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}


	for (auto& node : this->_instance->_event_nodes) {
		try {
			node->call();
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
}

void hv::v2::context::executionDelay(int ms) {
	this->_instance->_executionDelay = ms;
}

int hv::v2::context::executionDelay() {
	return this->_instance->_executionDelay;

}



std::shared_ptr<hv::v2::icontext> hv::v2::context::clone() {

	auto _context = std::make_shared<hv::v2::context>();

	try {

		_context->setAddonPath(this->_instance->_libraryPath);
		_context->loadLibrary();
		_context->executionDelay(this->_instance->_executionDelay);

		for (auto& node : this->_instance->_composite_node_look_up_table) {
			auto cloneNode = node.second->clone(_context.get());
			auto cloneInput = cloneNode->inputs();
			auto cloneOutput = cloneNode->outputs();

			_context->registerConstNodeGroup(cloneInput, 9999);
			_context->registerConstNodeGroup(cloneOutput, 9999);
			_context->_instance->_composite_node_look_up_table[cloneNode->uid()] = cloneNode;
			
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

	//Depth 정렬
	_context->sortingDepth();

	//Depth 순으로 그룹핑
	_context->groupingDepth();

	//Search Event Node
	_context->searchingEventNode();

	return _context;
}


// Private Function
std::size_t hv::v2::context::generate_const_unique_key() {
	std::random_device rd;
	std::mt19937_64 mersenne(rd());
	std::uniform_int_distribution<unsigned long long int> dice(1, INT64_MAX);


	unsigned long long unique_id = 0;

	do {
		unique_id = dice(rd);
		if (unique_id == 0)
			continue;
	} while (this->_instance->_const_node_loook_up_table.find(unique_id) != this->_instance->_const_node_loook_up_table.end());


	return unique_id;
}


std::size_t hv::v2::context::generate_var_unique_key() {
	std::random_device rd;
	std::mt19937_64 mersenne(rd());
	std::uniform_int_distribution<unsigned long long int> dice(1, INT64_MAX);


	unsigned long long unique_id = 0;

	do {
		unique_id = dice(rd);
		if (unique_id == 0)
			continue;
	} while (this->_instance->_composite_node_look_up_table.find(unique_id) != this->_instance->_composite_node_look_up_table.end());


	return unique_id;
}




// Node Special Lock Down
void hv::v2::context::registerAddon(std::shared_ptr<hv::v2::iaddon> addon, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (addon == nullptr) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid addon.");
		throw hv::v2::oexception(message);
	}



	auto addon_information = addon->information();

	for (auto& info : addon_information) {
		this->_instance->_addon_type_overlap_table[info->type()]++;
	}


	for (auto& frequency : this->_instance->_addon_type_overlap_table) {
		if (frequency.second > 1) {
			auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type overlap addon issue");
			throw hv::v2::oexception(message);
		}
	}


	this->_instance->_addons.push_back(addon);

}




std::shared_ptr<hv::v2::iconstNode> hv::v2::context::create(std::string name, int objectType, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (name.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (objectType == (int)hv::v2::objectType::CONST_EXECUTION) {
		auto uid = this->generate_const_unique_key();
		auto executionNode = std::make_shared<hv::v2::constExecutionNode>(name);
		executionNode->uid(uid);
		this->_instance->_const_node_loook_up_table[uid] = executionNode;
		return executionNode;
	}


	try {
		for (auto addon : this->_instance->_addons) {
			if (addon->exist(objectType) == true) {

				auto uid = this->generate_const_unique_key();
				auto constructor = addon->constConstructor(objectType);
				auto node = constructor->create(name);
				node->uid(uid);


				this->_instance->_const_node_loook_up_table[uid] = node;

				return node;
			}
		}

		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Can't find object type");
		throw hv::v2::oexception(message);

	}
	catch (std::exception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}


std::shared_ptr<hv::v2::iconstNode> hv::v2::context::find(std::size_t uid, std::string name, int depth, int specialKey) {


	if (specialKey != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (name.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_composite_node_look_up_table.find(uid) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "uid is not exist");
		throw hv::v2::oexception(message);
	}


	try {

		auto node = this->_instance->_composite_node_look_up_table[uid];

		if (node->depth() >= depth) {
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid graph depth");
			throw hv::v2::oexception(message);
		}

		if (node->isConditionalNode() == false) {
			node->call();
		}
		auto const_output = node->output(name);

		return const_output;
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


std::shared_ptr<hv::v2::irunable> hv::v2::context::findExecution(std::size_t uid, std::string name, int depth, int special_lock_key) {

	std::shared_ptr<hv::v2::irunable> temp;

	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (name.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

	if (this->_instance->_composite_node_look_up_table.find(uid) == this->_instance->_composite_node_look_up_table.end()) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "uid is not exist");
		throw hv::v2::oexception(message);
	}


	try {

		for (auto& pair : this->_instance->_composite_node_look_up_table) {

			if (pair.second->checkSourceUID(uid) == true) {
				auto inputs = pair.second->inputs();
				for (auto& input : inputs) {
					if (input->type() == (int)hv::v2::objectType::CONST_EXECUTION) {
						if (input->sourceName() == name) {
							return pair.second;
						}
					}
				}
			}
		}

		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Can't find flow node");
		throw hv::v2::oexception(message);
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

	return temp;
}

void hv::v2::context::registerConstNodeGroup(std::vector<std::shared_ptr<hv::v2::iconstNode>> group, int special_lock_key) {

	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	for (auto& node : group) {
		this->_instance->_const_node_loook_up_table[node->uid()] = node;
	}
}


void hv::v2::context::removeConstNodeGroup(std::vector<std::shared_ptr<hv::v2::iconstNode>> group, int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	for (auto& node : group) {
		this->_instance->_const_node_loook_up_table.erase(node->uid());
	}
}


void hv::v2::context::stop() {
	this->_instance->_isStop = true;
}

bool hv::v2::context::isStop(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}


	return this->_instance->_isStop;
}