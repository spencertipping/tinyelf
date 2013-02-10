# Disable implicit build rules (otherwise helloworld < helloworld.c via $(CC))
.SUFFIXES:
all: tinyelf examples
examples: helloworld helloworld-c

.PHONY: clean
clean:
	rm -f tinyelf helloworld helloworld-*

.SECONDARY: helloworld-c helloworld-bin

# ELF construction process
%: %-bin makefile
	cat tinyelf $< > $@
	chmod +x $@

%-bin: %-c makefile
	objcopy -O binary -j .text $< $@
	chmod -x $@

%-c: %.c makefile
	gcc -o $@ -nostdlib $<

# Header compilation (from text description of binary data)
%: %.binary makefile
	./binary perl "file::write('$@', compile_binary('$<'))"
