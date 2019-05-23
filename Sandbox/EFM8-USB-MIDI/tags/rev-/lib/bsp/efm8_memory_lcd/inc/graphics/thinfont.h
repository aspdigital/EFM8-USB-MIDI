#define thinfont_width 800
#define thinfont_height 8
static SI_SEGMENT_VARIABLE(thinfont_bits[], const uint8_t, SI_SEG_CODE) = {
  0x00, 0x20, 0x50, 0x50, 0x20, 0xC0, 0x60, 0x60, 0x10, 0x40, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x20, 0x70, 0xF8, 0x10, 0xF8, 0x30, 0xF8, 
  0x70, 0x70, 0x00, 0x00, 0x08, 0x00, 0x80, 0x70, 0x70, 0x70, 0xF0, 0x70, 
  0xE0, 0xF8, 0xF8, 0x70, 0x88, 0x70, 0x38, 0x88, 0x80, 0x88, 0x88, 0x70, 
  0xF0, 0x70, 0xF0, 0x78, 0xF8, 0x88, 0x88, 0x88, 0x88, 0x88, 0xF8, 0x70, 
  0x00, 0x70, 0x20, 0x00, 0x40, 0x00, 0x80, 0x00, 0x08, 0x00, 0x30, 0x00, 
  0x80, 0x20, 0x10, 0x80, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x60, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x50, 0x78, 0xC8, 0x90, 0x20, 
  0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x88, 0x60, 0x88, 0x10, 
  0x30, 0x80, 0x40, 0x08, 0x88, 0x88, 0x60, 0x60, 0x10, 0x00, 0x40, 0x88, 
  0x08, 0x88, 0x88, 0x88, 0x90, 0x80, 0x80, 0x88, 0x88, 0x20, 0x10, 0x90, 
  0x80, 0xD8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80, 0x20, 0x88, 0x88, 0x88, 
  0x88, 0x88, 0x08, 0x40, 0x00, 0x10, 0x50, 0x00, 0x20, 0x00, 0x80, 0x00, 
  0x08, 0x00, 0x48, 0x78, 0x80, 0x00, 0x00, 0x80, 0x20, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
  0x20, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0xF8, 
  0x80, 0x10, 0xA0, 0x40, 0x40, 0x10, 0xA8, 0x20, 0x00, 0x00, 0x00, 0x08, 
  0x98, 0x20, 0x08, 0x20, 0x50, 0xF0, 0x80, 0x10, 0x88, 0x88, 0x60, 0x60, 
  0x20, 0xF8, 0x20, 0x08, 0x08, 0x88, 0x88, 0x80, 0x88, 0x80, 0x80, 0x80, 
  0x88, 0x20, 0x10, 0xA0, 0x80, 0xA8, 0xC8, 0x88, 0x88, 0x88, 0x88, 0x80, 
  0x20, 0x88, 0x88, 0x88, 0x50, 0x88, 0x10, 0x40, 0x80, 0x10, 0x88, 0x00, 
  0x10, 0x70, 0xB0, 0x70, 0x68, 0x70, 0x40, 0x88, 0xB0, 0x60, 0x30, 0x90, 
  0x20, 0xD0, 0xB0, 0x70, 0xF0, 0x68, 0xB0, 0x70, 0xE0, 0x88, 0x88, 0x88, 
  0x88, 0x88, 0xF8, 0x40, 0x20, 0x10, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x20, 0x00, 0x50, 0x70, 0x20, 0x40, 0x00, 0x40, 0x10, 0x70, 0xF8, 
  0x00, 0xF8, 0x00, 0x10, 0xA8, 0x20, 0x10, 0x10, 0x90, 0x08, 0xF0, 0x20, 
  0x70, 0x78, 0x00, 0x00, 0x40, 0x00, 0x10, 0x10, 0x68, 0x88, 0xF0, 0x80, 
  0x88, 0xF0, 0xF0, 0xB8, 0xF8, 0x20, 0x10, 0xC0, 0x80, 0xA8, 0xA8, 0x88, 
  0xF0, 0x88, 0xF0, 0x70, 0x20, 0x88, 0x88, 0xA8, 0x20, 0x50, 0x20, 0x40, 
  0x40, 0x10, 0x00, 0x00, 0x00, 0x08, 0xC8, 0x80, 0x98, 0x88, 0xE0, 0x88, 
  0xC8, 0x20, 0x10, 0xA0, 0x20, 0xA8, 0xC8, 0x88, 0x88, 0x98, 0xC8, 0x80, 
  0x40, 0x88, 0x88, 0x88, 0x50, 0x88, 0x10, 0x80, 0x20, 0x08, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x08, 0x40, 0xA8, 0x00, 
  0x40, 0x10, 0xA8, 0x20, 0x60, 0x00, 0x00, 0x20, 0xC8, 0x20, 0x20, 0x08, 
  0xF8, 0x08, 0x88, 0x40, 0x88, 0x08, 0x60, 0x60, 0x20, 0xF8, 0x20, 0x20, 
  0xA8, 0xF8, 0x88, 0x80, 0x88, 0x80, 0x80, 0x88, 0x88, 0x20, 0x10, 0xA0, 
  0x80, 0x88, 0x98, 0x88, 0x80, 0xA8, 0xA0, 0x08, 0x20, 0x88, 0x88, 0xA8, 
  0x50, 0x20, 0x40, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x78, 0x88, 0x80, 
  0x88, 0xF8, 0x40, 0x78, 0x88, 0x20, 0x10, 0xC0, 0x20, 0xA8, 0x88, 0x88, 
  0xF0, 0x78, 0x80, 0x70, 0x40, 0x88, 0x88, 0xA8, 0x20, 0x78, 0x20, 0x40, 
  0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 
  0xF0, 0x98, 0x90, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x60, 0x40, 
  0x88, 0x20, 0x40, 0x88, 0x10, 0x88, 0x88, 0x40, 0x88, 0x10, 0x60, 0x20, 
  0x10, 0x00, 0x40, 0x00, 0xA8, 0x88, 0x88, 0x88, 0x90, 0x80, 0x80, 0x88, 
  0x88, 0x20, 0x90, 0x90, 0x80, 0x88, 0x88, 0x88, 0x80, 0x90, 0x90, 0x08, 
  0x20, 0x88, 0x50, 0xA8, 0x88, 0x20, 0x80, 0x40, 0x10, 0x10, 0x00, 0x00, 
  0x00, 0x88, 0x88, 0x88, 0x88, 0x80, 0x40, 0x08, 0x88, 0x20, 0x90, 0xA0, 
  0x20, 0x88, 0x88, 0x88, 0x80, 0x08, 0x80, 0x08, 0x48, 0x98, 0x50, 0xA8, 
  0x50, 0x08, 0x40, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x20, 0x00, 0x50, 0x20, 0x18, 0x68, 0x00, 0x10, 0x40, 0x00, 0x00, 
  0x40, 0x00, 0x60, 0x80, 0x70, 0x70, 0xF8, 0x70, 0x10, 0x70, 0x70, 0x40, 
  0x70, 0x60, 0x00, 0x40, 0x08, 0x00, 0x80, 0x20, 0x70, 0x88, 0xF0, 0x70, 
  0xE0, 0xF8, 0x80, 0x70, 0x88, 0x70, 0x60, 0x88, 0xF8, 0x88, 0x88, 0x70, 
  0x80, 0x68, 0x88, 0xF0, 0x20, 0x70, 0x20, 0x50, 0x88, 0x20, 0xF8, 0x70, 
  0x08, 0x70, 0x00, 0xFC, 0x00, 0x78, 0xF0, 0x70, 0x78, 0x70, 0x40, 0x70, 
  0x88, 0x70, 0x60, 0x90, 0x70, 0x88, 0x88, 0x70, 0x80, 0x08, 0x80, 0xF0, 
  0x30, 0x68, 0x20, 0x50, 0x88, 0x70, 0xF8, 0x30, 0x20, 0x60, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
