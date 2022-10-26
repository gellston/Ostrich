#pragma once



#ifndef OSTRICH_COMPOSITE_END_NODE
#define OSTRICH_COMPOSITE_END_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeEndNode;
		class compositeEndNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeEndNode> _instance;
		public:
			compositeEndNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeEndNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeEndNode)
		};

	}
}

#endif