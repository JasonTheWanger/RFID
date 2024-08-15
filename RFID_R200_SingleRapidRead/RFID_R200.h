#ifndef _singleReadHeader
#define _singleReadHeader
/*
 * Contains single read command 
 */
struct RapidSingleRead { 
  unsigned char const readCmd[7]; // Array contains the decimal cmd for single read detection;
  int readCmdDec[7];
  int size;
};
struct RapidSingleRead singleRead = {{0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E}, {}, 7}; // initialize the corresponding struct command
#endif

#ifndef _maxRangeSetting
#define _maxRangeSetting
/*
 * Contains maximum receiving range setup command 
 */
struct maxRange {
  unsigned char const settingCmd[9]; // Array contains the decimal cmd for single read detection;
  int settingCmdDec[9];
  int size;
};
struct maxRange max = {{0xBB, 0x00, 0xB6, 0x00, 0x02, 0x07, 0xD0, 0x8F, 0x7E}, {}, 9}; // Initialize the corresponding struct command
#endif