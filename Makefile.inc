mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_LIBS += -lm

APPL_DIRS += $(mkfile_path)src $(mkfile_path)src/core $(mkfile_path)src/programs $(mkfile_path)src/robot 

INCLUDES += -I$(mkfile_path)LineTracer -I$(mkfile_path)src/core -I$(mkfile_path)src/programs -I$(mkfile_path)src/robot

APPL_COBJS += config.o helpers.o motor.o color_sensor.o run_parts.o run.o test.o debug.o drive.o actuator.o linefollow.o float_array.o
