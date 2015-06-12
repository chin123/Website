#ifndef _vga_h
#define _vga_h


class VGA {
public:
  VGA(void);
  int setVideoMode(int xres, int yres, int bitdepth);
     // only valid parms are (320, 200, 8);
  
  char *mapVideoMemory(void);
     // hooks to OS to return pointer in virtual address space 
     // to physical 0xa0000
  ~VGA();
private:

};
  

#endif
