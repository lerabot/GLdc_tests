TARGET = main.elf
OBJS = main.o utils.o


REAP_LIBS = $(addprefix lib/, $(REAP_OBJ))
REAP_OBJ  = gl_png.o debug_screen.o game_object.o scene.o  gl_font.o gl_pvr_texture.o player.o

KOS_CFLAGS += -std=c99 -I$(KOS_PORTS)/include/lua
#KOS_ROMDISK_DIR = romdisk

all: rm-elf $(TARGET)

include $(KOS_BASE)/Makefile.rules

clean:
	@$(RM) $(TARGET) $(OBJS) $(REAP_LIBS) romdisk.* *.cdi *.iso

rm-elf:
	@$(RM) $(TARGET) romdisk.*

$(TARGET): $(OBJS) $(REAP_LIBS) romdisk.o
	$(KOS_CC) $(KOS_CFLAGS) $(KOS_LDFLAGS) -o $(TARGET) $(KOS_START) \
		$(OBJS) $(REAP_LIBS) romdisk.o $(OBJEXTRA) -lpng -llua -lGLdc -lmp3 -loggvorbisplay -lvorbis -logg -lm -lz  $(KOS_LIBS)

#make a bunch of romdisk here
romdisk.img:
	$(KOS_GENROMFS) -f romdisk.img -d romdisk

romdisk.o: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o romdisk.img romdisk romdisk.o

run: $(TARGET)
	$(KOS_LOADER) $(TARGET)

dist:
	rm -f $(OBJS) romdisk.o romdisk.img
	$(KOS_STRIP) $(TARGET)
