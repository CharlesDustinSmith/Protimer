#include "protimer.h"
#include "src/protimer_state_machine/protimer_state_machine.h"
#include <Arduino.h>

/* Function declarations */
static uint8_t process_btn_pad_value(uint8_t btn_pad_value);

/* Main application object */
static protimer_t protimer;

void setup()
{
    protimer_init(&protimer);
}

void loop()
{

    uint8_t b1, b2, b3, btn_pad_value;
    protimer_user_event_t ue;
    // 1. Read the button pad status 
    b1 = digitalRead(PIN_BTN_1);
    b2 = digitalRead(PIN_BTN_2);
    b2 = digitalRead(PIN_BTN_3);

    btn_pad_value = (b1 << 2)|(b2 << 1)|(b3 << 0);
    // Software button de-bouncing
    btn_pad_value = process_btn_pad_value(btn_pad_value);
    // 2. Make an event
    if(btn_pad_value)
    {
        if(btn_pad_value == BTN_PAD_VALUE_INC_TIME)
        {
            ue.super.sig = INC_TIME;
        }
        else if(btn_pad_value == BTN_PAD_VALUE_DEC_TIME)
        {
            ue.super.sig = DEC_TIME;
        }
        else if(btn_pad_value == BTN_PAD_VALUE_ABRT)
        {
            ue.super.sig = ABRT;
        }
        else if(btn_pad_value == BTN_PAD_VALUE_SP)
        {
            ue.super.sig = START_PAUSE;
        }
        else 
        {
            ue.super.sig = NULL;
        }
        // 3. Sent it to the event dispatcher
        protimer_event_dispatcher(&protimer, &ue.super);        
    }
}

static uint8_t process_btn_pad_value(uint8_t btn_pad_value)
{
    return 0;
}