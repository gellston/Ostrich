#pragma once


#ifndef OSTRICH_VARCONSTRUCTOR
#define OSTRICH_VARCONSTRUCTOR


#include "ivarConstructor.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		template<typename T> class varConstructor : public hv::v2::ivarConstructor {
		public:

			varConstructor() {}
			virtual ~varConstructor() {}

			std::shared_ptr<hv::v2::ivarNode> create(std::string name, hv::v2::ihandle * context) override {
				try {
					return std::dynamic_pointer_cast<hv::v2::ivarNode>(std::make_shared<T>(name, context));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}

			hv::v2::constructorType type() override {
				return hv::v2::constructorType::varConstructor;
			}

		};
	}
}

#endif