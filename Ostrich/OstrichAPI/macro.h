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


#ifndef OSTRICH_CLONE_PATTERN_MACRO
#define OSTRICH_CLONE_PATTERN_MACRO

#define CLONE_PATTERN(CLASS_TYPE) \
std::shared_ptr<hv::v2::icompositeNode> clone(hv::v2::ihandle* context) {\
try {\
	auto object = std::make_shared<hv::v2::CLASS_TYPE>(this->name(), context);\
	object->uid(this->uid());\
	object->depth(this->depth());\
	object->isFreezed(this->isFreezed());\
	object->replaceInputs(this->inputs());\
	object->replaceOuputs(this->outputs());\
	return object;\
}\
catch (hv::v2::oexception e) {\
	std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());\
	throw hv::v2::oexception(message);\
}\
catch (std::exception e) {\
	std::string message = hv::v2::generate_error_message(__FUNCTION__, __LINE__, e.what());\
	throw hv::v2::oexception(message);\
}\
}\

#endif