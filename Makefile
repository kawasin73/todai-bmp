CC := gcc

.PHONY: all
all: copybmp gray

copybmp: copybmp.o bitmap.o

gray: gray.o bitmap.o

.PHONY: clean
clean:
	$(RM) *.o copybmp gray
