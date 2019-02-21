#include "importaction.h"

ImportAction::ImportAction()
{

}
static int parseDoc(const char* docname)
{
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlKeepBlanksDefault(0);

    doc = xmlParseFile(docname);

    if(doc == nullptr) {
        fprintf(stderr, "doc error!\n");
        return 0;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur == nullptr) {
        fprintf(stderr, "root error!\n");
        xmlFreeDoc(doc);
        return 0;
    }

    if(xmlStrcmp(cur->name, reinterpret_cast<const xmlChar*>("serialise"))) {
        printf("end\n");
        return 0;
    }

    cur = cur->children;
    //不编辑关卡引导
    for(int i=0;i<13;i++)
            cur = cur->next;
    xmlChar* attr_value = nullptr;
    while(cur != nullptr) {
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("version"));
        printf("name=%s content=%s\n",cur->name,
        attr_value);
        cur = cur->next;
    }
    xmlFreeDoc(doc);
    return 0;
}

int main()
{
    const char* docname = "/home/fhh/桌面/test.txt";
    parseDoc(docname);
    return 1;
}
