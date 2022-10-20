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


        


        while (true) {

            context.loadLibrary();
            context.unloadLibrary();


        }
        

    }
    catch (hv::v2::oexception e) {
        std::cout << e.what() << std::endl;
    }


}
