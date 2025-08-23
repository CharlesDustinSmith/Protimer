#ifndef PROTIMER_STATE_MACHINE_H
#define PROTIMER_STATE_MACHINE_H

#include "protimer.h"

void protimer_init(protimer_t *mobj);

event_status_t protimer_state_machine(protimer_t *mobj, event_t *e);

event_status_t protimer_state_handler_IDLE(protimer_t *mobj, event_t *e);

event_status_t protimer_state_handler_STAT(protimer_t *const mobj, event_t *const e);

event_status_t protimer_state_handler_COUNTDOWN(protimer_t *const mobj, event_t *const e);

event_status_t protimer_state_handler_TIME_SET(protimer_t *const mobj, event_t *const e);

event_status_t protimer_state_handler_PAUSE(protimer_t *const mobj, event_t *const e);

void protimer_event_dispatcher(protimer_t *const mobj, event_t *const e);

/// Helper functiion decalaration
static void display_time(uint32_t &time);

static void display_message(const char *message);

static void display_clear();

static void do_beep();

#endif