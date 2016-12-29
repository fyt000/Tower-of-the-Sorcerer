#pragma once
#include "MyAction.h"
#include "Condition.h"
#include <vector>

class GlobalEvent{
    public:
        //GlobalEvent(); 
        bool tryTrigger();
        void attachAction(MyAction*);
        void addCondition(Condition*);
        ~GlobalEvent();
    private:
    std::vector<Condition*> conditions;
    std::vector<MyAction*> actions;
};