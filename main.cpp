#include "httplib.h"
#include <iostream>

int main(){
    httplib::Server server;
    server.Post("/hello", [](auto req, auto res){
        res.body="Lol";
    });
    server.listen("localhost",8000);
}