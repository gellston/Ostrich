#pragma once


#ifndef OSTRICH_COMPOSITE_NODE
#define OSTRICH_COMPOSITE_NODE


#include "node.h"
#include "icompositeNode.h"
#include "commonException.h"


namespace hv {
	namespace v2 {
		class impl_compositeNode;
		class compositeNode : public hv::v2::node, public hv::v2::icompositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeNode> _instance;

		public:
			OSTRICH_COMMON_API compositeNode(std::string value, int type, hv::v2::ihandle * context);
			OSTRICH_COMMON_API virtual ~compositeNode() override;

			OSTRICH_COMMON_API int depth() override;
			OSTRICH_COMMON_API void depth(int value) override;


			OSTRICH_COMMON_API bool isConnected() override;
			OSTRICH_COMMON_API bool checkSourceUID(std::size_t uid) override;

			OSTRICH_COMMON_API bool isConditionalNode() override;


			OSTRICH_COMMON_API bool isFreezed() override;
			OSTRICH_COMMON_API void isFreezed(bool value) override;

			OSTRICH_COMMON_API bool isEventNode() override;

			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs() override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs() override;

			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> input(std::string key) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> output(std::string key) override;

			OSTRICH_COMMON_API void replaceInputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs) override;
			OSTRICH_COMMON_API void replaceOuputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs) override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> inputClone() override;
			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> outputClone() override;

			OSTRICH_COMMON_API std::vector<std::size_t> constUID() override;
			OSTRICH_COMMON_API std::vector<std::size_t> inputConstUID() override;
			OSTRICH_COMMON_API std::vector<std::size_t> outputConstUID() override;

			OSTRICH_COMMON_API std::string name() override;

			OSTRICH_COMMON_API int type() override;


			OSTRICH_COMMON_API std::size_t uid() override;
			OSTRICH_COMMON_API void uid(std::size_t value) override;

			OSTRICH_COMMON_API hv::v2::resultType call() override;
			OSTRICH_COMMON_API void updateConst(std::size_t uid) override;



		protected:

			OSTRICH_COMMON_API void isEventNode(bool check) override;

			OSTRICH_COMMON_API std::shared_ptr<hv::v2::iconstNode> search(std::string key, int objectType, hv::v2::searchType type)override;
			template<typename T> std::shared_ptr<T> search(std::string key, int objectType, hv::v2::searchType type) {
				try {

					auto node = this->search(key, objectType, type);
					return std::dynamic_pointer_cast<T>(node);
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
				catch (std::exception e) {
					throw e; 
				}

			}


			OSTRICH_COMMON_API std::vector<std::shared_ptr<hv::v2::iconstNode>> searchMultipleNode(std::string key, int objectType, hv::v2::searchType type) override;
			template<typename T> std::vector<std::shared_ptr<T>> searchMultipleNode(std::string key, int objectType, hv::v2::searchType type) {
				try {
					auto nodes = this->searchMultipleNode(key, objectType, type);
					std::vector<std::shared_ptr<T>> _cast_nodes;

					for (auto _node : nodes) {
						_cast_nodes.push_back(std::dynamic_pointer_cast<T>(_node));
					}
					return _cast_nodes;
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
				catch (std::exception e) {
					throw e;
				}

			}

			OSTRICH_COMMON_API void registerNode(std::string key, int objectType, hv::v2::searchType type) override;
			OSTRICH_COMMON_API void registerMultipleNode(std::string key, int objectType, hv::v2::searchType type) override;
			OSTRICH_COMMON_API void registerExecutionNode(std::string key, hv::v2::searchType type) override;
			OSTRICH_COMMON_API std::shared_ptr<hv::v2::irunable> execution(std::string key) override;

		};
	}
}

#endif