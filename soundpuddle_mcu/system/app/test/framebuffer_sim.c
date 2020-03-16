#include <stdio.h>
#include <unistd.h>
#include <framebuffer.h>
#include <framebuffer.c>

static char ANSI[7][100] = {
  "\x1b[0m#\0",
  "\x1b[31m#\0",
  "\x1b[32m#\0",
  "\x1b[33m#\0",
  "\x1b[34m#\0",
  "\x1b[35m#\0",
  "\x1b[36m#\0"
};

#define ANSI_RESET "\x1b[0m\0"

static const char sector_strip_printf_offsets[FB_STRIPS_PER_SECTOR][16] = {
  "", // Unused, zero index is variable
  "            ",
  "            ",
  "    ",
  "            ",
  "            ",
};

static inline const char * sector_strip0_printf_offset(uint8_t sector)
{
  return (sector ? sector % 3 ? "  " : " " : "");
}

static inline const char * sector_strip_printf_offset(uint8_t sector, uint8_t sector_strip)
{
  return (sector_strip > 0 ? sector_strip_printf_offsets[sector_strip] : sector_strip0_printf_offset(sector));
}

static inline const char * strip_printf_offset(uint8_t strip)
{
  return sector_strip_printf_offset(strip_to_sector(strip), strip_to_sector_strip(strip));
}
int main(void)
{
  framebuffer_init();
  uint32_t values[72];
  uint32_t times = 0;
  do{
    uint8_t i = 0;
    for(; i < FB_STRIP_NUM; i++){
      values[i] = i;
    }
    /*
    memset(values, times, FB_STRIP_NUM * 4);
    //printf("here");
    #ifdef SIMULATE_OUT
    framebuffer_migrate_out(values);
    #elif SIMULATE_IN
    framebuffer_migrate_in(values);
    #endif
    */
    framebuffer_spiral_out_fast(values);
    for(uint16_t j = 0; j < FB_STRIP_NUM ; j++){
      //printf("strip %d sector %d sector_strip %d offset %d\n", j, strip_to_sector(j), strip_to_sector_strip(j), strip_offset(j));
      printf("%s", strip_printf_offset(j));
      uint16_t logical = strip_offset(j);
      char * space = "";
      for(uint16_t i = 0 ; i < FB_STRIP_LEN + 12 - strip_offset(j); i++){
        if (logical >= FB_LED_IDX_SAFE_LOWERBOUND ){
          space = " ";
        } else {
          
        }
        logical++;
        printf( "%s%s", ANSI[ FB_INDEX(j,i) % 7], space);
        
      }
      printf("%s\n", ANSI_RESET);
    }
    usleep(500000);
    if (times < 10000) printf("\e[1;1H\e[2J");

  } while(times ++ < 10000);
}