#pragma once


#ifndef OSTRICH_COMMON_EXCEPTION
#define OSTRICH_COMMON_EXCEPTION

#include <stdexcept>
#include <string>

#include "common_export.h"
#include "macro.h"

namespace hv {
	namespace v2 {
		class oexception : public std::runtime_error {
		public:
			OSTRICH_COMMON_API oexception(const std::string& message = "");
			OSTRICH_COMMON_API ~oexception();
		};


	}
}


#define START_ERROR_HANDLE() \
try{\



#define END_ERROR_HANDLE(function, line)\
}\
catch(hv::v2::oexception e){\
	std::string message = hv::v2::generate_error_message(function, line, e.what());\
	throw hv::v2::oexception(message);\
}\



#endif
