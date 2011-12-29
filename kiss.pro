include(config.pri)

TEMPLATE = lib
TARGET = 
DEPENDPATH += src

LIBPATH += /Volumes/Eve/lib
INCLUDEPATH += /Volumes/Eve/include

CONFIG -= qt debug debug_and_release
CONFIG += staticlib release

# Input
HEADERS += 	graphics_interface.h \
			kiss.h \
			kiss_graphics.h \
			kiss_graphics_draw.h \
			kiss_ops.h \
			thread_interface.h \
			timing_interface.h \
			kiss_serial.h \
			kiss_serial_buffer.h \
			serial_interface.h \
			kiss_util.h \
			kiss_input.h

SOURCES += 	graphics_interface.c \
			kiss.c \
			kiss_graphics.c \
			kiss_graphics_draw.c \
			thread_interface.c \
			timing_interface.c \
			kiss_serial_buffer.c \
			serial_interface.c \
			kiss_util.c \
			kiss_input.c

unix: SOURCES += kiss_serial_unix.c
windows: SOURCES += kiss_serial_windows.c

QMAKE_CLEAN += src/*~ libkiss.a

