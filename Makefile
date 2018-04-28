CC := gcc

.PHONY: all
all: copybmp

copybmp: copybmp.o bitmap.o

.PHONY: clean
clean:
	$(RM) *.o copybmp
