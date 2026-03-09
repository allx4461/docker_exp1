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

// int main(){
//     srand(time(0));
//     World world(140, 38);
//     Canvas canvas(world.width(), world.height());
//     std::unique_ptr<fish5> entity1 = std::make_unique<fish5>(world.width(), world.height());
//     world.addEntity(std::move(entity1));
//     std::unique_ptr<fish6> entity2 = std::make_unique<fish6>(world.width(), world.height());
//     world.addEntity(std::move(entity2));
//     std::unique_ptr<fish7> entity3 = std::make_unique<fish7>(world.width(), world.height());
//     world.addEntity(std::move(entity3));
//     fish7* entity3_ptr = entity3.get();
//     srand(time(0));
//     std::unique_ptr<fish2> entity4 = std::make_unique<fish2>(world.width(), world.height());
//     world.addEntity(std::move(entity4));
//     std::unique_ptr<weed1> entity5 = std::make_unique<weed1>(world.width(), world.height());
//     world.addEntity(std::move(entity5));
//     std::cout << world.size() << std::endl;
//     std::cout << "\033[?25l";
//     for (int i=0; i<20; ++i){
//         std::unique_ptr<Bubble> bubble = std::make_unique<Bubble>(world.width(), world.height());
//         world.addEntity(std::move(bubble));
//         std::cout << "\033[H"; 
//         canvas.clear();
//         world.update();
//         world.render(canvas);
//         canvas.present();
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     world.removeEntity(entity3_ptr);
//     std::cout << "REMOOOOOOOOOOVE" << std::endl;
//     for (int i=0; i<20; ++i){
//         std::unique_ptr<Bubble> bubble = std::make_unique<Bubble>(world.width(), world.height());
//         world.addEntity(std::move(bubble));
//         std::cout << "\033[H"; 
//         canvas.clear();
//         world.update();
//         world.render(canvas);
//         canvas.present();
//         std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     }
//     std::cout << "\033[?25h";
//     return 0;
// }

std::string chooseEntity(){
    std::string f;
    bool flag_s = true;
    std::cout << "You may choose one of this:" << std::endl;
    std::cout << "MiniShark | JellyFish | mediumFish | MiniFish | ManyFish | Seahorse | Weed | 42" << std::endl;
    std::getline(std::cin, f);
    while (flag_s){      
        if (f=="MiniShark" || f=="JellyFish" || f=="mediumFish" || f=="MiniFish" || f=="ManyFish" || f=="Seahorse" || f=="Weed" || f=="42"){
            flag_s = false;
        }else{
            std::cout << "enter correct command pls" << std::endl;
            std::getline(std::cin, f);
        }
    }
    return f;
}

std::unique_ptr<Entity> createFish(std::string s, int width, int height){
    if (s=="MiniShark"){
        std::unique_ptr<fish1> entity = std::make_unique<fish1>(width, height);
        return entity;
    }else if(s=="MiniFish"){
        std::unique_ptr<fish2> entity = std::make_unique<fish2>(width, height);
        return entity;
    }else if(s=="mediumFish"){
        std::unique_ptr<fish3> entity = std::make_unique<fish3>(width, height);
        return entity;
    }else if(s=="ManyFish"){
        std::unique_ptr<fish4> entity = std::make_unique<fish4>(width, height);
        return entity;
    }else if(s=="JellyFish"){
        std::unique_ptr<fish5> entity = std::make_unique<fish5>(width, height);
        return entity;
    }else if(s=="Seahorse"){
        std::unique_ptr<fish6> entity = std::make_unique<fish6>(width, height);
        return entity;
    }else if(s=="42"){
        std::unique_ptr<fish7> entity = std::make_unique<fish7>(width, height);
        return entity;
    }else if(s=="Weed"){
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
    std::cout << "Welkome to bulbul aquarium ^^" << std::endl;
    std::cout << "How much ticks do you want?" << std::endl;
    int tik;
    std::cin >> tik;
    std::cin.ignore();
    std::cout << "Let's add your first entity to aquarium!" << std::endl;
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
        std::cout << "What do you wanto to do?(choose)" << std::endl;
        std::cout << "stop | addEntity | playWorld" << std::endl;
        std::string command;
        std::getline(std::cin, command);
        bool enterFlag = true;
        while (enterFlag){
            if (command=="stop" || command=="addEntity" || command=="playWorld"){
                enterFlag=false;
            }else{
                std::cout << "wtf normal command please :3" << std::endl;
                std::getline(std::cin, command);
            }
        }
        bool comF = true;
        while (comF){
            if (command=="stop"){ 
                flag = false;
                comF = false;
            }
            else if (command=="addEntity"){
                std::string comm = chooseEntity();
                world.addEntity(createFish(comm, world.width(), world.height()));
                comF = false;
            }else if (command=="playWorld"){
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
                std::cout << "wtf normal command please :3" << std::endl;
                std::getline(std::cin, command);
            }
        }
    }
}
