#pragma once


#ifndef OSTRICH_ICOMPOSITENODE
#define OSTRICH_ICOMPOSITENODE


#include "inode.h"
#include "iconstNode.h"
#include "searchType.h"




#include <iostream>


namespace hv {
	namespace v2 {
		class icompositeNode : public hv::v2::inode {
		public:

			virtual ~icompositeNode() { }

			virtual int depth() = 0;
			virtual void depth(int value) = 0;

			virtual bool isConnected() = 0;
			virtual bool checkSourceUID(std::size_t uid) = 0;

			virtual bool isFreezed() = 0;
			virtual void isFreezed(bool value) = 0;

			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs() = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs() = 0;

			virtual std::shared_ptr<hv::v2::iconstNode> input(std::string key) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> output(std::string key) = 0;


			virtual std::vector<std::size_t> constUID() = 0;


		protected:
			
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
			virtual void registerNode(std::string key, int objectType, hv::v2::searchType type) = 0;
			virtual void registerExecutionNode(std::string key, hv::v2::searchType type) = 0;

			virtual std::shared_ptr<hv::v2::irunable> execution(std::string key) = 0;
		};
	}
}

#endif
