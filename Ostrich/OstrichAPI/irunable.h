#pragma once


#ifndef OSTRICH_IRUNABLE
#define OSTRICH_IRUNABLE


#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace hv {
	namespace v2 {
		class irunable {
		public:

			virtual ~irunable() { }

			virtual void process() = 0;

		};
	}
}

#endif
