#pragma once


#ifndef OSTRICH_IVARNODE
#define OSTRICH_IVARNODE


#include "inode.h"
#include "iconstNode.h"
#include "searchType.h"




#include <iostream>


namespace hv {
	namespace v2 {
		class ivarNode : public hv::v2::inode {
		public:

			virtual ~ivarNode() { }



			virtual int depth() = 0;
			virtual void depth(int value) = 0;




			virtual bool inCondition() = 0;
			virtual void inCondition(bool value) = 0;
			virtual bool isConditionalNode() = 0;
			virtual void process() = 0;
		


			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> inputs() = 0;
			virtual std::vector<std::shared_ptr<hv::v2::iconstNode>> outputs() = 0;

			virtual std::shared_ptr<hv::v2::iconstNode> input(std::string key) = 0;
			virtual std::shared_ptr<hv::v2::iconstNode> output(std::string key) = 0;


		protected:
			virtual void isConditionalNode(bool value) = 0;
			
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
		};
	}
}

#endif
