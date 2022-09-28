#pragma once


#ifndef OSTRICH_INODE
#define OSTRICH_INODE


#include "ihandle.h"


#include <iostream>
#include <string>

namespace hv {
	namespace v2 {
		class inode : public hv::v2::ihandle {
		public:

			virtual ~inode() { }

			virtual std::string name() = 0;
			virtual void name(std::string value) = 0;
			virtual int type() = 0;

			virtual void init() = 0;

		};
	}
}

#endif
