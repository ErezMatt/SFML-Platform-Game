#include "StateMachine.hpp"

StateMachine::StateMachine()
{
}

void StateMachine::addState(std::unique_ptr<State> newState, bool replacing)
{
    _status = ADDING;
    _replacing = replacing;
    _state=std::move(newState);
}

void StateMachine::eraseState()
{
    _status = REMOVING;
}

void StateMachine::update()
{
    if(_status == REMOVING && !_states.empty()){
        _states.pop();

        if(!_states.empty()){
            _states.top()->resume();
        }
        _status = NONE;
    }

    if(_status == ADDING){
        if(!_states.empty()){
            if(_replacing){
                _states.pop();
            }
            else{
                _states.top()->pause();
            }
        }
        _states.push(std::move(_state));
        _states.top()->init();
        _status = NONE;
    }
}

std::unique_ptr<State> &StateMachine::getState()
{
    return _states.top();
}

StateMachine::~StateMachine()
{
}
