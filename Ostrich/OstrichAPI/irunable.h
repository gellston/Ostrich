#pragma once


#ifndef OSTRICH_IRUNABLE
#define OSTRICH_IRUNABLE


#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "resultType.h"

namespace hv {
	namespace v2 {
		class irunable {
		public:

			virtual ~irunable() { }

			virtual hv::v2::resultType process() = 0;

		};
	}
}

#endif
