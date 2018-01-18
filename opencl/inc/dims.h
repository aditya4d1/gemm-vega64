/**
* Will be included in both OpenCL
* kernel and runtime code
*/

#pragma once

const unsigned int xDim = 4096;
const unsigned int yDim = 4096;
const unsigned int xDim4 = xDim/4;
const unsigned int xDim8 = xDim/8;
const unsigned int x32 = 32;
const unsigned int x16 = 16;
const unsigned long Size = xDim * yDim * sizeof(float);
