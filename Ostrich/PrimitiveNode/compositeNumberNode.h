#pragma once



#ifndef OSTRICH_COMPOSITE_NUMBER_NODE
#define OSTRICH_COMPOSITE_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeNumberNode;
		class compositeNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeNumberNode> _instance;
		public:
			compositeNumberNode(std::string name, hv::v2::ihandle * context);
			virtual ~compositeNumberNode();

		
			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeNumberNode)

		};

	}
}

#endif