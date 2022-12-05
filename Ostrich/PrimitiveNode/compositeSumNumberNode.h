#pragma once



#ifndef OSTRICH_COMPOSITE_SUM_NUMBER_NODE
#define OSTRICH_COMPOSITE_SUM_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeSumNumberNode;
		class compositeSumNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeSumNumberNode> _instance;
		public:
			compositeSumNumberNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeSumNumberNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeSumNumberNode)

		};

	}
}

#endif