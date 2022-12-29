

#include <msclr/marshal_cppstd.h>


//C++/CLI Header
#include "PrimitiveNodeExtension.h"



//C++ Header
#include <constNumberNode.h>
#include <commonException.h>




void HV::V2::Extension::PrimitiveNode::UpdateConstNumberNodeData(IntPtr _constNode, double value) {
	try {
		auto constNode = *(std::shared_ptr <hv::v2::iconstNode>*)_constNode.ToPointer();
		if (constNode->type() != 2) {
			throw gcnew System::Exception("Invalid object type, its not constNumberNode");
		}
		auto constNumberNode = std::dynamic_pointer_cast<hv::v2::constNumberNode>(constNode);
		constNumberNode->data(value);
	}
	catch (hv::v2::oexception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
}



double HV::V2::Extension::PrimitiveNode::FindConstNumberNodeData(IntPtr _constNode) {

	try {
		auto constNode = *(std::shared_ptr <hv::v2::iconstNode>*)_constNode.ToPointer();
		if (constNode->type() != 2) {
			throw gcnew System::Exception("Invalid object type, its not constNumberNode");
		}
		auto constNumberNode = std::dynamic_pointer_cast<hv::v2::constNumberNode>(constNode);
		return constNumberNode->data();
	}
	catch (hv::v2::oexception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
}