#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

class StateMachine
{
    private:
        enum {NONE, ADDING, REMOVING} _status;

    public:
        StateMachine();
        virtual ~StateMachine();

        void addState(std::unique_ptr<State> newState, bool replacing=true);
        void eraseState();
        void update();

        std::unique_ptr<State> &getState();

    private:
        std::stack<std::unique_ptr<State>> _states;
        std::unique_ptr<State> _state;
        bool _replacing;
};
