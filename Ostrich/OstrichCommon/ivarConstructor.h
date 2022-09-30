#pragma once


#ifndef OSTRICH_IVARCONSTRUCTOR
#define OSTRICH_IVARCONSTRUCTOR


#include "iconstructor.h"
#include "ivarNode.h"

namespace hv {
	namespace v2 {
		
		class ivarConstructor : public hv::v2::iconstructor {

		public:
			virtual ~ivarConstructor() {  };
			virtual std::shared_ptr<hv::v2::ivarNode> create(std::string name, std::shared_ptr<hv::v2::ihandle> context) = 0;
		};
	}
}


#endif