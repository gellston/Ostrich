#pragma once



#ifndef OSTRICH_COMPOSITE_DIVIDE_NUMBER_NODE
#define OSTRICH_COMPOSITE_DIVIDE_NUMBER_NODE


#include <compositeNode.h>

namespace hv {
	namespace v2 {
		class impl_compositeDivideNumberNode;
		class compositeDivideNumberNode : public hv::v2::compositeNode {
		private:
			std::unique_ptr<hv::v2::impl_compositeDivideNumberNode> _instance;
		public:
			compositeDivideNumberNode(std::string name, hv::v2::ihandle* context);
			virtual ~compositeDivideNumberNode();


			void init() override;
			hv::v2::resultType process() override;

			COMPOSITE_NODE_CLONE_PATTERN(compositeDivideNumberNode)

		};

	}
}

#endif