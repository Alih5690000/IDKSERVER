#include "httplib.h"
#include "db.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <ctime>
#include <mutex>
#define PWD 6752

std::vector<std::string> splitBy(std::string s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : s) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(){
    DataBase db("data.db");
    db.AddInt("A",5);
    db.WriteTo("data.db");
    std::thread thread([&db](int cd){
        time_t timer;
        time_t start,end;
        time_t dt;
        while (true){
            start=time(NULL);
            dt=start-end;
            timer+=dt;
            if (timer>cd){
                timer%=cd;
                DataBase d=db;
                d.WriteTo("data.db");
            }
        }
    }, 2000);
    httplib::Server server;
    server.Get("/hello", [](auto& req, auto& res){
        std::cout<<"Got request"<<std::endl;
        res.body="lol";
    });
    server.Post("/get", [&db](auto& req, auto& res){
        std::cout<<"Req is "<<req.body<<std::endl;
        auto v=splitBy(req.body,';');
        if (v.size()!=2){ 
            res.body="Invalid format";
            return;
        }
        int num=stoi(v[0]);
        if (num==PWD){
            std::vector<uint8_t> bytes=db.attrs[v[1]];
            res.body.resize(bytes.size());
            memcpy(res.body.data(), bytes.data(), bytes.size());
        }
        else{
            res.body="Invalid password";
        }
    });
    server.Post("/set", [&db](auto& req, auto& res){
        std::cout<<"Req is "<<req.body<<std::endl;
        auto v=splitBy(req.body,';');
        if (v.size()!=3){ 
            res.body="Invalid format";
            return;
        }
        int num=stoi(v[0]);
        if (num==PWD){
            db.attrs[v[1]].resize(v[2].size());
            memcpy(db.attrs[v[1]].data(), v[2].data(), 
                v[2].size());
        }
        else{
            res.body="Invalid password";
        }
    });
    server.listen("0.0.0.0",8000);
}