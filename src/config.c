#include "../include/config.h"

Motor a = { EV3_PORT_A, LARGE_MOTOR, A_COUNTERCLOCKWISE };
Motor b = { EV3_PORT_B, MEDIUM_MOTOR, B_COUNTERCLOCKWISE };
Motor c = { EV3_PORT_C, MEDIUM_MOTOR, C_COUNTERCLOCKWISE };
Motor d = { EV3_PORT_D, LARGE_MOTOR, D_COUNTERCLOCKWISE };

ColorSensor s1 = { EV3_PORT_1 };
ColorSensor s2 = { EV3_PORT_2 };
ColorSensor s3 = { EV3_PORT_3 };
ColorSensor s4 = { EV3_PORT_4 };

Actuator lifter = { .motor = { EV3_PORT_D, LARGE_MOTOR, D_COUNTERCLOCKWISE }, .max_neg_speed = 40, .max_pos_speed = 60 };
Actuator dropper = { .motor = { EV3_PORT_A, LARGE_MOTOR, A_COUNTERCLOCKWISE }, .max_neg_speed = 40, .max_pos_speed = 20 };

int current_speed = 0;
int smooth_deg_acc_end = 0;
int smooth_deg_deacc_start = 0;
int smooth_current_max_speed = 0;
int smooth_start_speed = 0;
float smooth_current_acc_factor = 0.0;
float smooth_current_deacc_factor = 0.0;

int scan_count;
float sum_rolled_average;
float needs_to_be_subtracted;
float sum_rolled_average;
float last_value;
float second_last_value;
float_array temp_scanned_values;
float_array maxima_ids;

// pos1, pos2, pos3, pos4, pos5, pos6, finish,, surprise_rule drive back
int pos_ship_values[POS_COUNT + 2] = { 135, 235, 460, 570, 680, 780, 280, 370 };

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

    // reset scan variables
    reset_scan();
}