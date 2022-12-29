#pragma once




using namespace System;



namespace HV {
	namespace V2 {
		namespace Extension {
			public ref class PrimitiveNode {

	
			public:
				static PrimitiveNode() {

				}

				static void UpdateConstNumberNodeData(System::IntPtr pointer, double value);
				static double FindConstNumberNodeData(System::IntPtr pointer);
			};
		};
	};
};