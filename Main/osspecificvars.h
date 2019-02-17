#ifndef OSSPECIFICVARS_H
#define OSSPECIFICVARS_H
#ifdef __linux__
//Linux here
#define BLOCKSIZE 48
#endif
#ifdef _WIN32
//Windows here
#define BLOCKSIZE 36
#endif
#endif // OSSPECIFICVARS_H
