#pragma once


#ifndef OSTRICH_OBJECT_TYPE
#define OSTRICH_OBJECT_TYPE

namespace hv {
	namespace v2 {
		enum class objectType {
			CONST_NODE = 0,
			CONST_EXECUTION = 1,
			COMPOSITE_NODE=50000,
			DEVICE_NODE=100000
		};
	}
}


#endif
