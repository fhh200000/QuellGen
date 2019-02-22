#include "importaction.h"
#define MAX_PATH_LENGTH 128
static int parseDoc(const char* docname)
{
    int *layer0,*layer1,*layer2;
    FILE *fp;
    //一个FILE指针就够了hahahaha
    char path[MAX_PATH_LENGTH];
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
    int curr=0;
    for(int i=0;i<13;i++)
            cur = cur->next;
    xmlChar* attr_value = nullptr;
    while(cur != nullptr) {
        printf("%d.%d.%d\n",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("layout"));
        sprintf(path,"/home/fhh/桌面/tmp/%d.%d.%d.txt",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        /*printf("name=%s content=%s\n",cur->name,
        attr_value);
        */
        printf("%s\n",path);
        fp = fopen(path,"w");
        fprintf(fp,"[QuellGen level data file]\n");
        fprintf(fp,"Level name:%s\n",cur->name);
        fprintf(fp,"Level data:%s\n",attr_value);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("width"));
        fprintf(fp,"Width:%s\n",attr_value);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("height"));
        fprintf(fp,"Height:%s\n",attr_value);
        fclose(fp);
        cur = cur->next;
        curr++;
    }
    xmlFreeDoc(doc);
    return 0;
}

int main()
{
    const char* docname = "/home/fhh/桌面/levels_zen.txt";
    parseDoc(docname);
    return 0;
}
