#pragma once


#ifndef OSTRICH_IVARNODE
#define OSTRICH_IVARNODE


#include "inode.h"


#include <iostream>

namespace hv {
	namespace v2 {
		class ivarNode : public hv::v2::inode {
		public:

			virtual ~ivarNode() { }

			virtual int depth() = 0;
			virtual void depth(int value) = 0;

			virtual std::size_t uid() = 0;
			virtual void uid(std::size_t value) = 0;

			virtual bool inCondition() = 0;
			virtual void inCondition(bool value) = 0;
			virtual void process() = 0;


		};
	}
}

#endif
