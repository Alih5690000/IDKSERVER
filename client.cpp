#include "httplib.h"
#include <iostream>

int main(){
    httplib::Client cli("localhost:8000");
    auto res=cli.Get("/hello");
    if (!res){
        std::cout<<"Fuck "<<res.error()<<std::endl;
        return 1;
    }

    auto rr=cli.Post("/set", "6752;A;lol", "text/plain");
    if (!rr){
        std::cout<<"POST failed "<<rr.error()<<std::endl;
    }
    
    auto r=cli.Post("/get", "6752;A", "text/plain");
    if (!r) {
        std::cout << "POST failed: " << r.error() << '\n';
        return 1;
    }

    std::cout << "Size: " << r->body.size() << '\n';

    for (unsigned char c : r->body) {
        std::cout << std::hex << static_cast<int>(c) << ' ';
    }

    std::cout << '\n';
    std::cout<<"Response is "<<r->body.data()<<std::endl;
}