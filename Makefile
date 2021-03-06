CC := gcc

.PHONY: all
all: copybmp gray thermo post sobel-main sobel-binary

copybmp: copybmp.o bitmap.o

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

post: post.o bitmap.o

sobel-main: sobel-main.o sobel.o bitmap.o

sobel-binary: sobel-binary.o sobel.o bitmap.o

.PHONY: clean
clean:
	$(RM) *.o copybmp gray thermo post sobel-main sobel-binary
