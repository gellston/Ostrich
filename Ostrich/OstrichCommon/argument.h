#pragma once


#ifndef OSTRICH_ARGUMENT
#define OSTRICH_ARGUMENT

#include <string>
#include <memory>
#include <initializer_list>
#include <tuple>
#include <variant>


#include "commonException.h"
#include "common_export.h"

namespace hv {
	namespace v2 {

		using arg = std::variant<bool, std::string, double, int>;

		class impl_argument;
		class argument {
		private:

			std::unique_ptr<impl_argument> _instance;
		public:
			
			OSTRICH_COMMON_API argument();
			OSTRICH_COMMON_API argument(std::initializer_list<std::tuple <std::string, arg>> list);
			OSTRICH_COMMON_API ~argument();


			template<typename T> T get(std::string key) {}
			template<typename T> T get(const char* key) {
				try {
					return this->get<T>(std::string(key));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}

			template<> OSTRICH_COMMON_API double get(std::string key);
			template<> OSTRICH_COMMON_API int get(std::string key);
			template<> OSTRICH_COMMON_API std::string get(std::string key);
			template<> OSTRICH_COMMON_API bool get(std::string key);

			template<typename T> void add(std::string key, T value) {}
			template<typename T> void add(const char* key, T value) {
				try {
					this->add<T>(std::string(key), value);
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}
			template<> OSTRICH_COMMON_API void add(std::string key, double value);
			template<> OSTRICH_COMMON_API void add(std::string key, int value);
			template<> OSTRICH_COMMON_API void add(std::string key, bool value);
			template<> OSTRICH_COMMON_API void add(std::string key, std::string value);
			template<> OSTRICH_COMMON_API void add(std::string key, const char* value);

			OSTRICH_COMMON_API std::string parse();
			OSTRICH_COMMON_API void print();

		};
	}


}



#endif