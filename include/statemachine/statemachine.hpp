#pragma once

#include <functional>
#include <unordered_map>


namespace statemachine
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Minimalistic finite state machine API

/// Expressive placeholders to indicate empty functors in code
constexpr nullptr_t no_action = nullptr;
constexpr decltype(no_action) no_onetime_action = no_action;
constexpr decltype(no_action) no_repeated_action = no_action;

using transition_condition_ftor_t = std::function<bool(void)>;
using transition_action_ftor_t = std::function<void(void)>;

transition_condition_ftor_t default_condition = []() { return true; };

template <typename StateType>
struct StateTransitionTemplate_s
{
    
    StateType From;
    StateType To;
    transition_condition_ftor_t Condition = default_condition;
    transition_action_ftor_t DoOnce = no_onetime_action;
    transition_action_ftor_t DoRepeatedly = no_repeated_action;

    StateType performTransitionIfPossible()
    {
        if ((Condition)())
        {
            if (DoOnce)
            {
                (DoOnce)();
            }
            return To;
        }
        else
        {
            if (DoRepeatedly)
            {
                (DoRepeatedly)();
            }
            return From;
        }
    }
};

template <typename StateType, StateType InitialState>
class StateMachine_i
{
public:
    using StateTransition_s = StateTransitionTemplate_s<StateType>;

private:
    StateType State;
    std::vector<StateTransition_s> Transitions

public:
    StateType state() const
    {
        return State;
    }

    void addTransition(StateTransition_s& transition)
    {
        Transitions.push_back(transition);
    }

    void performTransition()
    {
        for (const StateTransition_s& t : Transitions)
        {
            if (State == t.From)
            {
                State = performTransitionIfPossible();
            }
        }
    }

    constexpr StateMachine_i() :
        State(InitialState)
    {}
};

} // namespace statemachine