#pragma once


#ifndef OSTRICH_ICONTEXT
#define OSTRICH_ICONTEXT


#include "ihandle.h"
#include "inode.h"
#include "ivarNode.h"
#include "iconstNode.h"
#include "iaddon.h"
#include "contentType.h"
#include "syncType.h"


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
			virtual void run(hv::v2::syncType sync = v2::syncType::sequential_execution) = 0;

			virtual int maxDepth() = 0;
	
			virtual std::string serialization() = 0;
			virtual void deserialization(std::string value) = 0;
	

			// Node manipulation
			virtual std::shared_ptr<hv::v2::ivarNode> search(std::size_t uid) = 0;
			virtual std::shared_ptr<hv::v2::ivarNode> search(std::string nick) = 0;

			virtual void connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) = 0;
			virtual void connect(std::shared_ptr<hv::v2::ivarNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) = 0;

			virtual void disonnect(std::string nick) = 0;
			virtual void disconnect(std::size_t targetUID, std::string targetName) = 0;
			virtual void disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) = 0;
			virtual void disconnect(std::size_t targetUID) = 0;
			virtual void disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode) = 0;

			virtual std::shared_ptr<hv::v2::ivarNode> addNode(std::string name, int objectType) = 0;
			virtual void removeNode(std::size_t uid) = 0;
			virtual void removeNode(std::shared_ptr<hv::v2::ivarNode> node) = 0;
			virtual void removeNode(std::string nick) = 0;




			// Node Special Lock
			virtual void registerAddon(std::shared_ptr<hv::v2::iaddon> addon, int special_lock_key) =0;
			virtual std::shared_ptr<hv::v2::iconstNode> create(std::string name, int objectType, int special_lock_key) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> find(std::size_t uid, std::string name, int depth, int special_lock_key) = 0;

		};
	}
}

#endif
