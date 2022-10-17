#pragma once


#ifndef OSTRICH_ICONTEXT
#define OSTRICH_ICONTEXT


#include "ihandle.h"
#include "inode.h"
#include "icompositeNode.h"
#include "iconstNode.h"
#include "iaddon.h"
#include "contentType.h"


#include <vector>
#include <string>

namespace hv {
	namespace v2 {

		using addon_info = std::tuple<std::string, std::string>;
		class icontext : public hv::v2::ihandle {
		public:

			virtual ~icontext() { }

			// Addon manipulation
			virtual void loadLibrary() =0;
			virtual void unloadLibrary() = 0;
			virtual void setAddonPath(std::string path) = 0;
			virtual std::vector<addon_info> addonInfo() = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iaddon>> addons() = 0;


			// Context manipulation
			virtual void load(std::string context, hv::v2::contentType contentType) = 0;
			virtual void save(std::string path) = 0;
			virtual void initNodes() = 0;
			virtual void setMaxTaskCount(int num) = 0;
			virtual void verification() = 0;
			virtual void clear() = 0;
			virtual void run(std::size_t uid) = 0;
			virtual void run(int objectType, std::string name) = 0;
			

			virtual int maxDepth() = 0;
	
			virtual std::string serialization() = 0;
			virtual void deserialization(std::string value) = 0;
	

			// Node manipulation
			virtual std::shared_ptr<hv::v2::icompositeNode> search(std::size_t uid) = 0;
			virtual std::shared_ptr<hv::v2::icompositeNode> search(std::string name) = 0;

			virtual void connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) = 0;
			virtual void connect(std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) = 0;

			virtual void disconnect(std::string name) = 0;
			virtual void disconnect(std::size_t targetUID, std::string targetName) = 0;
			virtual void disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) = 0;
			virtual void disconnect(std::size_t targetUID) = 0;
			virtual void disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode) = 0;

			virtual std::shared_ptr<hv::v2::icompositeNode> addNode(std::string name, int objectType) = 0;
			virtual void removeNode(std::size_t uid) = 0;
			virtual void removeNode(std::shared_ptr<hv::v2::icompositeNode> node) = 0;
			virtual void removeNode(std::string name) = 0;




			// Node Special Lock
			virtual void registerAddon(std::shared_ptr<hv::v2::iaddon> addon, int special_lock_key) =0;
			virtual std::shared_ptr<hv::v2::iconstNode> create(std::string name, int objectType, int special_lock_key) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> find(std::size_t uid, std::string name, int depth, int special_lock_key) = 0;
			virtual std::shared_ptr<hv::v2::irunable> findExecution(std::size_t uid, std::string name, int depth, int special_lock_key) = 0;

		};
	}
}

#endif
