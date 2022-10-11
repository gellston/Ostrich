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



			virtual std::size_t sourceUID() = 0;
			virtual void sourceUID(std::size_t value) = 0;


			virtual std::string sourceName() = 0;
			virtual void sourceName(std::string value) = 0;



		};
	}
}

#endif

