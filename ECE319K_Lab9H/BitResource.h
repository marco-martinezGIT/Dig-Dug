#ifndef RESOURCE_DATA_H
#define RESOURCE_DATA_H

#include <cstdint>
#include <stdint.h>

// Sprites
extern const unsigned short taizo_stand[];
extern const unsigned short block_1[196];
extern const unsigned short block_2[196];
extern const unsigned short block_3[196];
extern const unsigned short block_4[196];
extern const unsigned short block_5[196];
extern const unsigned short block_6[196];
extern const unsigned short block_7[196];
extern const unsigned short* blocks_arr[7];

// Loading animation frames (17x17 = 289 pixels)
extern const unsigned short load1[289];
extern const unsigned short load2[289];
extern const unsigned short load3[289];
extern const unsigned short load4[289];
extern const unsigned short load5[289];
extern const unsigned short load6[289];
extern const unsigned short load7[289];
extern const unsigned short load8[289];
extern const unsigned short monster1[289];
extern const unsigned short monster2[289];


extern const unsigned short* loadingArr[8];
extern const unsigned short* monsters[2];

#endif // RESOURCE_DATA_H
