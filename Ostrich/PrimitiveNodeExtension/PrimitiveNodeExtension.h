#pragma once




using namespace System;
using namespace System::Windows::Media::Imaging;


namespace HV {
	namespace V2 {
		namespace Extension {
			public ref class PrimitiveNode {

	
			public:
				static PrimitiveNode() {

				}

				static void UpdateConstNumberNodeData(System::IntPtr pointer, double value);
				static double FindConstNumberNodeData(System::IntPtr pointer);


				static WriteableBitmap^ FindConstImageNodeImage(System::IntPtr pointer);


			
			};
		};
	};
};