#pragma once

#ifndef OSTRICH_CONTEXT_STATUS
#define OSTRICH_CONTEXT_STATUS


namespace hv {
	namespace v2 {

		enum class contextStatus {
			LOOP_CONTINUE,
			LOOP_BREAK,
			CONTINUE,
			STOP,
		};
	}
}



#endif