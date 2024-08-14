#include "../include/Menu.hpp"



using namespace std;

Menu::Menu(){ 
    active();
}

int Menu::active(){

    return 0;
}

void Menu::checkInput(){
    if(_kbhit()){
        char ch = _getch();
        switch(ch){
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            default:
                break;
        }
    }
}