#pragma once



#ifndef OSTRICH_CONST_EXECUTION_NODE
#define OSTRICH_CONST_EXECUTION_NODE


#include "constNode.h"


namespace hv {
	namespace v2 {
		class impl_constExecutionNode;
		class constExecutionNode : public hv::v2::constNode {
		private:
			std::unique_ptr<hv::v2::impl_constExecutionNode> _instance;
		public:
			constExecutionNode(std::string name);
			~constExecutionNode();

			void init() override;
	
			
		};

	}
}

#endif