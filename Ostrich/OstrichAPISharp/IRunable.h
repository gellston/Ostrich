#pragma once

#include "ResultType.h"


namespace HV {
	namespace V2 {
		public interface class IRunable{
		public:

			virtual HV::V2::ResultType Call();


		};
	}
}