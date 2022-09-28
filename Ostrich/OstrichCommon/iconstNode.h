#pragma once


#ifndef OSTRICH_CONST_NODE
#define OSTRICH_CONST_NODE


#include "inode.h"

namespace hv {
	namespace v2 {
		class iconstNode : public hv::v2::inode {
		public:

			virtual ~iconstNode() { }


			virtual std::size_t targetUID() = 0;
			virtual void targetUID(std::size_t value) = 0;
			virtual std::string targetName() = 0;
			virtual void targetName(std::string value) = 0;


		};
	}
}

#endif

