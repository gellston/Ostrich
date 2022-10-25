#pragma once


#ifndef OSTRICH_CONST_NODE
#define OSTRICH_CONST_NODE


#include "node.h"
#include "iconstNode.h"



namespace hv {
	namespace v2 {
		class impl_constNode;
		class constNode : public hv::v2::node, public hv::v2::iconstNode{
		private:
			std::unique_ptr<hv::v2::impl_constNode> _instance;

		public:
			OSTRICH_COMMON_API constNode(std::string value, int type);
			OSTRICH_COMMON_API virtual ~constNode() override;

			OSTRICH_COMMON_API bool isConnected() override;
			OSTRICH_COMMON_API void isConnected(bool value) override;

			OSTRICH_COMMON_API int index() override;
			OSTRICH_COMMON_API void index(int _index) override;


			OSTRICH_COMMON_API std::size_t sourceUID() override;
			OSTRICH_COMMON_API void sourceUID(std::size_t value) override;


			OSTRICH_COMMON_API std::string sourceName() override;
			OSTRICH_COMMON_API void sourceName(std::string value) override;




			OSTRICH_COMMON_API std::string name() override;
	

			OSTRICH_COMMON_API int type() override;


			OSTRICH_COMMON_API std::size_t uid() override;
			OSTRICH_COMMON_API void uid(std::size_t value) override;



		};
	}
}

#endif