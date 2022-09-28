#pragma once


#ifndef OSTRICH_NODE_TYPE
#define OSTRICH_NODE_TYPE

namespace hv {
	namespace v2 {
		enum class nodeType {
			CONST_NODE = 0,
			VAR_NODE=50000,
			DEVICE_NODE=100000
		};
	}
}


#endif
