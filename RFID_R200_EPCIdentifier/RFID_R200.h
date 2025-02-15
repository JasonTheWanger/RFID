#ifndef _singleReadHeader
#define _singleReadHeader
/*
 * Contains single read command 
 */
struct RapidSingleRead { 
  unsigned char const readCmd[10]; // Array contains the decimal cmd for single read detection;
  int readCmdDec[10];
  int size;
};
struct RapidSingleRead singleRead = {{0xBB, 0x00, 0x27, 0x00, 0x03, 0x22, 0x00, 0x01, 0x4D, 0x7E}, {}, 10}; // initialize the corresponding struct command
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

#ifndef _cmdPointer
#define _cmdPointer

struct RapidSingleRead *cmd = &(singleRead); // BB 00 27 00 03 22 00 01 4D 7E
struct maxRange *maximum = &(max); // BB 00 B6 00 02 07 D0 8F 7E

#endif

#ifndef formatFlag
#define formatFlag

int newLineFlag = 0; // Boolean flag variable that controls whether to output a \n character when RFID output is detected

#endif
