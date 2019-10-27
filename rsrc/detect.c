vidmem=( (*((char*)(0x410+MAPPHY)) & 0x30) == 0x30) ?  // Monochrome?
	(char*)(0xb0000+MAPPHY):        // MDA
	(char*)(0xb8000+MAPPHY);        // VGA

