mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_LIBS += -lm

APPL_DIRS += $(mkfile_path)lib $(mkfile_path)lib/robot $(mkfile_path)lib/utils $(mkfile_path)lib/programs 

INCLUDES += -I$(mkfile_path)lib/robot -I$(mkfile_path)lib/programs -I$(mkfile_path)lib/utils

APPL_COBJS += globals.o helpers.o motor.o color_sensor.o run_parts.o run.o test.o debug.o drive.o actuator.o linefollow.o float_array.o utils.o drive_control.o scan.o shorthands.o second_day.o globals_programs.o drive_system.o second_day_test.o
