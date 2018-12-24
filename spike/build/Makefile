include $(PRJROOT_ETHERIF)/Makefile.eif

CC		:= v850-elf-gcc
CXX		:= v850-elf-g++
LINK	:= v850-elf-gcc

CXXFLAGS := -fno-use-cxa-atexit -fno-exceptions -fno-rtti 
CFLAGS	:= -O0 -mdisable-callt -mno-app-regs -mtda=0
CFLAGS	+= -gdwarf-2 -Wall -Wno-unused-label -Wpointer-arith  -mv850e2v3 -Wa,-mno-bcond17 -msoft-float -Wa,-mwarn-signed-overflow -Wa,-mwarn-unsigned-overflow

IFLAGS	:= -I.
IFLAGS	+= $(INCLUDE_PATHS)
IFLAGS	+= -I$(PRJROOT_ASP)
IFLAGS	+= -I$(PRJROOT_ASP)/include
IFLAGS	+= -I$(PRJROOT_ASP)/target/v850_gcc
IFLAGS	+= -I$(PRJROOT_ASP)/arch
IFLAGS	+= -I$(PRJROOT_ASP)/arch/v850_gcc


VPATH	:= $(PRJROOT_ETHERIF)
VPATH	+= $(PRJROOT_ETHERIF)/Socket

%.o: %.S
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(IFLAGS)  $(CDEFS) $(CFLAGS) $<

%.o: %.cpp
	$(CXX) -c $(IFLAGS) $(CFLAGS) $(CDEFS) $(CXXFLAGS) $<

all: $(CXX_OBJ) $(C_OBJ)


clean:
	rm -f *.o