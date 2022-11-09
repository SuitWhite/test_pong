#include "singleton.h"

Singleton::Singleton(){
}

Singleton* Singleton::getInstance(){
    if (instance==nullptr){
        instance = new Singleton();
    }
    return instance;
}