void reboot() {
	// Insert code here to setup the BIOS to do a warm/cold reboot.
	// I think it's in BIOS at 40:72 (Note: that's in real mode) (word)
	//	0x1234 - Warm boot
	//	0x4321 - PS/2
	//	0x5678 - Suspend system
	// 	0x9abc - Manufacturing test mode
	// 	0xabcd - POST loop mode
	//	0x0064 - Burn-in mode
	// Also location dword ptr 40:67 contains re-entry pointer after reset
	// If you find out more, let me know!
	kprintf("Rebooting...\n");
	lidt((void*)0xffffffff,0);
	asm("int $0x00");
}

// Rebooting your computer.	Douglas Armstrong
