#include "../include/config.h"

Motor a = { EV3_PORT_A, LARGE_MOTOR, A_COUNTERCLOCKWISE };
Motor b = { EV3_PORT_B, MEDIUM_MOTOR, B_COUNTERCLOCKWISE };
Motor c = { EV3_PORT_C, MEDIUM_MOTOR, C_COUNTERCLOCKWISE };
Motor d = { EV3_PORT_D, LARGE_MOTOR, D_COUNTERCLOCKWISE };

ColorSensor s1 = { EV3_PORT_1 };
ColorSensor s2 = { EV3_PORT_2 };
ColorSensor s3 = { EV3_PORT_3 };
ColorSensor s4 = { EV3_PORT_4 };

void init()
{
    m_init(a);
    m_init(b);
    m_init(c);
    m_init(d);
    col_init(s1);
    col_init(s2);
    col_init(s3);
    col_init(s4);

    ev3_lcd_set_font(EV3_FONT_MEDIUM);

    m_reset(a);
    m_reset(b);
    m_reset(c);
    m_reset(d);

    // waits until all sensors are running
    ev3_color_sensor_get_reflect(EV3_PORT_1);
    ev3_color_sensor_get_reflect(EV3_PORT_2);
    ev3_color_sensor_get_reflect(EV3_PORT_3);
    ev3_color_sensor_get_reflect(EV3_PORT_4);
    m_get_deg(a);
    m_get_deg(b);
    m_get_deg(c);
    m_get_deg(d);
}