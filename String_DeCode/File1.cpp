

int hex2int(char *hex) {
	int val = 0;
    while (*hex) {
        // get char + increment
		int byte = *hex++;
        // hex character to the 4bit equivalent number (ascii table)
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}
