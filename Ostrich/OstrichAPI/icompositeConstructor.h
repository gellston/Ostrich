#pragma once


#ifndef OSTRICH_ICOMPOSITE_CONSTRUCTOR
#define OSTRICH_ICOMPOSITE_CONSTRUCTOR


#include "iconstructor.h"
#include "icompositeNode.h"

namespace hv {
	namespace v2 {
		
		class icompositeConstructor : public hv::v2::iconstructor {

		public:
			virtual ~icompositeConstructor() {  };
			virtual std::shared_ptr<hv::v2::icompositeNode> create(std::string name, hv::v2::ihandle* context) = 0;
		};
	}
}


#endif