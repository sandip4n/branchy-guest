SECTIONS
{
	.payload 0 : {
		guest_beg = .;
                guest.img.o
		guest_end = .;
	}
}
