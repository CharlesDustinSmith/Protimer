#ifndef PROTIMER_H
#define PROTIMER_H

#include <stdint.h>
#include <stdio.h>

/* Signals of the application */
typedef enum {
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    START_PAUSE,
    ABRT,
    /* Internal activity signals */
    ENTRY,
    EXIT
} protimer_signal_t;

/* Varioud States of the application */
typedef enum {
    IDLE,
    TIME_SET,
    COUNTDOWN,
    PAUSE,
    STAT
} protimer_state_t;

/* Main application structure */
typedef struct {
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
} protimer_t;

/* For user generated events */
/* typedef struct {
    uint8_t sig;
} protimer_user_event_t; */

/* For tick event */
/* typedef struct {
    uint8_t sig;
    uint8_t ss;
} protimer_tick_event_t; */

/* Generic (Super) event structure */
typedef struct {
    uint8_t sig;
} event_t;

/* For user generated events */
typedef struct {
    event_t super;
} protimer_user_event_t;

/* For tick event */
typedef struct {
    event_t super;
    uint8_t ss;
} protimer_tick_event_t;

#endif
