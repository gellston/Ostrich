#pragma once


#ifndef OSTRICH_NODE_INFO
#define OSTRICH_NODE_INFO


#include <string>
#include <memory>


#include "argument.h"


namespace hv {
	namespace v2 {
		class impl_nodeInfo;
		class nodeInfo {

		private:
			std::unique_ptr<impl_nodeInfo> _instance;

		public:
			
			OSTRICH_COMMON_API nodeInfo(std::string name, std::shared_ptr<hv::v2::argument> arg);
			OSTRICH_COMMON_API ~nodeInfo();

			OSTRICH_COMMON_API std::string name();
			OSTRICH_COMMON_API std::string category();
			OSTRICH_COMMON_API std::string nodeName();
			OSTRICH_COMMON_API int type();
		};
	}
}

#endif
