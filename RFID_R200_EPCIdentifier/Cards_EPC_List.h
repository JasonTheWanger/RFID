// #ifndef _EPCList
// #define _EPCList
// /*
//  * Contains the structure of a PVC White cards
//  */
// struct PVC_White {
//   unsigned char epc[12]; // Array contains the epc number of the pvc white cards
// };

// struct PVC_White pvc1 = {{0xE2, 0x00, 0x47, 0x01, 0x72, 0xA0, 0x60, 0x21, 0xA2, 0x0F, 0x01, 0x12}}; // Initializing the epc number of pvc card #1 
// struct PVC_White pvc2 = {{0xE2, 0x00, 0x47, 0x18, 0xCF, 0x20, 0x64, 0x26, 0x47, 0x9F, 0x01, 0x0B}}; // Initializing the epc number of pvc card #2

// /*
//  * Contains the strcutre of an eSticker 
//  */
// struct eSticker {
//   unsigned char epc[12]; // Array contains the epc number of the eSticker 
//   unsigned char USR[64]; // Array contains the user customizable data section information
// };

// struct eSticker eS1 = {{0x66, 0x66, 0x55, 0x55, 0x44, 0x44, 0x33, 0x33, 0x22, 0x22, 0x11, 0x11}, {}}; // Initializing the epc number of electronic sticker #1 

// #endif

#ifndef EPCList
#define EPCList
/*
 * Contains the structure of a PVC White cards
 */
struct card {
  unsigned char epc[12]; // Array contains the epc number of the pvc white cards
};

struct card card1 = {{0xE2, 0x00, 0x47, 0x01, 0x72, 0xA0, 0x60, 0x21, 0xA2, 0x0F, 0x01, 0x12}}; // Initializing the epc number of general rf card #1 
struct card card2 = {{0xE2, 0x00, 0x47, 0x18, 0xCF, 0x20, 0x64, 0x26, 0x47, 0x9F, 0x01, 0x0B}}; // Initializing the epc number of general rf card #2
struct card card3 = {{0x66, 0x66, 0x55, 0x55, 0x44, 0x44, 0x33, 0x33, 0x22, 0x22, 0x11, 0x11}}; // Initializing the epc number of general rf card #3
struct card epcList[3] = {card1, card2, card3};
uint16_t epcListSize = sizeof(epcList) / sizeof(struct card);

#endif


