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

inline transition_condition_ftor_t default_condition = []() { return true; };

template <typename StateType>
struct StateTransitionTemplate_s
{   
    StateType From;
    StateType To;
    transition_condition_ftor_t Condition = default_condition;
    transition_action_ftor_t DoOnce = no_onetime_action;
    transition_action_ftor_t DoRepeatedly = no_repeated_action;

    enum class TransitionResult_e
    {
        TRANSITION_PERFORMED,
        NO_TRANSITION_PERFORMED
    };

    TransitionResult_e performTransitionIfPossible(StateType& state)
    {
        if ((Condition)())
        {
            if (DoOnce)
            {
                (DoOnce)();
            }
            
            state = To;
            return TransitionResult_e::TRANSITION_PERFORMED;
        }
        else
        {
            if (DoRepeatedly)
            {
                (DoRepeatedly)();
            }

            state = From;
            return TransitionResult_e::NO_TRANSITION_PERFORMED;
        }
    }
};

template <typename StateType> //, StateType InitialState>
class StateMachine_i
{
public:
    using StateTransition_s = StateTransitionTemplate_s<StateType>;

private:
    StateType State;
    std::vector<StateTransition_s> Transitions;

public:
    StateType state() const
    {
        return State;
    }

    void addTransition(StateTransition_s&& transition)
    {
        Transitions.push_back(transition);
    }

    void performTransition()
    {
        for (StateTransition_s& t : Transitions)
        {
            if (State == t.From)
            {
                auto res = t.performTransitionIfPossible(State);
                if (res == StateTransition_s::TransitionResult_e::TRANSITION_PERFORMED)
                {
                    break;
                }
            }
        }
    }

    explicit StateMachine_i(StateType initialState) :
        State(initialState)
    {}
};

} // namespace statemachine