// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <context.h>
#include <compositeNumberNode.h>
#include <constNumberNode.h>
#include <chrono>
#include <thread>


int main()
{


    std::string current_path = "C://Github//Ostrich//Ostrich//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;

    
    try {

        hv::v2::context context;
        context.setAddonPath(current_path);



        context.loadLibrary();


        auto start = context.addNode("start", 50002);
        auto end1 = context.addNode("end1", 50003);
        auto end2 = context.addNode("end2", 50003);
        auto loop = context.addNode("loop", 50004);
        auto sleep = context.addNode("sleep", 50005);


        context.connect(start, "Exec", loop, "Exec");
        context.connect(loop, "Complete", end1, "Exec");
        context.connect(loop, "Loop", sleep, "Exec");
        context.connect(sleep, "Exec", end2, "Exec");

        auto ms = std::dynamic_pointer_cast<hv::v2::constNumberNode>(sleep->input("ms"));
        auto count = std::dynamic_pointer_cast<hv::v2::constNumberNode>(loop->input("count"));


        ms->data(10000);
        count->data(10);


        while (true) {

            std::cout << "===========================================" << std::endl;
            context.run();
            std::cout << "===========================================" << std::endl;
            
         
        }
        

    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }


}
