#include "context.h"
#include "commonException.h"
#include "macro.h"
#include "contextStatus.h"

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


namespace hv {
	namespace v2 {

		class impl_context {
		public:

			std::unordered_map< std::size_t, std::shared_ptr<hv::v2::icompositeNode>> _composite_node_look_up_table;
			std::unordered_map<std::size_t, std::shared_ptr<hv::v2::iconstNode>> _const_node_loook_up_table;
			std::unordered_map < std::size_t, std::vector<std::shared_ptr<hv::v2::icompositeNode>>> _align_nodes;


			std::unordered_map<std::string, HMODULE> _addon_handles;
			std::vector<hv::v2::addon_info> _addon_info;
			std::string _libraryPath;
			std::vector<std::shared_ptr<hv::v2::iaddon>> _addons;

			unsigned int _max_task_count;


			hv::v2::contextStatus _currentContextStatus;


			int _depth;


			impl_context() {

				_depth = 0;
				_max_task_count = 4;

				_currentContextStatus = hv::v2::contextStatus::CONTINUE;

			}


			~impl_context() {

			}

		};
	}
}


hv::v2::context::context() {


	this->_instance = std::make_unique<hv::v2::impl_context>();



}

hv::v2::context::~context() {

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
			if (node->isConnected() == true) {
				current_node_stack.push(node->uid());
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
				if (node->isConnected() == true) {
					current_node_stack.push(node->uid());
				}
			}
		}



		auto sourceConstNode = sourceNode->output(sourceName);
		auto targetConstNode = targetNode->input(targetName);


		if (sourceConstNode->type() != targetConstNode->type()) {
				auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Type is not match");
				throw hv::v2::oexception(message);
		}


		targetConstNode->sourceName(sourceName);
		targetConstNode->sourceUID(sourceNode->uid());
		targetConstNode->isConnected(true);
		


		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

	}
	catch (hv::v2::oexception e) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}

}

void hv::v2::context::disconnect(std::string name) {

	try {
		for (auto node : this->_instance->_composite_node_look_up_table) {
			if (node.second->name() == name) {
				auto inputs = node.second->inputs();
				for (auto input : inputs) {
					input->isConnected(false);
				}

				//Depth 정렬
				this->sortingDepth();

				//Depth 순으로 그룹핑
				this->groupingDepth();
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
			input->isConnected(false);
		}

		//Depth 정렬
		this->sortingDepth();

		//Depth 순으로 그룹핑
		this->groupingDepth();

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
	this->_instance->_const_node_loook_up_table.clear();
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

std::string hv::v2::context::serialization() {
	//작업 해야됨.
	return "";

}
void hv::v2::context::deserialization(std::string value) {
	//작업 해야됨.

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


					if (addon_version == nullptr || addon_name == nullptr || addon_module == nullptr || addon_init == nullptr) {
						FreeLibrary(module);
						continue;
					}

					if (addon_module() == false) {
						FreeLibrary(module);
					}

					

					if (addon_init(this) == false) {
						FreeLibrary(module);
					}

					std::string version = addon_version();
					std::string name = addon_name();

					this->_instance->_addon_handles[fileName] = module;
					this->_instance->_addon_info.push_back({ name, version });
			

				}
				catch (std::exception e) {
					FreeLibrary(module);
				}
			}
		}
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



void hv::v2::context::load(std::string context, hv::v2::contentType contentType) {
	//작업 해야됨.
}

void hv::v2::context::save(std::string path) {
	//작업 해야됨.
}

void hv::v2::context::initNodes() {
	//작업 해야됨.


	concurrency::concurrent_vector<std::string> error_message;
	volatile bool errorDetected = false;


	for (auto& node : this->_instance->_composite_node_look_up_table) {
		try {
			node.second->init();

		}
		catch (hv::v2::oexception e) {
			error_message.push_back(e.what());
			errorDetected = true;
		}
		catch (std::exception e) {
			error_message.push_back(e.what());
			errorDetected = true;
		}
	}

	if (errorDetected == true) {
		std::string all_message;
		for (auto& message : error_message) {
			all_message += message;
		}
		throw hv::v2::oexception(all_message);
	}

}

void hv::v2::context::setMaxTaskCount(int num) {
	this->_instance->_max_task_count = num;
}

void hv::v2::context::run() {

	concurrency::concurrent_vector<std::string> error_message;
	volatile bool errorDetected = false;

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
			std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invaliid graph depth");
			throw hv::v2::oexception(message);
		}

		auto const_output = node->output(name);

		return const_output;
	}
	catch (hv::v2::oexception e) {
		std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());
		throw hv::v2::oexception(message);
	}


}


void hv::v2::context::loopBack(std::string key, int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}

}
void hv::v2::context::foward(std::string key, int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	if (key.length() == 0) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid key");
		throw hv::v2::oexception(message);
	}


}
bool hv::v2::context::isLoopContinue(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}


	return this->_instance->_currentContextStatus == hv::v2::contextStatus::LOOP_CONTINUE;

}
bool hv::v2::context::isLoopBreak(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	return this->_instance->_currentContextStatus == hv::v2::contextStatus::LOOP_BREAK;
}

void hv::v2::context::loopContinue(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	this->_instance->_currentContextStatus = hv::v2::contextStatus::LOOP_CONTINUE;
}
void hv::v2::context::loopBreak(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	this->_instance->_currentContextStatus = hv::v2::contextStatus::LOOP_BREAK;
}

void hv::v2::context::stop(int special_lock_key) {
	if (special_lock_key != 9999) {
		auto message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, "Invalid special key");
		throw hv::v2::oexception(message);
	}

	this->_instance->_currentContextStatus = hv::v2::contextStatus::STOP;
}