#include "importaction.h"
#define MAX_PATH_LENGTH 128
/*
 * Import name
 * Still under construction
static int parseDoc(const char* docname)
{
    vector<char*> id = vector<char*>();
    vector<char*> name = vector<char*>();
    int i=0;
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
    cur = cur->children;
    //匹配到第一条
    printf("Now loading String data structure……\n");
    while(strcmp((char*)xmlNodeGetContent(cur->children),"STR_LEVEL_ZEN_E1"))
        cur = cur->next;
    while(i++<244)
        {
        id.push_back((char*)xmlNodeGetContent(cur->children));
        name.push_back((char*)xmlNodeGetContent(cur->children->next->next));
        //printf("%s->%s\n",(char*)xmlNodeGetContent(cur->children),(char*)xmlNodeGetContent(cur->children->next->next));
        cur = cur->next;
        }
    i=0;
    while(i<244)
        {
        printf("%s->%s\n",id.data()[i],name.data()[i]);
        i++;
        }
    xmlFreeDoc(doc);
    return 0;
}

int main()
{
    const char* docname = "/home/fhh/桌面/strings.xml";
    parseDoc(docname);
    return 0;
}

 */
static int parseDoc(const char* docname)
{
    int width,height,lspace=0,rspace=0;
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
        sprintf(path,"/home/fhh/桌面/tmp/%d.%d.%d.gmp",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        printf("%s\n",path);
        fp = fopen(path,"w");
        fprintf(fp,"[QuellGen level data file]\n");
        fprintf(fp,"Level name:%s\n",cur->name);
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("width"));
        //fprintf(fp,"Width:%s\n",attr_value);
        sscanf(reinterpret_cast<const char*>(attr_value),"%d",&width);
        lspace = width;
        rspace = width;
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("height"));
        //fprintf(fp,"Height:%s\n",attr_value);
        layers = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("layers"));
        sscanf(reinterpret_cast<const char*>(attr_value),"%d",&height);
        //attr_value = xmlGetProp(cur->children->next,reinterpret_cast<const xmlChar*>("array_size"));
        fprintf(fp,"Best solution:%s\nSolution:%s\nSoludrop:%s\n",\
                    xmlGetProp(cur->children->next,reinterpret_cast<const xmlChar*>("array_size")),\
                    xmlGetProp(cur->children,reinterpret_cast<const xmlChar*>("array_chars")),\
                    xmlGetProp(cur->children->next,reinterpret_cast<const xmlChar*>("array_chars")));
        attr_value = xmlGetProp(cur, reinterpret_cast<const xmlChar*>("layout"));
        //Get the space on the left/right-------------
        const unsigned char* pos=attr_value;
        const char* tmpchr = reinterpret_cast<const char*>(pos);
        char* tmpchr2 =const_cast<char*>(tmpchr);
        int datacount,lcurrent,rcurrent;
        for(int i=0;i<height;i++)
        {
            lcurrent = 0;
            rcurrent = 0;
            datacount = 0;
            while(datacount++,static_cast<int>(strtod(tmpchr2, &tmpchr2))==1)
            {
                lcurrent++;
                if(lcurrent==width) goto out;
            }
                //datacount++;
            //for(int j=0;j<width-lcurrent-1;j++)
             //   strtod(tmpchr2, &tmpchr2);
             while(datacount++<width)
                static_cast<int>(strtod(tmpchr2, &tmpchr2))==1?rcurrent++:rcurrent;
            lspace = lspace>lcurrent?lcurrent:lspace;
            rspace = rspace>rcurrent?rcurrent:rspace;
            out:;
        }
        fprintf(fp,"Width:%d\n",width-lspace-rspace);
        fprintf(fp,"Height:%d\n",height);
        fprintf(fp,"Left space:%d\n",lspace);
        fprintf(fp,"Right space:%d\n",rspace);
        //-----------------------------
        fprintf(fp,"Layer 0:\n");
        pos=attr_value;
        datacount=0;
        for(int i=0;i<height;i++)
        {
        //skip spaces
            pos+=lspace*2;
            for(int j=lspace;j<width-rspace;j++)
                 while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
            fprintf(fp,"\n");
            pos+=rspace*2;
        }
        fprintf(fp,"Layer 1:\n");
        datacount=0;
        for(int i=0;i<height;i++)
        {
            pos+=lspace*2;
            for(int j=lspace;j<width-rspace;j++)
                 while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
            fprintf(fp,"\n");
            pos+=rspace*2;
        }
        fprintf(fp,"Layer 2:\n");
        switch(layers[0])
        {
            case '2':
            {
                for(int i=0;i<height;i++)
                {
                    for(int j=lspace;j<width-rspace;j++)
                        fprintf(fp,"0 ");
                fprintf(fp,"\n");
                }
            break;
            }
            case '3':
            {
                for(int i=0;i<height;i++)
                {
                    pos+=lspace*2;
                    for(int j=lspace;j<width-rspace;j++)
                        while(fprintf(fp,"%c",*pos),datacount++,*pos++!=' ');
                    fprintf(fp,"\n");
                    pos+=rspace*2;
                }
            break;
            }
        }
        //-------------------------------
        fprintf(fp,"[End of file]\n");
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
