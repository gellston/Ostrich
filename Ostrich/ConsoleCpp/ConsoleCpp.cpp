// ConsoleCpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <context.h>
#include <compositeNumberNode.h>
#include <constNumberNode.h>

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
        auto end1 = context.addNode("End", 50003);
        auto end2 = context.addNode("End2", 50003);
        auto end3 = context.addNode("End3", 50003);
        auto loopCount = context.addNode("Count", 50001);
        auto forNode = context.addNode("For", 50004);
        auto sleepNode = context.addNode("Sleep", 50005);
        context.verification();


        // node 연결
        // node 연결
        // node 연결
        context.connect(start, "Exec", loopCount, "Exec");
        context.connect(loopCount, "Exec", forNode, "Exec");
        context.connect(forNode, "Complete", end1, "Exec");
        context.connect(forNode, "Loop", sleepNode, "Exec");
        context.connect(loopCount, "output", forNode, "count");
        context.connect(sleepNode, "Exec", end2, "Exec");
        context.verification();

        // 상수 설정
        // sleep 시간 설정
        auto sleepTime = std::dynamic_pointer_cast<hv::v2::constNumberNode>(sleepNode->input("us"));
        sleepTime->data(1000);

        // 반복 횟수 설정
        auto forCount = std::dynamic_pointer_cast<hv::v2::constNumberNode>(loopCount->input("input"));
        forCount->data(10);

        //시작 위치 uid 가져오기
        auto startUID = start->uid();

        //노드 실행
        context.run(startUID);

        

    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }


}
