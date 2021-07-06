ROOTNAME=os_
HW=2
FOPTION=_main
RUNOPTIONS=DecOfInd.txt
CC=gcc
CFLAGS= -g -I.
LIBS =
DEPS = b_io.h
OBJ = $(ROOTNAME)$(HW)$(FOPTION).o b_io.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ROOTNAME)$(HW)$(FOPTION): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)  $(LIBS)

clean:
	rm *.o $(ROOTNAME)$(HW)$(FOPTION)

run: $(ROOTNAME)$(HW)$(FOPTION)
	./$(ROOTNAME)$(HW)$(FOPTION) $(RUNOPTIONS)
