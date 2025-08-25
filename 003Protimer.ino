#include "protimer.h"
#include "protimer_state_machine.h"
#include <Arduino.h>

/* Function declarations */
static uint8_t process_btn_pad_value(uint8_t btn_pad_value);
static void display_init(void);

/* Main application object */
static protimer_t protimer;

void setup()
{
    /* Put your setup code here, to run once: */
    Serial.begin(115200);
    display_init();
    Serial.println("Productive timer applicarion");
    Serial.println("============================");
    pinMode(PIN_BTN_1, INPUT);
    pinMode(PIN_BTN_2, INPUT);
    pinMode(PIN_BTN_3, INPUT);

    protimer_init(&protimer);
}

void loop()
{

    uint8_t b1, b2, b3, btn_pad_value;
    protimer_user_event_t ue;
    static uint32_t current_time = millis();
    static protimer_tick_event_t te;

    // 1. Read the button pad status
    b1 = digitalRead(PIN_BTN_1);
    b2 = digitalRead(PIN_BTN_2);
    b2 = digitalRead(PIN_BTN_3);

    btn_pad_value = (b1 << 2) | (b2 << 1) | (b3 << 0);
    // Software button de-bouncing
    btn_pad_value = process_btn_pad_value(btn_pad_value);
    // 2. Make an event
    if (btn_pad_value) {
        if (btn_pad_value == BTN_PAD_VALUE_INC_TIME) {
            ue.super.sig = INC_TIME;
        } else if (btn_pad_value == BTN_PAD_VALUE_DEC_TIME) {
            ue.super.sig = DEC_TIME;
        } else if (btn_pad_value == BTN_PAD_VALUE_ABRT) {
            ue.super.sig = ABRT;
        } else if (btn_pad_value == BTN_PAD_VALUE_SP) {
            ue.super.sig = START_PAUSE;
        } else {
            ue.super.sig = NULL;
        }
        // 3. Sent it to the event dispatcher
        protimer_event_dispatcher(&protimer, &ue.super);
    }
    // 4. Dispatch the time tick event for event 100ms
    if (millis() - current_time >= 100) {
        // 100ms has passed
        current_time = millis();
        te.super.sig = TIME_TICK;
        ++te.ss;
        if (++te.ss > 10){
            te.ss = 1;
        }           
        protimer_event_dispatcher(&protimer, &te.super);
    }
}

static uint8_t process_btn_pad_value(uint8_t btn_pad_value)
{
    static uint8_t btn_sm_state = NOT_PRESSED;
    static uint8_t curr_time = millis();
    
    switch(btn_sm_state)
    {
        case NOT_PRESSED:
        {
            if(btn_pad_value)
            {
                btn_sm_state = BOUNCE;
                curr_time = millis();
            }
            break;
        }
        case BOUNCE:
        {
            if(millis() - curr_time >= 50 )
            {
                // 50ms has passed 
                if(btn_pad_value)
                {
                    btn_sm_state = PRESSED;
                    return btn_pad_value;
                }
                else
                {
                    btn_sm_state = NOT_PRESSED;
                }
            }
        }
        case PRESSED:
        {
            if(!btn_pad_value)
            {
                btn_sm_state = BOUNCE;
                curr_time = millis();
            }
        }

    }
    return 0;
}

static void display_init(void)
{
    lcd_begin(16, 2);
    lcd_clear();
    lcd_move_cursor_L_to_R();
    lcd_set_cursor(0, 0);
    lcd_no_auto_scroll();
    lcd_cursor_off();
}