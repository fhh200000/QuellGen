#ifndef OSSPECIFICVARS_H
#define OSSPECIFICVARS_H
/*
 * Due to Windows' HiDpi auto resize,
 * The size of 48×48 seems too big.
 * Here we define it to 36px so it can scratch approximately
 * into the original 48 px in 1.25x resize.
*/
#ifdef __linux__
//Linux here
#define BLOCKSIZE 48
#endif
#ifdef _WIN32
//Windows here
#define BLOCKSIZE 36
#pragma warning(disable:4068)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif // OSSPECIFICVARS_H
