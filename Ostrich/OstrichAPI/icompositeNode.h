#pragma once


#ifndef OSTRICH_ICOMPOSITENODE
#define OSTRICH_ICOMPOSITENODE


#include "inode.h"
#include "iconstNode.h"
#include "searchType.h"
#include "irunable.h"



#include <iostream>
#include <vector>

namespace hv {
	namespace v2 {
		class icompositeNode : public hv::v2::inode, public hv::v2::irunable {
		public:

			virtual ~icompositeNode() { }

			virtual int depth() = 0;
			virtual void depth(int value) = 0;

			virtual bool hasError() = 0;
			virtual void hasError(bool error) = 0;

			virtual bool isConnected() = 0;
			virtual bool checkSourceUID(std::size_t uid) = 0;

			virtual bool isConditionalNode() = 0;

			virtual bool isFreezed() = 0;
			virtual void isFreezed(bool value) = 0;

			virtual bool isEventNode()=0;

			virtual bool isCustomNode() = 0;



			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs() = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs() = 0;

			virtual std::shared_ptr<hv::v2::iconstNode> input(std::string key) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> output(std::string key) = 0;

			virtual void replaceInputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs) = 0;
			virtual void replaceOuputs(std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs) = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> inputClone() = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> outputClone() = 0;

			virtual std::vector<std::size_t> constUID() = 0;
			virtual std::vector<std::size_t> inputConstUID() = 0;
			virtual std::vector<std::size_t> outputConstUID() = 0;

			virtual hv::v2::resultType process() = 0;
			virtual void updateConst(int nodeType, std::size_t uid) = 0;


			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> results() = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> result(std::string key) = 0;
			virtual void replaceResults(std::vector<std::shared_ptr<hv::v2::iconstNode>> result)= 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> resultsClone() = 0;

			virtual std::shared_ptr<hv::v2::icompositeNode> clone(hv::v2::ihandle * context) = 0;


			virtual void addConstNode(std::string key, int objectType, hv::v2::searchType type) = 0;
			virtual void addConstMultipleNode(std::string key, int objectType, hv::v2::searchType type) = 0;
			virtual void addConstExecutionNode(std::string key, int objectType, hv::v2::searchType type) = 0;


			virtual void removeConstNode(std::string key, hv::v2::searchType type) = 0;

		protected:

			virtual void isEventNode(bool check) = 0;
			virtual void isCustomNode(bool value) = 0;

			virtual std::shared_ptr<hv::v2::iconstNode> search(std::string key, int objectType, hv::v2::searchType type)=0;
			template<typename T> std::shared_ptr<T> search(std::string key, int objectType, hv::v2::searchType type) {
				try {

					auto node = this->search(key, objectType, type);
					return std::dynamic_pointer_cast<T>(node);
				}
				catch (std::exception e) {
					throw e;
				}
			}
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> searchMultipleNode(std::string key, int objectType, hv::v2::searchType type) = 0;


			virtual void registerNode(std::string key, int objectType, hv::v2::searchType type) = 0;
			virtual void registerMultipleNode(std::string key, int objectType, hv::v2::searchType type) = 0;
			virtual void registerExecutionNode(std::string key, hv::v2::searchType type) = 0;

			virtual std::shared_ptr<hv::v2::irunable> execution(std::string key) = 0;
		};
	}
}

#endif
