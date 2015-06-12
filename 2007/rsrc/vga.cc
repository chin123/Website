#include "vga.h"

#include "io.h"

const int MiscOutputReg = 0x3c2;
const int DataReg = 0x3c0;
const int AddressReg = 0x3c0;

const char mode13[][32] = {
  { 0x03, 0x01, 0x0f, 0x00, 0x0e },            // 0x3c4, index 0-4
  { 0x5f, 0x4f, 0x50, 0x82, 0x54, 0x80, 0xbf, 0x1f,
    0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9c, 0x0e, 0x8f, 0x28, 0x40, 0x96, 0xb9, 0xa3,
    0xff },                                    // 0x3d4, index 0-0x18
  { 0, 0, 0, 0, 0, 0x40, 0x05, 0x0f, 0xff },   // 0x3ce, index 0-8
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
    0x41, 0, 0x0f, 0, 0 }                      // 0x3c0, index 0-0x14
};

VGA::VGA(void)
{
}

int VGA::setVideoMode(int xres, int yres, int bitdepth)
{
  int i;

  outb_p(0x63, MiscOutputReg);
  outb_p(0x00, 0x3da);

  for (i=0; i < 5; i++) {
    outb_p(i, 0x3c4);
    outb_p(mode13[0][i], 0x3c4+1);
  }

  outw_p(0x0e11, 0x3d4);

  for (i=0; i < 0x19; i++) {
    outb_p(i, 0x3d4);
    outb_p(mode13[1][i], 0x3d4+1);
  }  

  for (i=0; i < 0x9; i++) {
    outb_p(i, 0x3ce);
    outb_p(mode13[2][i], 0x3ce+1);
  }

  inb_p(0x3da);

  for (i=0; i < 0x15; i++) {
    inw(DataReg);
    outb_p(i, AddressReg);
    outb_p(mode13[3][i], DataReg);
  }

  outb_p(0x20, 0x3c0);

  return 1;
}

char *VGA::mapVideoMemory(void)
{
  char *vidmem = (char *) 0xf00a0000;  // address of phys[0xa0000]

  return vidmem;

  //  return k->mapPhysMem(root, 0xa0000, 0x10000);
}
