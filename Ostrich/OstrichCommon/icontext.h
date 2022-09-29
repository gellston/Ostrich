#pragma once


#ifndef OSTRICH_ICONTEXT
#define OSTRICH_ICONTEXT


#include "ihandle.h"
#include "inode.h"
#include "ivarNode.h"

namespace hv {
	namespace v2 {
		class icontext : public hv::v2::ihandle {
		public:

			virtual ~icontext() { }


			virtual std::shared_ptr<hv::v2::inode> search(std::size_t uid) = 0;
			virtual std::shared_ptr<hv::v2::inode> search(std::string nick) = 0;

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

			virtual void verification() = 0;
			virtual void clear() = 0;

			virtual int maxDepth() = 0;
			virtual void maxDepth(int value) = 0;

			virtual std::string serialization() = 0;
			virtual void deserialization(std::string value) = 0;

		};
	}
}

#endif
