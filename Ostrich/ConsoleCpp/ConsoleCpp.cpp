// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <context.h>

#include <varNumberNode.h>
#include <constNumberNode.h>

int main()
{


    std::string current_path = "C://Github//Ostrich//Ostrich//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;

    
    try {
        hv::v2::context context;
        context.setAddonPath(current_path);
        context.loadLibrary();

        auto node1 = context.addNode("test1", 50001);
        auto node2 = context.addNode("test2", 50001);

        context.verification();

        context.connect(node1, "output", node2, "input");

        context.verification();

        auto input = std::dynamic_pointer_cast<hv::v2::constNumberNode>(node1->input("input"));
        auto output = std::dynamic_pointer_cast<hv::v2::constNumberNode>(node2->output("output"));

        
        input->data(888);


        context.run(hv::v2::syncType::sequential_execution);


        context.verification();

       
        std::cout << "result = " << output->data() << std::endl;


    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }


}
