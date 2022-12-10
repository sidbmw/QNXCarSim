#
#	Makefile for QNXCarSim
#

DEBUG = -g
CC = qcc
LD = qcc


TARGET = -Vgcc_ntox86_64
#TARGET = -Vgcc_ntox86
#TARGET = -Vgcc_ntoarmv7le
#TARGET = -Vgcc_ntoaarch64le


CFLAGS += $(DEBUG) $(TARGET) -Wall
LDFLAGS+= $(DEBUG) $(TARGET)
BINS = engine airbags throttle indicator brakes steering
all: clean $(BINS)

clean:
	rm -f *.o $(BINS);

