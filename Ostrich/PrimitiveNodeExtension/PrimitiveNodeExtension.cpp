

#include <msclr/marshal_cppstd.h>


//C++/CLI Header
#include "PrimitiveNodeExtension.h"



//C++ Header
#include <constNumberNode.h>
#include <constImageNode.h>
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
			throw gcnew System::Exception("Invalid object type, its not constImageNode");
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



WriteableBitmap^ HV::V2::Extension::PrimitiveNode::FindConstImageNodeImage(System::IntPtr pointer) {
	try {
		auto constNode = *(std::shared_ptr <hv::v2::iconstNode>*)pointer.ToPointer();
		if (constNode->type() != 3) {
			throw gcnew System::Exception("Invalid object type, its not constImageNode");
		}
		auto constImageNode = std::dynamic_pointer_cast<hv::v2::constImageNode>(constNode);
		



		System::Windows::Media::PixelFormat format = System::Windows::Media::PixelFormats::Gray8;

		switch (constImageNode->channel())
		{
		case 1:
			format = System::Windows::Media::PixelFormats::Gray8;
			break;

		case 3:
			format = System::Windows::Media::PixelFormats::Bgr24;
			break;
		default:
			throw gcnew System::Exception(gcnew System::String("Invalid channel info"));
			break;
		}

		auto image = WriteableBitmap::Create(constImageNode->width(),
											 constImageNode->height(),
											 96,
											 96,
											 format,
											 nullptr,
											 System::IntPtr(constImageNode->data()),
											 (int)constImageNode->size(),
											 constImageNode->stride());

		WriteableBitmap^ writeableImage = gcnew WriteableBitmap(image);
		writeableImage->Freeze();

		return writeableImage;

	}
	catch (hv::v2::oexception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
	catch (std::exception e) {
		throw gcnew System::Exception(gcnew System::String(e.what()));
	}
}