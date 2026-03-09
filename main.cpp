#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime> 
#include "fishes.h"
#include "world.h"
#include "canvas.h"
#include "sprite_utils.h"
#include "entity.h"
#include "bubble.h"

std::string chooseEntity(){
    std::string f;
    bool flag_s = true;
    std::cout << "choose from these:" << std::endl;
    std::cout << "small shark -1 | jellyfish -2 | fish -3 | small fish -4 | fishes -5 | seahorse -6 | seaweed -7 | 42" << std::endl;
    std::getline(std::cin, f);
    while (flag_s){      
        if (f=="1" || f=="2" || f=="3" || f=="4" || f=="5" || f=="6" || f=="7" || f=="42"){
            flag_s = false;
        }else{
            std::cout << "enter correct command pls" << std::endl;
            std::getline(std::cin, f);
        }
    }
    return f;
}

std::unique_ptr<Entity> createFish(std::string s, int width, int height){
    if (s=="1"){
        std::unique_ptr<fish1> entity = std::make_unique<fish1>(width, height);
        return entity;
    }else if(s=="4"){
        std::unique_ptr<fish2> entity = std::make_unique<fish2>(width, height);
        return entity;
    }else if(s=="3"){
        std::unique_ptr<fish3> entity = std::make_unique<fish3>(width, height);
        return entity;
    }else if(s=="5"){
        std::unique_ptr<fish4> entity = std::make_unique<fish4>(width, height);
        return entity;
    }else if(s=="2"){
        std::unique_ptr<fish5> entity = std::make_unique<fish5>(width, height);
        return entity;
    }else if(s=="6"){
        std::unique_ptr<fish6> entity = std::make_unique<fish6>(width, height);
        return entity;
    }else if(s=="42"){
        std::unique_ptr<fish7> entity = std::make_unique<fish7>(width, height);
        return entity;
    }else if(s=="7"){
        std::unique_ptr<weed1> entity = std::make_unique<weed1>(width, height);
        return entity;
    }else{
        std::cout << "net takoi entity, add basic entity" << std::endl;
        std::unique_ptr<fish2> entity = std::make_unique<fish2>(width, height);
        return entity;
    }
}

int main(){
    World world(140, 38);
    Canvas canvas(world.width(), world.height());
    srand(time(0));
    std::cout << "== aquarium ==" << std::endl;
    std::cout << "ticks?" << std::endl;
    int tik;
    std::cin >> tik;
    std::cin.ignore();
    std::cout << "add entity" << std::endl;
    std::string f = chooseEntity();
    auto entity = createFish(f, world.width(), world.height());
    world.addEntity(std::move(entity));
    bool flag = true;
    while (flag){
        std::cout << "\033[?25l";
        for (int i=0; i<tik; ++i){
            std::unique_ptr<Bubble> bubble = std::make_unique<Bubble>(world.width(), world.height());
            world.addEntity(std::move(bubble));
            std::cout << "\033[H"; 
            canvas.clear();
            world.update();
            world.render(canvas);
            canvas.present();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "\033[?25h";
        std::cout << "choose" << std::endl;
        std::cout << "stop | add | play" << std::endl;
        std::string command;
        std::getline(std::cin, command);
        bool enterFlag = true;
        while (enterFlag){
            if (command=="stop" || command=="add" || command=="play"){
                enterFlag=false;
            }else{
                std::cout << "try again" << std::endl;
                std::getline(std::cin, command);
            }
        }
        bool comF = true;
        while (comF){
            if (command=="stop"){ 
                flag = false;
                comF = false;
            }
            else if (command=="add"){
                std::string comm = chooseEntity();
                world.addEntity(createFish(comm, world.width(), world.height()));
                comF = false;
            }else if (command=="play"){
                std::cout << "\033[?25l";
                for (int i=0; i<100; ++i){
                    std::unique_ptr<Bubble> bubble = std::make_unique<Bubble>(world.width(), world.height());
                    world.addEntity(std::move(bubble));
                    std::cout << "\033[H"; 
                    canvas.clear();
                    world.update();
                    world.render(canvas);
                    canvas.present();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
                comF = false;
                std::cout << "\033[?25h";
            }else{
                std::cout << "try again" << std::endl;
                std::getline(std::cin, command);
            }
        }
    }
}
