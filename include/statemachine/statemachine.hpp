#pragma once

#include <functional>
#include <unordered_map>


namespace statemachine
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Minimalistic finite state machine API

/// First, we define strong tag types to make distinction
/// Between repeated and onetime actions, to make harder
/// for the API users to mix them and also the caller side
/// code will be more expressive
struct TransitionConditionTag {};
struct RepeatedActionTag {};
struct OnetimeActionTag {};

/// Then define the function type aliases
using transition_condition_ftor_t = std::function<bool(TransitionConditionTag&&)>;
using repeated_action_ftor_t = std::function<void(RepeatedActionTag&&)>;
using onetime_action_ftor_t = std::function<void(OnetimeActionTag&&)>;

/// Then we define the placeholders which shall be used
/// when a state transition doesn't needs any of these,
/// eg. if we want to have an unconditional transition from a state
/// to another, we can just use statmachine::default_condition instead
inline transition_condition_ftor_t default_condition = [](TransitionConditionTag) { return true; };
inline repeated_action_ftor_t empty_repeated_action = [](RepeatedActionTag) {};
inline onetime_action_ftor_t empty_onetime_action = [](OnetimeActionTag) {};

/// Helper enum class to inform StateMachine_c and the outside world if a transition happened or not 
enum class TransitionResult_e
{
    TRANSITION_PERFORMED,
    NO_TRANSITION_PERFORMED
};

/////////////////////////////////////////////////////////////////////////////////////////
/// Struct representing a transition between states 'From' to 'To'.
/// The transition takes place under the condition described in the Condition functor
///
/// The interface also provides support for in-state and on-transition actions:
/// DoRepeatedly is called at every transition check, when the transition does not happens
/// Contrary to, DoOnce which is called once during the state transition
///
/// It has a template parameter (StateType) which is the type (preferably an enumeration),
/// which is used to track the states on the API user side



template <typename StateType>
struct StateTransitionTemplate_s
{   
    StateType From;
    StateType To;

    repeated_action_ftor_t DoRepeatedly = empty_repeated_action;
    transition_condition_ftor_t Condition = default_condition;
    onetime_action_ftor_t DoOnce = empty_onetime_action;

    TransitionResult_e performTransitionIfPossible(StateType& state)
    {
        if ((Condition)(TransitionConditionTag()))
        {
            (DoOnce)(OnetimeActionTag());
            state = To;
            return TransitionResult_e::TRANSITION_PERFORMED;
        }
        else
        {
            (DoRepeatedly)(RepeatedActionTag());
            state = From;
            return TransitionResult_e::NO_TRANSITION_PERFORMED;
        }
    }
};


/////////////////////////////////////////////////////////////////////////////////////////
/// The main state machine class, which maintains a list of transitions
/// and stores the actual state of type StateType. 
///
/// It has a template parameter (StateType) which is the type (preferably an enumeration),
/// which is used to track the states on the API user side

template <typename StateType> //, StateType InitialState>
class StateMachine_c
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

    TransitionResult_e performTransition()
    {
        for (StateTransition_s& t : Transitions)
        {
            if (State == t.From)
            {
                TransitionResult_e res = t.performTransitionIfPossible(State);

                // If the transition was successful we shall return,
                // and avoid further checks for optimalization and more
                // importantly, to avoid unwanted skipping of states
                if (res == TransitionResult_e::TRANSITION_PERFORMED)
                {
                    return res;
                }
            }
        }

        return TransitionResult_e::NO_TRANSITION_PERFORMED;
    }

    explicit StateMachine_c(StateType initialState) :
        State(initialState)
    {}
};

} // namespace statemachine