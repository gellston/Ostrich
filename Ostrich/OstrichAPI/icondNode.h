#pragma once


#ifndef OSTRICH_ICONDITIONAL_NODE
#define OSTRICH_ICONDITIONAL_NODE


#include "ivarNode.h"


#include <iostream>

namespace hv {
	namespace v2 {
		class icondNode : public hv::v2::ivarNode {
		public:

			virtual ~icondNode() { }

			virtual void addInCondition(std::string key, std::shared_ptr<ivarNode> node) = 0;
			virtual void removeInCondition(std::string key, std::shared_ptr<ivarNode> node) = 0;





		};
	}
}

#endif
