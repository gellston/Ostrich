#pragma once



#ifndef OSTRICH_VAR_NUMBER_NODE
#define OSTRICH_VAR_NUMBER_NODE


#include <varNode.h>

namespace hv {
	namespace v2 {
		class impl_varNumberNode;
		class varNumberNode : public hv::v2::varNode {
		private:
			std::unique_ptr<hv::v2::impl_varNumberNode> _instance;
		public:
			varNumberNode(std::string name, hv::v2::ihandle * context);
			~varNumberNode();

		
			void init() override;
			void process() override;
		};

	}
}

#endif