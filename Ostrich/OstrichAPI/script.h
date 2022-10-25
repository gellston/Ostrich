#pragma once


#ifndef OSTRICH_SCRIPT_BUIILDER
#define OSTRICH_SCRIPT_BUILDER

#include "icontext.h"

namespace hv {
	namespace v2 {
		class impl_script;
		class script {

		private:
			std::unique_ptr<hv::v2::impl_script> _instance;
		
		public:

			OSTRICH_COMMON_API script();
			OSTRICH_COMMON_API ~script();

			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> search(std::string context_name, std::size_t uid);
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> search(std::string context_name, std::string name);
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

			OSTRICH_COMMON_API void connect(std::string context_name, std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName);
			OSTRICH_COMMON_API void connect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName);

			OSTRICH_COMMON_API void disconnect(std::string context_name, std::string name);
			OSTRICH_COMMON_API void disconnect(std::string context_name, std::size_t targetUID, std::string targetName);
			OSTRICH_COMMON_API void disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName);
			OSTRICH_COMMON_API void disconnect(std::string context_name, std::size_t targetUID);
			OSTRICH_COMMON_API void disconnect(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> targetNode);

			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> addNode(std::string context_name, std::string name, int objetType);
			OSTRICH_COMMON_API void removeNode(std::string context_name, std::size_t uid);
			OSTRICH_COMMON_API void removeNode(std::string context_name, std::shared_ptr<hv::v2::icompositeNode> node);
			OSTRICH_COMMON_API void removeNode(std::string context_name, std::string name);

			OSTRICH_COMMON_API void verification(std::string context_name);
			OSTRICH_COMMON_API void clear(std::string context_name);
			OSTRICH_COMMON_API void loadLibrary(std::string context_name);
			OSTRICH_COMMON_API void unloadLibrary(std::string context_name);
			OSTRICH_COMMON_API void loadLibrary();
			OSTRICH_COMMON_API void unloadLibrary();
			OSTRICH_COMMON_API void setAddonPath(std::string path);
			OSTRICH_COMMON_API std::vector<hv::v2::addon_info> addonInfo(std::string context_name);
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iaddon>> addons(std::string context_name);

			OSTRICH_COMMON_API void load(std::string context_name, std::string path);
			OSTRICH_COMMON_API void save(std::string context_name, std::string path);
			OSTRICH_COMMON_API void initNodes(std::string context_name);
			OSTRICH_COMMON_API void run(std::string context_name, std::size_t uid);
			OSTRICH_COMMON_API void run(std::string context_name, int objectType, std::string name);
			OSTRICH_COMMON_API void run(std::string context_name);

			OSTRICH_COMMON_API void createContext(std::string name);
			OSTRICH_COMMON_API void renameContext(std::string sourceName, std::string targetName);
			OSTRICH_COMMON_API void removeContext(std::string name);
			OSTRICH_COMMON_API void copyContext(std::string sourceName, std::string targetName);

			OSTRICH_COMMON_API std::string serialization(std::string context);
			OSTRICH_COMMON_API void deserialization(std::string context, std::string jsonContext);

		};
	}
}

#endif