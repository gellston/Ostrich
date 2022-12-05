// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <context.h>
#include <compositeNumberNode.h>
#include <compositeSumNumberNode.h>

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
     
        hv::v2::script _script;
        {
            _script.setAddonPath(current_path);
            _script.createContext("test");


            while (true) {
                auto start = _script.addNode("test", "start", 50002);
                auto end = _script.addNode("test", "end", 50003);

                auto var1 = _script.addNode("test", "var1", 50001);
                auto var2 = _script.addNode("test", "var2", 50001);
                auto var3 = _script.addNode("test", "var3", 50001);

                auto sum = _script.addNode("test", "sum", 50007);

                _script.connect("test", start, "Exec", sum, "Exec");
                _script.connect("test", sum, "Exec", end, "Exec");

                _script.connect("test", var1, "output", sum, "x");
                _script.connect("test", var2, "output", sum, "x");
                _script.connect("test", var3, "output", sum, "x");


                auto converted_var1 = std::dynamic_pointer_cast<hv::v2::compositeNumberNode>(var1);
                auto converted_var2 = std::dynamic_pointer_cast<hv::v2::compositeNumberNode>(var2);
                auto converted_var3 = std::dynamic_pointer_cast<hv::v2::compositeNumberNode>(var3);
                auto converted_sum = std::dynamic_pointer_cast<hv::v2::compositeSumNumberNode>(sum);

                std::dynamic_pointer_cast<hv::v2::constNumberNode>(converted_var1->input("input"))->data(5);
                std::dynamic_pointer_cast<hv::v2::constNumberNode>(converted_var2->input("input"))->data(5);
                std::dynamic_pointer_cast<hv::v2::constNumberNode>(converted_var3->input("input"))->data(5);
                

                _script.run("test", start->uid());

                _script.verification("test");

                std::cout << "y = " << std::dynamic_pointer_cast<hv::v2::constNumberNode>(converted_sum->output("y"))->data() << std::endl;
                

                _script.save("test", "C://Github//Ostrich//Ostrich//x64//Debug//test.json");
                _script.load("test", "C://Github//Ostrich//Ostrich//x64//Debug//test.json");
                _script.clear("test");
            }

        }



        std::cout << "end" << std::endl;
    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }
    

}
