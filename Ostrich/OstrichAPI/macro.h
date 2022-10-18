#pragma once

#ifndef OSTRICH_COMMON_MACRO
#define OSTRICH_COMMON_MACRO


#include <string>

namespace hv {
	namespace v2 {

		inline std::string generate_error_message(const char* function_name, int line, std::string _context) {
			std::string full_context = "";
			full_context += "==========================\n";
			full_context += function_name;
			full_context += ":";
			full_context += std::to_string(line);
			full_context += ":";
			full_context += "\n";
			full_context += _context;
			full_context += "\n";
			full_context += "==========================\n";
			return full_context;
		}
	}
}



#endif