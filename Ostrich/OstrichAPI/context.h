#pragma once


#ifndef OSTRICH_CONTEXT
#define OSTRICH_CONTEXT


#include "icontext.h"
#include "common_export.h"


namespace hv {
	namespace v2 {

		class impl_context;

		class context : public hv::v2::icontext {
		private:
			std::unique_ptr<hv::v2::impl_context> _instance;


			OSTRICH_COMMON_API std::size_t generate_const_unique_key();
			OSTRICH_COMMON_API std::size_t generate_var_unique_key();
			OSTRICH_COMMON_API void clearMaxDepth();
			OSTRICH_COMMON_API void groupingDepth();
			OSTRICH_COMMON_API void sortingDepth();
			OSTRICH_COMMON_API void searchingEventNode();

			OSTRICH_COMMON_API int maxDepth() override;

	


		public:

			OSTRICH_COMMON_API context();
			OSTRICH_COMMON_API virtual ~context() override;


			OSTRICH_COMMON_API void onProcessComplete(int nodeType, std::size_t composite_uid);
			OSTRICH_COMMON_API void onConstChanged(int nodeType, std::size_t constUID);
			OSTRICH_COMMON_API void onProcessStart(int nodeType, std::size_t composite_uid);
			OSTRICH_COMMON_API void onError(int nodeType, std::size_t composite_uid, const char* message);


			OSTRICH_COMMON_API void registerProcessCompleteEvent(std::function<void(int nodeType, std::size_t composite_uid)> eventHandler);
			OSTRICH_COMMON_API void registerConstChangedEvent(std::function<void(int nodeType, std::size_t constUID)> eventHandler);
			OSTRICH_COMMON_API void registerProcessStartEvent(std::function<void(int nodeType, std::size_t composite_uid)> eventHandler);
			OSTRICH_COMMON_API void registerErrorEvent(std::function<void(int nodeType, std::size_t composite_uid, const char* message)> eventHandler);

			OSTRICH_COMMON_API void resetProcessCompleteEvent();
			OSTRICH_COMMON_API void resetConstChangedEvent();
			OSTRICH_COMMON_API void resetProcessStartEvent();
			OSTRICH_COMMON_API void resetErrorEvent();


			OSTRICH_COMMON_API void updateAllConstNode();


			//Node manipulation
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> search(std::size_t uid) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> search(std::string name) override;
			template<typename T> std::shared_ptr<T> search(std::size_t uid) {
				try {
					return std::dynamic_pointer_cast<T>(this->search(uid));
				}
				catch (std::exception e) {
					throw e;
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}

			template<typename T> std::shared_ptr<T> search(std::string name) {
				try {
					return std::dynamic_pointer_cast<T>(this->search(name));
				}
				catch (std::exception e) {
					throw e;
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}


			OSTRICH_COMMON_API void connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) override;
			OSTRICH_COMMON_API void connect(std::shared_ptr<hv::v2::icompositeNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) override;

			OSTRICH_COMMON_API bool checkConnectability(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) override;

			OSTRICH_COMMON_API void disconnect(std::string name) override;
			OSTRICH_COMMON_API void disconnect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) override;
			OSTRICH_COMMON_API void disconnect(std::size_t targetUID, std::string targetName) override;
			OSTRICH_COMMON_API void disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode, std::string targetName) override;
			OSTRICH_COMMON_API void disconnect(std::size_t targetUID) override;
			OSTRICH_COMMON_API void disconnect(std::shared_ptr<hv::v2::icompositeNode> targetNode) override;



			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icompositeNode> addNode(std::string name, int objectType) override;
			OSTRICH_COMMON_API void removeNode(std::size_t uid) override;
			OSTRICH_COMMON_API void removeNode(std::shared_ptr<hv::v2::icompositeNode> node) override;
			OSTRICH_COMMON_API void removeNode(std::string name) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> constNode(std::size_t uid) override;


			//Addon manipulation
			OSTRICH_COMMON_API void verification() override;
			OSTRICH_COMMON_API void clear() override;
			OSTRICH_COMMON_API void loadLibrary() override;
			OSTRICH_COMMON_API void unloadLibrary() override;
			OSTRICH_COMMON_API void setAddonPath(std::string path) override;
			OSTRICH_COMMON_API std::vector<hv::v2::addon_info> addonInfo() override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iaddon>> addons() override;

			OSTRICH_COMMON_API void load(std::string path) override;
			OSTRICH_COMMON_API void save(std::string path) override;
			OSTRICH_COMMON_API void initNodes() override;
			OSTRICH_COMMON_API void run(std::size_t uid) override;
			OSTRICH_COMMON_API void run(int objectType, std::string name) override;
			OSTRICH_COMMON_API void run() override;
			OSTRICH_COMMON_API void executionDelay(int ms) override;
			OSTRICH_COMMON_API int executionDelay() override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::icontext> clone() override;
			OSTRICH_COMMON_API void stop() override;



			OSTRICH_COMMON_API std::string serialization() override;
			OSTRICH_COMMON_API void deserialization(std::string value) override;



			//Node Special Lock
			OSTRICH_COMMON_API void registerAddon(std::shared_ptr<hv::v2::iaddon> addon, int special_lock_key) override;
			OSTRICH_COMMON_API virtual std::shared_ptr<hv::v2::iconstNode> create(std::string name, int objectType, int special_lock_key) override;
			OSTRICH_COMMON_API virtual std::shared_ptr<hv::v2::iconstNode> find(std::size_t uid, std::string name, int depth, int special_lock_key) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::irunable> findExecution(std::size_t uid, std::string name, int depth, int special_lock_key) override;
			OSTRICH_COMMON_API void registerConstNodeGroup(std::vector<std::shared_ptr<hv::v2::iconstNode>> group, int special_lock_key) override;
			OSTRICH_COMMON_API void removeConstNodeGroup(std::vector<std::shared_ptr<hv::v2::iconstNode>> group, int special_lock_key) override;
			OSTRICH_COMMON_API bool isStop(int special_lock_key) override;


		};
	}
}

#endif
