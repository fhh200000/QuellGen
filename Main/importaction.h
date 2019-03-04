#ifndef IMPORTACTION_H
#define IMPORTACTION_H
#include <cstdio>
#include <libxml/parser.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "osspecificvars.h"
using namespace std;
class ImportAction
{
public:
    static void loadinfo(char* docname,char* strname,char* filelocation);
};

#endif // IMPORTACTION_H
