#ifndef PROTIMER_H
#define PROTIMER_H

#include <LiquidCrystal.h>
#include <stdint.h>
#include <stdio.h>
#include "lcd.h"

/*  Macros for pins */
#define PIN_BTN_1 2
#define PIN_BTN_2 3
#define PIN_BTN_3 4
#define PIN_BUZZER 12

/* Macros for LCD connections */
#define LCD_RS 5
#define LCD_RW 6
#define LCD_EN 7
#define LCD_D4 8
#define LCD_D5 9
#define LCD_D6 10
#define LCD_D7 11

/* Macros for button pad */
#define BTN_PAD_VALUE_INC_TIME 4
#define BTN_PAD_VALUE_DEC_TIME 2
#define BTN_PAD_VALUE_ABRT 6
#define BTN_PAD_VALUE_SP 1

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

typedef enum {
    EVENT_HANDLED,
    EVENT_IGNORED,
    EVENT_TRANSITION
} event_status_t;

typedef enum{
    NOT_PRESSED, 
    BOUNCE, 
    PRESSED
} button_state_t;



#endif
