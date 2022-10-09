#pragma once


#ifndef OSTRICH_ICONSTCONSTRUCTOR
#define OSTRICH_ICONSTCONSTRUCTOR


#include "iconstructor.h"
#include "iconstNode.h"

namespace hv {
	namespace v2 {

		class iconstConstructor : public hv::v2::iconstructor {

		public:
			virtual ~iconstConstructor() {  };
			virtual std::shared_ptr<hv::v2::iconstNode> create(std::string name) = 0;
		};
	}
}


#endif