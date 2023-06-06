#include "lib/robot/globals.h"

Motor a = { .port = EV3_PORT_A, .is_large_motor = A_LARGE_MOTOR, .counterclockwise = A_COUNTERCLOCKWISE, .stall_detection = { .is_currently_stalled = false, .stall_detection_timeout = A_STALL_DETECTION_TIMEOUT } };
Motor b = { .port = EV3_PORT_B, .is_large_motor = B_LARGE_MOTOR, .counterclockwise = B_COUNTERCLOCKWISE, .stall_detection = { .is_currently_stalled = false, .stall_detection_timeout = B_STALL_DETECTION_TIMEOUT } };
Motor c = { .port = EV3_PORT_C, .is_large_motor = C_LARGE_MOTOR, .counterclockwise = C_COUNTERCLOCKWISE, .stall_detection = { .is_currently_stalled = false, .stall_detection_timeout = C_STALL_DETECTION_TIMEOUT } };
Motor d = { .port = EV3_PORT_D, .is_large_motor = D_LARGE_MOTOR, .counterclockwise = D_COUNTERCLOCKWISE, .stall_detection = { .is_currently_stalled = false, .stall_detection_timeout = D_STALL_DETECTION_TIMEOUT } };

ColorSensor s1 = { .port = EV3_PORT_1 };
ColorSensor s2 = { .port = EV3_PORT_2 };
ColorSensor s3 = { .port = EV3_PORT_3 };
ColorSensor s4 = { .port = EV3_PORT_4 };

Actuator lifter = { .motor = &d, .max_neg_speed = LIFTER_MAX_NEG_SPEED, .max_pos_speed = LIFTER_MAX_POS_SPEED };
Actuator dropper = { .motor = &a, .max_neg_speed = DROPPER_MAX_NEG_SPEED, .max_pos_speed = DROPPER_MAX_POS_SPEED };

void init_robot()
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
    col_get_ref(s1);
    col_get_ref(s2);
    col_get_ref(s3);
    col_get_ref(s4);
    col_get_rgb(s4);

    // reset scan variables
    init_complex_scan();
}
