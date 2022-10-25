// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <context.h>
#include <compositeNumberNode.h>
#include <constNumberNode.h>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>
#include <script.h>


int main()
{



    std::string current_path = "C://Github//Ostrich//Ostrich//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;

    
    try {
        /*
        auto start = context->addNode("start", 50002);
        auto end1 = context->addNode("end1", 50003);
        auto end2 = context->addNode("end2", 50003);
        auto loop = context->addNode("loop", 50004);
        auto sleep = context->addNode("sleep", 50005);


        context->connect(start, "Exec", loop, "Exec");
        context->connect(loop, "Complete", end1, "Exec");
        context->connect(loop, "Loop", sleep, "Exec");
        context->connect(sleep, "Exec", end2, "Exec");

        auto ms = std::dynamic_pointer_cast<hv::v2::constNumberNode>(sleep->input("ms"));
        auto count = std::dynamic_pointer_cast<hv::v2::constNumberNode>(loop->input("count"));
        */

        hv::v2::script _script;

        {
            _script.setAddonPath(current_path);
            _script.createContext("test");
            auto start = _script.addNode("test", "start", 50002);
            auto end1 = _script.addNode("test", "end1", 50003);
            auto end2 = _script.addNode("test", "end2", 50003);
            auto loop = _script.addNode("test", "loop", 50004);
            auto sleep = _script.addNode("test", "sleep", 50005);

            _script.connect("test", start, "Exec", loop, "Exec");
            _script.connect("test", loop, "Complete", end1, "Exec");
            _script.connect("test", loop, "Loop", sleep, "Exec");
            _script.connect("test", sleep, "Exec", end2, "Exec");

            auto ms = std::dynamic_pointer_cast<hv::v2::constNumberNode>(sleep->input("ms"));
            auto count = std::dynamic_pointer_cast<hv::v2::constNumberNode>(loop->input("count"));

            ms->data(5000);
            count->data(10);

            _script.copyContext("test", "test_copy");


            for (int index = 0; index < 1; index++) {
                std::cout << "===========================================" << std::endl;
                _script.run("test");
                std::cout << "===========================================" << std::endl;
            }

            for (int index = 0; index < 1; index++) {
                std::cout << "===========================================" << std::endl;
                _script.run("test_copy");
                std::cout << "===========================================" << std::endl;
            }

            _script.save("test", "C://Github//Ostrich//Ostrich//x64//Debug//test.json");
            _script.save("test_copy", "C://Github//Ostrich//Ostrich//x64//Debug//test_copy.json");

        }



        std::cout << "end" << std::endl;
    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }
    

}
