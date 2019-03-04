#ifndef EXPORTACTION_H
#define EXPORTACTION_H
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "osspecificvars.h"
using namespace std;
class ExportAction
{
public:
    static void saveinfo(char* docname,char* strname,char* filelocation);
};

#endif // EXPORTACTION_H
