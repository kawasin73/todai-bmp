CC := gcc

.PHONY: all
all: copybmp gray thermo

copybmp: copybmp.o bitmap.o

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

.PHONY: clean
clean:
	$(RM) *.o copybmp gray thermo
