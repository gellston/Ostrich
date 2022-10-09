#pragma once


#ifndef OSTRICH_INODE
#define OSTRICH_INODE


#include "ihandle.h"


#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace hv {
	namespace v2 {
		class inode : public hv::v2::ihandle {
		public:

			virtual ~inode() { }

			virtual std::string name() = 0;

			//virtual std::string nick() = 0;
			//virtual void nick(std::string value) = 0;


			virtual std::size_t uid() = 0;
			virtual void uid(std::size_t value) = 0;


			virtual int type() = 0;
			virtual void init() = 0;

		};
	}
}

#endif
