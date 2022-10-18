// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <context.h>
#include <compositeNumberNode.h>
#include <constNumberNode.h>
#include <chrono>

int main()
{


    std::string current_path = "C://Github//Ostrich//Ostrich//x64//Debug//";
    std::cout << "current execution path = " << current_path << std::endl;

    
    try {
        hv::v2::context context;
        context.setAddonPath(current_path);
        context.loadLibrary();


        // node 생성
        // node 생성
        // node 생성
        auto start = context.addNode("Start", 50002);
        auto end = context.addNode("End", 50003);
        auto var1 = context.addNode("variable1", 50001);
        auto var2 = context.addNode("variable2", 50001);
        auto add = context.addNode("add", 50006);
        auto sleepNode = context.addNode("Sleep", 50005);
        context.verification();


        // node 연결
        // node 연결
        // node 연결
        context.connect(start, "Exec", add, "Exec");
        context.connect(add, "Exec", sleepNode, "Exec");
        context.connect(sleepNode, "Exec", end, "Exec");
        context.connect(var1, "output", add, "x1");
        context.connect(var2, "output", add, "x2");
        context.verification();

        auto input1 = std::dynamic_pointer_cast<hv::v2::constNumberNode>(var1->input("input"));
        auto input2 = std::dynamic_pointer_cast<hv::v2::constNumberNode>(var2->input("input"));
        auto us = std::dynamic_pointer_cast<hv::v2::constNumberNode>(sleepNode->input("us"));

        input1->data(55);
        input2->data(8);
        us->data(1000);

        auto y = std::dynamic_pointer_cast<hv::v2::constNumberNode>(add->output("y"));


        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        int count = 0;
        while (true) {
            //노드 실행
            context.run(start->uid());

            //std::cout << "y = " << y->data() << std::endl;

            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            if (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > 1000) {
                
                std::cout << "fps : " << count << std::endl;

                begin = std::chrono::steady_clock::now();
                count = 0;
            }
            count++;
        }
        

    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }


}
