#pragma once


#ifndef OSTRICH_COMPOSITE_CONSTRUCTOR
#define OSTRICH_COMPOSITE_CONSTRUCTOR


#include "icompositeConstructor.h"
#include "commonException.h"

namespace hv {
	namespace v2 {
		template<typename T> class compositeConstructor : public hv::v2::icompositeConstructor {
		public:

			compositeConstructor() {}
			virtual ~compositeConstructor() {}

			std::shared_ptr<hv::v2::icompositeNode> create(std::string name, hv::v2::ihandle * context) override {
				try {
					return std::dynamic_pointer_cast<hv::v2::icompositeNode>(std::make_shared<T>(name, context));
				}
				catch (hv::v2::oexception e) {
					throw e;
				}
			}

			hv::v2::constructorType type() override {
				return hv::v2::constructorType::compositeConstructor;
			}

		};
	}
}

#endif