#pragma once



#ifndef OSTRICH_COMPOSITE_MULTIPLY_NUMBER_NODE
#define OSTRICH_COMPOSITE_MULTIPLY_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeMultiplyNumberNode;
		class compositeMultiplyNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeMultiplyNumberNode> _instance;
		public:
			compositeMultiplyNumberNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeMultiplyNumberNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeMultiplyNumberNode)

		};

	}
}

#endif