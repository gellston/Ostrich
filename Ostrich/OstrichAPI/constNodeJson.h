#pragma once


#ifndef OSTRICH_CONST_NODE_JSON
#define OSTRICH_CONST_NODE_JSON


#include <string>
#include <memory>

namespace hv {
	namespace v2 {
		class impl_constNodeJson;
		class constNodeJson {
		private:
			std::unique_ptr<hv::v2::impl_constNodeJson> _instance;
		public:
			constNodeJson(std::string json);
			~constNodeJson();

			void add(std::string key, double number);
			void add(std::string key, int integer);
			void add(std::string key, std::string context);


			double number(std::string key);
			int integer(std::string key);
			std::string context(std::string key);

		};
	}
}



#endif