# Get git commit version and date
#GIT_VERSION := $(shell git --no-pager describe --tags --always --dirty)
GIT_DATE := $(firstword $(shell git --no-pager show --date=short --format="%ai" --name-only))
GIT_VERSION := $(shell git describe --abbrev=0 --tags)

# uncomment the line below to include GPIO
#GPIO_INCLUDE=GPIO

# uncomment the line below to include MCP23017 I2C
#I2C_INCLUDE=I2C

# uncomment the line below to include USB Ozy support
#USBOZY_INCLUDE=USBOZY

# uncomment the line below to include support for psk31
#PSK_INCLUDE=PSK

# uncomment the line to below include support for FreeDV codec2
#FREEDV_INCLUDE=FREEDV

# uncomment the line below to include Pure Signal support
#PURESIGNAL_INCLUDE=PURESIGNAL

# uncomment the line to below include support for sx1509 i2c expander
#SX1509_INCLUDE=sx1509

# uncomment the line to below include support local CW keyer
#LOCALCW_INCLUDE=LOCALCW

# uncomment the line below to include support for STEMlab discovery (WITH AVAHI)
#STEMLAB_DISCOVERY=STEMLAB_DISCOVERY

# uncomment the line below to include support for STEMlab discovery (WITHOUT AVAHI)
#STEMLAB_DISCOVERY=STEMLAB_DISCOVERY_NOAVAHI

# uncommment this line for circumventing problems with RedPitya HPSDR apps.
#STEMLAB_FIX_OPTION=-DSTEMLAB_FIX

# uncomment the line below to include support for Pi SDR
#PI_SDR_INCLUDE=PI_SDR

#uncomment the line below for the platform being compiled on (actually not used)
UNAME_N=raspberrypi
#UNAME_N=odroid
#UNAME_N=up
#UNAME_N=pine64
#UNAME_N=jetsen

CC=gcc
LINK=gcc

# uncomment the line below for various debug facilities
#DEBUG_OPTION=-D DEBUG

ifeq ($(PURESIGNAL_INCLUDE),PURESIGNAL)
    PURESIGNAL_OPTIONS=-D PURESIGNAL
    PURESIGNAL_SOURCES= \
    ps_menu.c
    PURESIGNAL_HEADERS= \
    ps_menu.h
    PURESIGNAL_OBJS= \
    ps_menu.o
endif

ifeq ($(REMOTE_INCLUDE),REMOTE)
    REMOTE_OPTIONS=-D REMOTE
    REMOTE_SOURCES= \
    remote_radio.c \
    remote_receiver.c
    REMOTE_HEADERS= \
    remote_radio.h \
    remote_receiver.h
    REMOTE_OBJS= \
    remote_radio.o \
    remote_receiver.o
endif

ifeq ($(USBOZY_INCLUDE),USBOZY)
    USBOZY_OPTIONS=-D USBOZY
    USBOZY_LIBS=-lusb-1.0
    USBOZY_SOURCES= \
    ozyio.c
    USBOZY_HEADERS= \
    ozyio.h
    USBOZY_OBJS= \
    ozyio.o
endif

# uncomment the line below for LimeSDR (uncomment line below)
#LIMESDR_INCLUDE=LIMESDR

# uncomment the line below when Radioberry radio cape is plugged in (for now use emulator and old protocol)
#RADIOBERRY_INCLUDE=RADIOBERRY
ifeq ($(RADIOBERRY_INCLUDE),RADIOBERRY)
    RADIOBERRY_OPTIONS=-D RADIOBERRY
endif

ifeq ($(LIMESDR_INCLUDE),LIMESDR)
    LIMESDR_OPTIONS=-D LIMESDR
    SOAPYSDRLIBS=-lSoapySDR
    LIMESDR_SOURCES= \
    lime_discovery.c \
    lime_protocol.c
    LIMESDR_HEADERS= \
    lime_discovery.h \
    lime_protocol.h
    LIMESDR_OBJS= \
    lime_discovery.o \
    lime_protocol.o
endif


ifeq ($(PSK_INCLUDE),PSK)
    PSK_OPTIONS=-D PSK
    PSKLIBS=-lpsk
    PSK_SOURCES= \
    psk.c \
    psk_waterfall.c
    PSK_HEADERS= \
    psk.h \
    psk_waterfall.h
    PSK_OBJS= \
    psk.o \
    psk_waterfall.o
endif


ifeq ($(FREEDV_INCLUDE),FREEDV)
    FREEDV_OPTIONS=-D FREEDV
    FREEDVLIBS=-lcodec2
    FREEDV_SOURCES= \
    freedv.c \
    freedv_menu.c
    FREEDV_HEADERS= \
    freedv.h \
    freedv_menu.h
    FREEDV_OBJS= \
    freedv.o \
    freedv_menu.o
endif

ifeq ($(LOCALCW_INCLUDE),LOCALCW)
    LOCALCW_OPTIONS=-D LOCALCW
    LOCALCW_SOURCES= iambic.c
    LOCALCW_HEADERS= iambic.h
    LOCALCW_OBJS= iambic.o
endif

ifeq ($(GPIO_INCLUDE),GPIO)
    GPIO_OPTIONS=-D GPIO
    GPIO_LIBS=-lwiringPi
    GPIO_SOURCES= \
    gpio.c \
    encoder_menu.c
    GPIO_HEADERS= \
    gpio.h \
    encoder_menu.h
    GPIO_OBJS= \
    gpio.o \
    encoder_menu.o
endif

ifeq ($(I2C_INCLUDE),I2C)
    I2C_OPTIONS=-D I2C
    I2C_SOURCES=i2c.c
    I2C_HEADERS=i2c.h
    I2C_OBJS=i2c.o
endif

#
# We have two versions of STEMLAB_DISCOVERY here,
# the second one has to be used
# if you do not have the avahi (devel-) libraries
# on your system.
#
ifeq ($(STEMLAB_DISCOVERY), STEMLAB_DISCOVERY)
    STEMLAB_OPTIONS=-D STEMLAB_DISCOVERY \
    `pkg-config --cflags avahi-gobject` \
    `pkg-config --cflags libcurl`
    STEMLAB_LIBS=`pkg-config --libs avahi-gobject` `pkg-config --libs libcurl`
    STEMLAB_SOURCES=stemlab_discovery.c
    STEMLAB_HEADERS=stemlab_discovery.h
    STEMLAB_OBJS=stemlab_discovery.o
endif

ifeq ($(STEMLAB_DISCOVERY), STEMLAB_DISCOVERY_NOAVAHI)
    STEMLAB_OPTIONS=-D STEMLAB_DISCOVERY -D NO_AVAHI `pkg-config --cflags libcurl`
    STEMLAB_LIBS=`pkg-config --libs libcurl`
    STEMLAB_SOURCES=stemlab_discovery.c
    STEMLAB_HEADERS=stemlab_discovery.h
    STEMLAB_OBJS=stemlab_discovery.o
endif

ifeq ($(PI_SDR_INCLUDE),PI_SDR)
    PI_SDR_OPTIONS=-D PI_SDR
endif

GTKINCLUDES=`pkg-config --cflags gtk+-3.0`
GTKLIBS=`pkg-config --libs gtk+-3.0`

AUDIO_LIBS=-lasound
#AUDIO_LIBS=-lsoundio

OPTIONS=-g -Wno-deprecated-declarations $(PURESIGNAL_OPTIONS) $(REMOTE_OPTIONS) $(USBOZY_OPTIONS) $(I2C_OPTIONS) $(GPIO_OPTIONS) $(LIMESDR_OPTIONS) \
    $(FREEDV_OPTIONS) $(LOCALCW_OPTIONS) $(RADIOBERRY_OPTIONS) $(PI_SDR_OPTIONS) $(PSK_OPTIONS) $(STEMLAB_OPTIONS) $(STEMLAB_FIX_OPTION) \
    -D GIT_DATE='"$(GIT_DATE)"' -D GIT_VERSION='"$(GIT_VERSION)"' $(DEBUG_OPTION) -O3

LIBS=-lrt -lm -lwdsp -lpthread $(AUDIO_LIBS) $(USBOZY_LIBS) $(PSKLIBS) $(GTKLIBS) $(GPIO_LIBS) $(SOAPYSDRLIBS) $(FREEDVLIBS) $(STEMLAB_LIBS)
INCLUDES=$(GTKINCLUDES)

COMPILE=$(CC) $(OPTIONS) $(INCLUDES)

.c.o:
	$(COMPILE) -c -o $@ $<

PROGRAM=pihpsdr

SOURCES= \
about_menu.c \
agc_menu.c \
ant_menu.c \
audio_waterfall.c \
audio.c \
band_menu.c \
band.c \
bandstack_menu.c \
button_text.c \
configure.c \
cw_menu.c \
cwramp.c \
discovered.c \
discovery.c \
display_menu.c \
diversity_menu.c \
dsp_menu.c \
equalizer_menu.c \
error_handler.c \
exit_menu.c \
ext.c \
fft_menu.c \
filter_menu.c \
filter.c \
freqent_menu.c \
frequency.c \
led.c \
main.c \
memory.c \
meter_menu.c \
meter.c \
mode_menu.c \
mode.c \
new_discovery.c \
new_menu.c \
new_protocol_programmer.c \
new_protocol.c \
noise_menu.c \
oc_menu.c \
old_discovery.c \
old_protocol.c \
pa_menu.c \
property.c \
radio_menu.c \
radio.c \
receiver.c \
rigctl_menu.c \
rigctl.c \
rx_menu.c \
rx_panadapter.c \
sliders.c \
step_menu.c \
store_menu.c \
store.c \
test_menu.c \
toolbar.c \
transmitter.c \
tx_menu.c \
tx_panadapter.c \
update.c \
version.c \
vfo_menu.c \
vfo.c \
vox_menu.c \
vox.c \
waterfall.c \
xvtr_menu.c \


HEADERS= \
about_menu.h \
agc_menu.h \
agc.h \
alex.h \
ant_menu.h \
audio_waterfall.h \
audio.h \
band_menu.h \
band.h \
bandstack_menu.h \
bandstack.h \
button_text.h \
channel.h \
configure.h \
cw_menu.h \
discovered.h \
discovery.h \
display_menu.h \
diversity_menu.h \
dsp_menu.h \
equalizer_menu.h \
error_handler.h \
exit_menu.h \
ext.h \
fft_menu.h \
filter_menu.h \
filter.h \
freqent_menu.h \
frequency.h \
led.h \
memory.h \
meter_menu.h \
meter.h \
mode_menu.h \
mode.h \
new_discovery.h \
new_menu.h \
new_protocol.h \
noise_menu.h \
oc_menu.h \
old_discovery.h \
old_protocol.h \
pa_menu.h \
property.h \
radio_menu.h \
radio.h \
receiver.h \
rigctl_menu.h \
rigctl.h \
rx_menu.h \
rx_panadapter.h \
sliders.h \
step_menu.h \
store_menu.h \
store.h \
test_menu.h \
toolbar.h \
transmitter.h \
tx_menu.h \
tx_panadapter.h \
update.h \
version.h \
vfo_menu.h \
vfo.h \
vox_menu.h \
vox.h \
waterfall.h \
xvtr_menu.h \


OBJS= \
about_menu.o \
agc_menu.o \
ant_menu.o \
audio_waterfall.o \
audio.o \
band_menu.o \
band.o \
bandstack_menu.o \
button_text.o \
configure.o \
cw_menu.o \
cwramp.o \
discovered.o \
discovery.o \
display_menu.o \
diversity_menu.o \
dsp_menu.o \
equalizer_menu.o \
error_handler.o \
exit_menu.o \
ext.o \
fft_menu.o \
filter_menu.o \
filter.o \
freqent_menu.o \
frequency.o \
led.o \
main.o \
memory.o \
meter_menu.o \
meter.o \
mode_menu.o \
mode.o \
new_discovery.o \
new_menu.o \
new_protocol_programmer.o \
new_protocol.o \
noise_menu.o \
oc_menu.o \
old_discovery.o \
old_protocol.o \
pa_menu.o \
property.o \
radio_menu.o \
radio.o \
receiver.o \
rigctl_menu.o \
rigctl.o \
rx_menu.o \
rx_panadapter.o \
sliders.o \
step_menu.o \
store_menu.o \
store.o \
test_menu.o \
toolbar.o \
transmitter.o \
tx_menu.o \
tx_panadapter.o \
update.o \
version.o \
vfo_menu.o \
vfo.o \
vox_menu.o \
vox.o \
waterfall.o \
xvtr_menu.o \


$(PROGRAM): $(OBJS) $(REMOTE_OBJS) $(USBOZY_OBJS) $(LIMESDR_OBJS) $(FREEDV_OBJS) $(LOCALCW_OBJS) $(I2C_OBJS) $(GPIO_OBJS) $(PSK_OBJS) $(PURESIGNAL_OBJS) $(STEMLAB_OBJS)
	$(LINK) -o $(PROGRAM) $(OBJS) $(REMOTE_OBJS) $(USBOZY_OBJS) $(I2C_OBJS) $(GPIO_OBJS) $(LIMESDR_OBJS) $(FREEDV_OBJS) $(LOCALCW_OBJS) $(PSK_OBJS) $(PURESIGNAL_OBJS) $(STEMLAB_OBJS) $(LIBS)

all: prebuild $(PROGRAM) $(HEADERS) $(REMOTE_HEADERS) $(USBOZY_HEADERS) $(LIMESDR_HEADERS) $(FREEDV_HEADERS) $(LOCALCW_HEADERS) $(I2C_HEADERS) $(GPIO_HEADERS) $(PSK_HEADERS) $(PURESIGNAL_HEADERS) $(STEMLAB_HEADERS) $(SOURCES) $(REMOTE_SOURCES) $(USBOZY_SOURCES) $(LIMESDR_SOURCES) $(FREEDV_SOURCES) $(I2C_SOURCES) $(GPIO_SOURCES) $(PSK_SOURCES) $(PURESIGNAL_SOURCES) $(STEMLAB_SOURCES)

prebuild:
	rm -f version.o

clean:
	-rm -f *.o
	-rm -f $(PROGRAM)

install: $(PROGRAM)
	cp $(PROGRAM) /usr/local/bin

release: $(PROGRAM)
	cp $(PROGRAM) release/pihpsdr
	cd release; tar cvf pihpsdr.tar pihpsdr
	cd release; tar cvf pihpsdr-$(GIT_VERSION).tar pihpsdr
