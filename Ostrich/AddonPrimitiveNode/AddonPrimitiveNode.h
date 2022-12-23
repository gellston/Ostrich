#pragma once


#include <binding.h>


#include <constNumberNode.h>
#include <compositeNumberNode.h>
#include <compositeStartNode.h>
#include <compositeEndNode.h>
#include <compositeForNode.h>
#include <compositeSleepNode.h>
#include <compositeAddNumberNode.h>
#include <compositeSumNumberNode.h>

OSTRICH_MODULE()
OSTRICH_SANITY_CHECK()
OSTRICH_VERSION(1.0)
OSTRICH_NAME(PrimitiveNode)
OSTRICH_ADDON_INIT(context) {

	try {
		auto _addon = hv::v2::addon::createAddon();
		//1번째 상수노드는 Execution Node임. 이건 모든 노드가 가질 수 있는 노드임.
		_addon->addConst<hv::v2::constNumberNode>(2, "Constant", "ConstNumberNode");
		_addon->addComposite<hv::v2::compositeNumberNode>(50001, "Variable", "Number");
		_addon->addComposite<hv::v2::compositeStartNode>(50002, "Condition", "Start");
		_addon->addComposite<hv::v2::compositeEndNode>(50003, "Condition", "End");
		_addon->addComposite<hv::v2::compositeForNode>(50004, "Loop", "For");
		_addon->addComposite<hv::v2::compositeSleepNode>(50005, "Function", "Sleep");
		_addon->addComposite<hv::v2::compositeAddNumberNode>(50006, "Function", "AddNumber");
		_addon->addComposite<hv::v2::compositeSumNumberNode>(50007, "Function", "SumNumber");

		context->registerAddon(_addon, 9999);

		return true;
	}
	catch (hv::v2::oexception e) {
		return false;
	}
	return true;
}
