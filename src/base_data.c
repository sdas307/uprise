#include "base_data.h"

const xVector2 house[] =
{
    { 64, 128 },
};
const int houseCount = ARRAY_COUNT(house);

const xVector2 lightPosts[] =
{
    { 66, 320 - 32 },
};
const int lightPostsCount = ARRAY_COUNT(lightPosts);

const TileObject cliffColliders[] =
{
    { 1152, 0, 5 },
    { 1152, 64, 5 },
    { 1152, 128, 5 },
    { 1152, 192, 5 },
    { 1152, 256, 5 },
    { 1152, 320, 5 },
    { 1152, 384, 5 },
    { 1152, 448, 5 },
    { 1152, 512, 5 },
    { 1152, 576, 5 },
    { 1152, 640, 5 },
    { 0, 704, 7 },
    { 64, 704, 7 },
    { 128, 704, 7 },
    { 192, 704, 7 },
    { 256, 704, 7 },
    { 320, 704, 7 },
    { 384, 704, 7 },
    { 448, 704, 7 },
    { 512, 704, 7 },
    { 576, 704, 7 },
    { 640, 704, 7 },
    { 704, 704, 7 },
    { 960, 704, 7 },
    { 1024, 704, 7 },
    { 1088, 704, 7 },
    { 1152, 704, 8 },
    { 0, 768, 10 },
    { 64, 768, 10 },
    { 128, 768, 10 },
    { 192, 768, 10 },
    { 256, 768, 10 },
    { 320, 768, 10 },
    { 384, 768, 10 },
    { 448, 768, 10 },
    { 512, 768, 10 },
    { 576, 768, 10 },
    { 640, 768, 10 },
    { 704, 768, 10 },
    { 960, 768, 10 },
    { 1024, 768, 10 },
    { 1088, 768, 13 },
    { 1152, 768, 11 },
    { 0, 832, 13 },
    { 64, 832, 13 },
    { 128, 832, 13 },
    { 192, 832, 13 },
    { 256, 832, 13 },
    { 320, 832, 13 },
    { 384, 832, 13 },
    { 448, 832, 13 },
    { 512, 832, 13 },
    { 576, 832, 13 },
    { 640, 832, 13 },
    { 704, 832, 13 },
    { 960, 832, 13 },
    { 1024, 832, 13 },
    { 1088, 832, 13 },
    { 1152, 832, 14 },
};
const int cliffCollidersCount = ARRAY_COUNT(cliffColliders);

const xVector2 cliffStairs[] =
{
    { 768, 704 },
};
const int cliffStairsCount = ARRAY_COUNT(cliffStairs);

const TileObject upperLayer[] =
{
    { 704, 0, 4 },
    { 704, 64, 4 },
    { 704, 128, 4 },
    { 0, 192, 1 },
    { 64, 192, 2 },
    { 128, 192, 2 },
    { 192, 192, 2 },
    { 256, 192, 2 },
    { 320, 192, 2 },
    { 384, 192, 2 },
    { 448, 192, 2 },
    { 512, 192, 2 },
    { 704, 192, 12 },
    { 0, 256, 4 },
    { 0, 320, 12 }
};
const int upperLayerCount = ARRAY_COUNT(upperLayer);

const TileObject farmlandsDry[] =
{
    { 1344, 256, 1 },
    { 1408, 256, 2 },
    { 1472, 256, 2 },
    { 1536, 256, 2 },
    { 1600, 256, 2 },
    { 1664, 256, 3 },
    { 1344, 320, 4 },
    { 1408, 320, 5 },
    { 1472, 320, 5 },
    { 1536, 320, 5 },
    { 1600, 320, 5 },
    { 1664, 320, 6 },
    { 1344, 384, 7 },
    { 1408, 384, 8 },
    { 1472, 384, 8 },
    { 1536, 384, 8 },
    { 1600, 384, 8 },
    { 1664, 384, 9 },
};
const int farmlandsDryCount = ARRAY_COUNT(farmlandsDry);

const TileObject farmlandsWet[] =
{
    { 1344, 256, 1 },
    { 1408, 256, 2 },
    { 1472, 256, 2 },
    { 1536, 256, 2 },
    { 1600, 256, 2 },
    { 1664, 256, 3 },
    { 1344, 320, 4 },
    { 1408, 320, 5 },
    { 1472, 320, 5 },
    { 1536, 320, 5 },
    { 1600, 320, 5 },
    { 1664, 320, 6 },
    { 1344, 384, 7 },
    { 1408, 384, 8 },
    { 1472, 384, 8 },
    { 1536, 384, 8 },
    { 1600, 384, 8 },
    { 1664, 384, 9 },
};
const int farmlandsWetCount = ARRAY_COUNT(farmlandsWet);

const xVector2 grass1[] =
{
    { 2880, 128 },
    { 0, 448 },
    { 2240, 576 },
    { 896, 640 },
    { 256, 704 },
    { 2944, 832 },
    { 1856, 896 },
    { 1920, 896 },
    { 1920, 1088 },
    { 64, 1216 },
    { 768, 1344 },
    { 896, 1408 },
    { 2048, 1472 },
    { 128, 1536 },
    { 2176, 1536 },
};
const int grass1Count = ARRAY_COUNT(grass1);

const xVector2 grass2[] =
{
    { 1856, 192 },
    { 512, 320 },
    { 1024, 320 },
    { 64, 512 },
    { 2880, 640 },
    { 1408, 832 },
    { 2240, 896 },
    { 384, 1088 },
    { 1024, 1216 },
    { 1472, 1216 },
    { 2304, 1216 },
    { 1280, 1536 },
    { 2816, 1536 },
    { 1344, 1600 },
};
const int grass2Count = ARRAY_COUNT(grass2);

const xVector2 grass3[] =
{
    { 2432, 64 },
    { 448, 512 },
    { 2752, 576 },
    { 2048, 640 },
    { 2560, 960 },
    { 1216, 1024 },
    { 1408, 1152 },
    { 2688, 1280 },
    { 2176, 1344 },
    { 128, 1408 },
    { 1216, 1472 },
    { 2432, 1600 },
};
const int grass3Count = ARRAY_COUNT(grass3);

const xRectangle hedgeContinuous[] =
{
    { 0, 0, 768, 64 },
    { 448, 256, 64, 192 },
};
const int hedgeContinuousCount = ARRAY_COUNT(hedgeContinuous);


const xVector2 hedges[] =
{
    { 0, 64 },
    { 0, 128 }
};
const int hedgesCount = ARRAY_COUNT(hedges);

const xVector2 upperLayerStairs[] =
{
    { 576, 192 },
};
const int upperLayerStairsCount = ARRAY_COUNT(upperLayerStairs);

const Vector2 treesOakLarge[] =
{
    { 704, -128 },
    { 768, -128 },
};
const int treesOakLargeCount = ARRAY_COUNT(treesOakLarge);

const xVector2 wildflower1[] =
{
    { 1728, 64 },
    { 832, 192 },
    { 2176, 384 },
    { 896, 512 },
    { 512, 640 },
    { 1664, 640 },
    { 2752, 704 },
    { 2560, 1216 },
    { 256, 1280 },
    { 768, 1536 },
    { 1664, 1536 },
    { 64, 1600 },
};
const int wildflower1Count = ARRAY_COUNT(wildflower1);

const xVector2 wildflower2[] =
{
    { 2688, 0 },
    { 1344, 64 },
    { 2240, 192 },
    { 512, 256 },
    { 2752, 448 },
    { 0, 640 },
    { 2368, 768 },
    { 1664, 832 },
    { 576, 1216 },
    { 0, 1344 },
    { 1856, 1344 },
    { 2880, 1344 },
    { 1024, 1536 },
};
const int wildflower2Count = ARRAY_COUNT(wildflower2);


const xVector2 wildflower3[] =
{
    { 64, 64 },
    { 640, 128 },
    { 1024, 192 },
    { 2496, 320 },
    { 2048, 1216 },
    { 1344, 1408 },
    { 448, 1536 },
    { 2688, 1600 },
};
const int wildflower3Count = ARRAY_COUNT(wildflower3);