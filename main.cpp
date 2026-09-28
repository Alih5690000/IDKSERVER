#include "httplib.h"
#include <iostream>

int main(){
    httplib::Server server;
    server.Get("/hello", [](auto& req, auto& res){
        std::cout<<"Got request"<<std::endl;
        res.body="lol";
    });
    server.listen("0.0.0.0",8000);
}