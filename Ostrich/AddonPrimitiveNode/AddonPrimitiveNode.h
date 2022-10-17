#pragma once


#include <binding.h>


#include <constNumberNode.h>
#include <compositeNumberNode.h>


OSTRICH_MODULE()
OSTRICH_VERSION(1.0)
OSTRICH_NAME(PrimitiveNode)
OSTRICH_ADDON_INIT(context) {

	try {
		auto _addon = hv::v2::addon::createAddon();
		_addon->addConst<hv::v2::constNumberNode>(1, "Constant");
		_addon->addComposite<hv::v2::compositeNumberNode>(50001, "Variable");


		context->registerAddon(_addon, 9999);

		return true;
	}
	catch (hv::v2::oexception e) {
		return false;
	}
	return true;
}
