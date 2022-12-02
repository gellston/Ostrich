#pragma once


#ifndef OSTRICH_ICONST_NODE
#define OSTRICH_ICONST_NODE


#include "inode.h"


namespace hv {
	namespace v2 {
		class iconstNode : public hv::v2::inode {
		public:

			virtual ~iconstNode() { }



			virtual bool isConnected() = 0;
			virtual void isConnected(bool value) = 0;


			virtual bool isMultiple() = 0;
			virtual void isMultiple(bool value) = 0;


			virtual int index() = 0;
			virtual void index(int _index) =0;
			

			virtual std::size_t sourceUID() = 0;
			virtual void sourceUID(std::size_t value) = 0;


			virtual std::string sourceName() = 0;
			virtual void sourceName(std::string value) = 0;


			virtual std::vector<std::size_t> sourceMultiUID() = 0;
			virtual std::vector<std::string> sourceMultiNames() = 0;



			virtual void sourceMultiUID(std::vector<std::size_t> uids) = 0;
			virtual void sourceMultiNames(std::vector<std::string> names) = 0;


			virtual std::shared_ptr<hv::v2::iconstNode> clone() = 0;


		};
	}
}

#endif

