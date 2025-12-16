#include "touch_port.h"

int16_t g_tp_x;
int16_t g_tp_y;
uint8_t g_tp_is_pressed;

void touch_port_input(touch_event_t event, int16_t x, int16_t y)
{
    if( event==TOUCH_EVENT_UP ) {
        g_tp_x = x;
        g_tp_y = y;
        g_tp_is_pressed = 0;
    }
    else if( event==TOUCH_EVENT_DOWN ) {
        g_tp_x = x;
        g_tp_y = y;
        g_tp_is_pressed = 1;
    }
    else if( event==TOUCH_EVENT_MOVE ) {
        g_tp_x = x;
        g_tp_y = y;
        g_tp_is_pressed = 1;
    }
}

uint8_t tp_get_is_pressed(void)
{
    return g_tp_is_pressed;
}

int16_t tp_get_x(void)
{
    return g_tp_x;
}

int16_t tp_get_y(void)
{
    return g_tp_y;
}
