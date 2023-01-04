#pragma once



#ifndef OSTRICH_COMPOSITE_SUBSTRACT_NUMBER_NODE
#define OSTRICH_COMPOSITE_SUBSTRACT_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeSubstractNumberNode;
		class compositeSubstractNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeSubstractNumberNode> _instance;
		public:
			compositeSubstractNumberNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeSubstractNumberNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeSubstractNumberNode)

		};

	}
}

#endif