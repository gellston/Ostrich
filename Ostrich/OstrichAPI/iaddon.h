#pragma once


#ifndef OSTRICH_IADDON
#define OSTRICH_IADDON


#include "ihandle.h"
#include "icompositeConstructor.h"
#include "iconstConstructor.h"
#include "nodeInfo.h"

#include <memory>
#include <vector>

namespace hv {
	namespace v2 {
		class iaddon {

		public:

			virtual ~iaddon() {}

			virtual bool exist(int type) = 0;
			virtual std::shared_ptr<hv::v2::icompositeConstructor> compositeConstructor(int type) = 0;
			virtual std::shared_ptr<hv::v2::iconstConstructor> constConstructor(int type) = 0;
			virtual std::vector<std::shared_ptr<hv::v2::nodeInfo>> information() = 0;



		};
	}
}

#endif