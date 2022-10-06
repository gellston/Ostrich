#pragma once


#ifndef OSTRICH_VAR_NODE
#define OSTRICH_VAR_NODE


#include "node.h"
#include "ivarNode.h"



namespace hv {
	namespace v2 {
		class impl_varNode;
		class varNode : public hv::v2::node, public hv::v2::ivarNode {
		private:
			std::unique_ptr<hv::v2::impl_varNode> _instance;

		public:
			OSTRICH_COMMON_API varNode(std::string value, int type, hv::v2::ihandle * context);
			OSTRICH_COMMON_API virtual ~varNode() override;

			OSTRICH_COMMON_API int depth() override;
			OSTRICH_COMMON_API void depth(int value) override;


			OSTRICH_COMMON_API bool inCondition() override;
			OSTRICH_COMMON_API void inCondition(bool value) override;
			OSTRICH_COMMON_API bool isConditionalNode() override;


			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs() override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs() override;

			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> input(std::string key) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> output(std::string key) override;



			OSTRICH_COMMON_API std::string name() override;
			OSTRICH_COMMON_API std::string nick() override;
			OSTRICH_COMMON_API void nick(std::string value) override;
			OSTRICH_COMMON_API int type() override;


			OSTRICH_COMMON_API std::size_t uid() override;
			OSTRICH_COMMON_API void uid(std::size_t value) override;



		protected:

			OSTRICH_COMMON_API void isConditionalNode(bool value) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> search(std::string key, int objectType, hv::v2::searchType type)override;
			template<typename T> std::shared_ptr<T> search(std::string key, int objectType, hv::v2::searchType type) {
				try {

					auto node = this->search(key, objectType, type);
					return std::dynamic_pointer_cast<T>(node);
				}
				catch (std::exception e) {
					throw e;
				}
			}
			OSTRICH_COMMON_API void registerNode(std::string key, int objectType, hv::v2::searchType type) override;

		};
	}
}

#endif