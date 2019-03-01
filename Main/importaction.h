#ifndef IMPORTACTION_H
#define IMPORTACTION_H
#include <cstdio>
#include <libxml/parser.h>
#include <vector>
#include <cstring>
using namespace std;
class ImportAction
{
public:
    ImportAction();
    static void loadinfo(char* docname,char* strname);
};

#endif // IMPORTACTION_H
