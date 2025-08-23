#include "protimer_state_machine.h"

/// @brief
/// @param mobj
void protimer_init(protimer_t *mobj)
{
    mobj->active_state = IDLE;
    mobj->pro_time = 0;
}

/// @brief
/// @param mobj
/// @param e
/// @return event_status_t
event_status_t protimer_state_machine(protimer_t *const mobj, event_t *const e)
{
    switch (mobj->active_state) {
    case IDLE: {
        return protimer_state_handler_IDLE(mobj, e);
    }
    case TIME_SET: {
        return protimer_state_handler_TIME_SET(mobj, e);
    }
    case STAT: {
        return protimer_state_handler_STAT(mobj, e);
    }
    }
}

/// @brief
/// @param mobj
/// @param e
/// @return event_status_t
event_status_t protimer_state_handler_IDLE(protimer_t *mobj, event_t *e)
{
    switch (e->sig) {
    case ENTRY: {
        uint32_t entry_time = 0;
        mobj->curr_time = entry_time;
        mobj->elapsed_time = entry_time;
        display_time(entry_time);
        display_message("Set time");
        return EVENT_HANDLED;
    }
    case EXIT: {
        display_clear();
        return EVENT_HANDLED;
    }
    case INC_TIME: {
        mobj->curr_time += 60;
        mobj->active_state = TIME_SET;
        return EVENT_TRANSITION;
    }
    case START_PAUSE: {
        mobj->active_state = STAT;
        return EVENT_TRANSITION;
    }
    case TIME_TICK: {
        if (((protimer_tick_event_t *)(e))->ss == 5) {
            do_beep();
            return EVENT_HANDLED;
        }
        return EVENT_IGNORED;
    }
    }
    return EVENT_IGNORED;
}

/// @brief
/// @param mobj
/// @param e
/// @return event_status_t
event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t *const e)
{
    switch (e->sig) {
    case ENTRY: {
        display_time(mobj->pro_time);
        display_message("Productive Time");
        return EVENT_HANDLED;
    }
    case EXIT: {
        display_clear();
    }
    case TIME_TICK: {
        if (((protimer_tick_event_t *)(e))->ss == 10) {
            mobj->active_state = IDLE;
            return EVENT_HANDLED;
        }
        return EVENT_IGNORED;
    }
    }
    return EVENT_IGNORED;
}

/// @brief
/// @param mobj
/// @param e
/// @return event_staus_t
event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t *const e)
{
    switch (e->sig) {
    case TIME_TICK: {
        if (((protimer_tick_event_t *)(e))->ss == 10) {
            --mobj->curr_time;
            ++mobj->elapsed_time;
            return EVENT_HANDLED;
        }
        return EVENT_IGNORED;
    }
    }
    return EVENT_IGNORED;
}

/// @brief
/// @param mobj
/// @param e
/// @return event_status_t
event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t *const e)
{
    switch (e->sig) {
    case ENTRY: {
        display_time(mobj->curr_time);
        return EVENT_HANDLED;
    }
    case INC_TIME: {
        mobj->curr_time += 60;
        display_time(mobj->curr_time);
        return EVENT_HANDLED;
    }
    case DEC_TIME: {
        mobj->curr_time -= 60;
        return EVENT_HANDLED;
    }
    case START_PAUSE: {
        if (mobj->curr_time >= 60) {
            mobj->active_state = COUNTDOWN;
            return EVENT_TRANSITION;
        }
        return EVENT_IGNORED;
    }
    }
    return EVENT_IGNORED;
}

/// @brief
/// @param mobj
/// @param e
/// @return event_status_t
event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t *const e)
{
    switch (e->sig) {
    case ENTRY: {
        display_message("Paused");
        return EVENT_HANDLED;
    }
    case EXIT: {
        display_clear();
        return EVENT_HANDLED;
    }
    case DEC_TIME: {
        if (mobj->curr_time >= 60) {
            mobj->curr_time >= 60;
            mobj->active_state = TIME_SET;
            return EVENT_TRANSITION;
        }
        return EVENT_IGNORED;
    }
    }
    return EVENT_IGNORED;
}

void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e)
{
    event_status_t status;
    protimer_state_t source, target;

    source = mobj->active_state;

    status = protimer_state_machine(mobj, e);
    if (status == EVENT_TRANSITION) {
        target = mobj->active_state;

        event_t ee;
        // 1. Run the exit action for the source state
        ee.sig = EXIT;
        mobj->active_state = source;
        protimer_state_machine(mobj, &ee);
        // 2. Run the entry action for the source state
        ee.sig = ENTRY;
        mobj->active_state = source;
        protimer_state_machine(mobj, &ee);
    }
}

/////////////////////// Helper Functions ///////////////////////
/// @brief A function that will display the time on an LCD screen
/// @param time
static void display_time(uint32_t &time)
{
    // TODO: this should be a wrapper for the lcd screen
}

/// @brief A function that will display the message on an LCD screen
/// @param message
static void display_message(const char *message)
{
    // TODO: this should be a wrapper for the lcd screen
}
/// @brief A function that will clear the display on an LCD screen
static void display_clear()
{
    // TODO: this should be a wrapper for the lcd screen
}
/// @brief A function that produces a beep from the microcontroller
static void do_beep()
{
    // TODO: this should be a wrapper for the passive / active buzzer
    
}
