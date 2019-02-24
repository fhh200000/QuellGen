#include "importaction.h"
#define MAX_PATH_LENGTH 128
static int parseDoc(const char* docname)
{
    int width,height;
    const unsigned char* layers;
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
        printf("Processing Level %d.%d.%d\n",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        sprintf(path,"/home/fhh/桌面/tmp/%d.%d.%d.txt",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        printf("%s\n",path);
        fp = fopen(path,"w");
        fprintf(fp,"[QuellGen level data file]\n");
        fprintf(fp,"Level name:%s\n",cur->name);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("width"));
        fprintf(fp,"Width:%s\n",attr_value);
        sscanf(reinterpret_cast<const char*>(attr_value),"%d",&width);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("height"));
        fprintf(fp,"Height:%s\n",attr_value);
        layers = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("layers"));
        sscanf(reinterpret_cast<const char*>(attr_value),"%d",&height);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("layout"));
        //-------------------------------
        fprintf(fp,"Layer 0:\n");
        const unsigned char* pos=attr_value;
        int datacount=0;
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
                 while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
            fprintf(fp,"\n");
        }
        fprintf(fp,"Layer 1:\n");
        datacount=0;
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
                while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
            fprintf(fp,"\n");
        }
        fprintf(fp,"Layer 2:\n");
        switch(layers[0])
        {
            case '2':
            {
                for(int i=0;i<height;i++)
                {
                    for(int j=0;j<width;j++)
                        fprintf(fp,"0 ");
                fprintf(fp,"\n");
                }
            break;
            }
            case '3':
            {
                for(int i=0;i<height;i++)
                {
                    for(int j=0;j<width;j++)
                        while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
                    fprintf(fp,"\n");
                }
            break;
            }
        }
        //-------------------------------
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
