void lgdt(void *base, uint limit) {
        uint i[2];
        i[0]=limit << 16;
        i[1]=(uint)base;
        asm("lgdt (%0)": :"p" (((char *) i)+2));
}

descriptor *sgdt(void) {
        uint ptr[2];
        asm("sgdt (%0)": :"p" (((char *) ptr)+2));
        return(descriptor *)ptr[1];
}
