CFLAGS = -Wall -Wextra -Werror -O2

branchy-guest: branchy-guest.o payload.o
	$(CC) $^ -o $@

payload.o: payload.ld guest.img.o
	$(LD) -r -T $< -o $@

guest.o: guest.c
	$(CC) $(CFLAGS) -m64 -ffreestanding -fno-pic -c -o $@ $^

guest.img: guest.o
	$(LD) -T guest.ld $^ -o $@

%.img.o: %.img
	$(LD) -b binary -r $^ -o $@

.PHONY: clean
clean:
	$(RM) branchy-guest branchy-guest.o payload.o \
		guest.o guest.img guest.img.o
