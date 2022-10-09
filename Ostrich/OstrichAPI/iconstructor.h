#pragma once


#ifndef OSTRICH_ICONSTRUCTOR
#define OSTRICH_ICONSTRUCTOR



#include "ihandle.h"
#include "constructorType.h"

namespace hv {
	namespace v2 {

		class iconstructor : public hv::v2::ihandle {

		public:
			virtual ~iconstructor() {  };
			virtual hv::v2::constructorType type() = 0;

		};
	}
}


#endif