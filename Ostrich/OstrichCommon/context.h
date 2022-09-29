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
		public:

			OSTRICH_COMMON_API context();
			OSTRICH_COMMON_API virtual ~context() override;


			OSTRICH_COMMON_API std::shared_ptr<hv::v2::inode> search(std::size_t uid) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::inode> search(std::string nick) override;

			OSTRICH_COMMON_API void connect(std::size_t sourceUID, std::string sourceName, std::size_t targetUID, std::string targetName) override;
			OSTRICH_COMMON_API void connect(std::shared_ptr<hv::v2::ivarNode> sourceNode, std::string sourceName, std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) override;

			OSTRICH_COMMON_API void disonnect(std::string nick) override;
			OSTRICH_COMMON_API void disconnect(std::size_t targetUID, std::string targetName) override;
			OSTRICH_COMMON_API void disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode, std::string targetName) override;
			OSTRICH_COMMON_API void disconnect(std::size_t targetUID) override;
			OSTRICH_COMMON_API void disconnect(std::shared_ptr<hv::v2::ivarNode> targetNode) override;



			OSTRICH_COMMON_API std::shared_ptr<hv::v2::ivarNode> addNode(std::string name, int objectType) override;
			OSTRICH_COMMON_API void removeNode(std::size_t uid) override;
			OSTRICH_COMMON_API void removeNode(std::shared_ptr<hv::v2::ivarNode> node) override;
			OSTRICH_COMMON_API void removeNode(std::string nick) override;

			OSTRICH_COMMON_API void verification() override;
			OSTRICH_COMMON_API void clear() override;

			OSTRICH_COMMON_API int maxDepth() override;
			OSTRICH_COMMON_API void maxDepth(int value) override;

			OSTRICH_COMMON_API std::string serialization() override;
			OSTRICH_COMMON_API void deserialization(std::string value) override;

		};
	}
}

#endif
