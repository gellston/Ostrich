#pragma once


#ifndef OSTRICH_ISCRIPT_BUILDER
#define OSTRICH_ISCRIPT_BUILDER

#include "icompositeNode.h"
#include "icontext.h"


namespace hv {
	namespace v2 {
		class iscript {
		public:
			virtual ~iscript() {  }




			virtual void registerProcessCompleteEvent(std::string context_name, std::function<void(int nodeType, std::size_t composite_uid)> eventHandler) = 0;
			virtual void registerConstChangedEvent(std::string context_name, std::function<void(std::size_t constUID)> eventHandler) = 0;

			virtual void resetProcessCompleteEvent(std::string context_name) = 0;
			virtual void resetConstChangedEvent(std::string context_name) = 0;



			virtual std::shared_ptr<hv::v2::icompositeNode> search(std::string context_name, std::size_t uid) = 0;
			virtual std::shared_ptr<hv::v2::icompositeNode> search(std::string context_name, std::string name) = 0;
			template<typename T> std::shared_ptr<T> search(std::string context_name, std::string name) {
				try {
					return std::dynamic_pointer_cast<T>(this->search(context_name, name));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
				catch (std::exception e) {
					throw e;
				}
			}

			template<typename T> std::shared_ptr<T> search(std::string context_name, std::size_t uid) {
				try {
					return std::dynamic_pointer_cast<T>(this->search(context_name, uid));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
				catch (std::exception e) {
					throw e;
				}
			}


			virtual bool checkConnectability(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) = 0;

			virtual void connect(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) = 0;
			virtual void connect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) = 0;

			virtual void disconnect(std::string context_name, std::string name) = 0;
			virtual void disconnect(std::string context_name, std::size_t targetUID, std::string targetName) = 0;
			virtual void disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) = 0;
			virtual void disconnect(std::string context_name, std::size_t targetUID) = 0;
			virtual void disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode) = 0;

			virtual std::shared_ptr<hv::v2::icompositeNode> addNode(std::string context_name, std::string name, int objetType) = 0;
			virtual void removeNode(std::string context_name, std::size_t uid) = 0;
			virtual void removeNode(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> node) = 0;
			virtual void removeNode(std::string context_name, std::string name) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> constNode(std::string context_name, std::size_t uid) = 0;


			virtual void verification(std::string context_name) = 0;
			virtual void clear(std::string context_name) = 0;
			virtual void loadLibrary(std::string context_name) = 0;
			virtual void unloadLibrary(std::string context_name) = 0;
			virtual void loadLibrary() = 0;
			virtual void unloadLibrary() = 0;
			virtual void setAddonPath(std::string path) = 0;
			virtual void executionDelay(int ms) = 0;
			virtual int executionDelay() = 0;
			virtual std::vector<hv::v2::addon_info> addonInfo(std::string context_name) = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iaddon>> addons(std::string context_name) = 0;

			virtual void load(std::string context_name, std::string path) = 0;
			virtual void save(std::string context_name, std::string path) = 0;
			virtual void initNodes(std::string context_name) = 0;
			virtual void run(std::string context_name, std::size_t uid) = 0;
			virtual void run(std::string context_name, int objectType, std::string name) = 0;
			virtual void run(std::string context_name) = 0;


			virtual std::shared_ptr<hv::v2::icontext> context(std::string name) = 0;
			virtual void createContext(std::string name) = 0;
			virtual void renameContext(std::string sourceName, std::string targetName) = 0;
			virtual void removeContext(std::string name) = 0;
			virtual void copyContext(std::string sourceName, std::string targetName) = 0;

			virtual std::string serialization(std::string context) = 0;
			virtual void deserialization(std::string context, std::string jsonContext) = 0;
		};
	}
}

#endif