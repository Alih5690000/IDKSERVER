#include "httplib.h"
#include <iostream>

int main(){
    httplib::Client cli("localhost:8000");
    auto res=cli.Get("/hello");
    if (!res){
        std::cout<<"Fuck "<<res.error()<<std::endl;
        return 1;
    }
    std::cout<<"Response is "<<res->body<<std::endl;
}