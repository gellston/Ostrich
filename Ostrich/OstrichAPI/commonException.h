#pragma once


#ifndef OSTRICH_COMMON_EXCEPTION
#define OSTRICH_COMMON_EXCEPTION

#include <stdexcept>


#include "common_export.h"

namespace hv {
	namespace v2 {
		

		class oexception : public std::runtime_error {
		public:
			OSTRICH_COMMON_API oexception(const std::string& message = "");
			OSTRICH_COMMON_API ~oexception();
		};

	}
}

#endif
