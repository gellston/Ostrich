#pragma once


#ifndef OSTRICH_RAII
#define OSTRICH_RAII


#include <functional>



namespace hv {
	namespace v2 {
		class raii {
		private:
			std::function<void()> _call;
		public:

			raii(std::function<void()> call) {
				this->_call = call;
			}

			~raii() {
				this->_call();
			}

		};
	}
}

#endif