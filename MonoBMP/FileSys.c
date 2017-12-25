
void _error() {
	printf("Supported flags\n" \
		"--input=  Destination of original bmp\n" \
		"--output= Path to modified bmp\n" \
		"Missing flag mean that program replace it: --input=default.bmp and write modifications in current folder\n\n");
	exit(1);
}