#include "importaction.h"
#include <QDebug>

using namespace std;
static int parseDoc(const char* docname,const char* strname,char* filelocation)
{
    //-----------------------------------
    vector<char*> lvl_zen_e = vector<char*>();
    vector<char*> lvl_classic = vector<char*>();
    vector<char*> lvl_d = vector<char*>();
    vector<char*> lvl_z = vector<char*>();
    vector<char*> lvl_g = vector<char*>();
    vector<char*> lvl_m = vector<char*>();
    vector<char*> lvl_b = vector<char*>();
    vector<char*> lvl_candy = vector<char*>();
    vector<char*>* id;
    int classindex[] = {21,12,11,2,22,0,27,29,37,13,15,32,28,16,38,3,25,33,39,26,36,9,19,20,23,14,8,7,30,10,34,1,31,18,17,35,24,6,51,4,52,52};
    int i=0,posi,tmp,reloadindex=0;
    int needReload=0;
    char* name=nullptr;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(strname);

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
    while(strcmp(reinterpret_cast<char*>(xmlNodeGetContent(cur->children)),"STR_LEVEL_ZEN_E1"))
        cur = cur->next;
    while(i++<244)
        {
        switch(xmlNodeGetContent(cur->children)[10])
        {
            case 'G':
            {
                id = &lvl_g;break;
            }
            case 'M':
            {
                id = &lvl_m;break;
            }
            case 'B':
            {
                id = &lvl_b;break;
            }
            case 'D':
            {
                id = &lvl_d;break;
            }
            case 'Z':
            {
                id = xmlNodeGetContent(cur->children)[11]=='E'?&lvl_zen_e:&lvl_z;break;
            }
            case 'C':
            {
                id = xmlNodeGetContent(cur->children)[11]=='A'?&lvl_candy:&lvl_classic;
                if(lvl_classic.size()==5)lvl_classic.push_back(const_cast<char*>(""));
                break;
            }
            default:
            {
                id=&lvl_classic;
            }
        }
            id->push_back(reinterpret_cast<char*>(xmlNodeGetContent(cur->children->next->next)));
        cur = cur->next;
        }
    i=0;
    //fixed a name bug caused by Quell Zen 233333
    lvl_classic.push_back(lvl_zen_e.front());
    lvl_classic.push_back(const_cast<char*>("Candle"));
    xmlFreeDoc(doc);
    //-----------------------------------
    int width,height,lspace=0,rspace=0;
    const unsigned char* layers;
    FILE *fp;
    //一个FILE指针就够了hahahaha
    char path[MAX_PATH_LENGTH];
    xmlKeepBlanksDefault(0);
    doc = xmlParseFile(docname);

    if(doc == nullptr)
    {
        fprintf(stderr, "doc error!\n");
        return 0;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur == nullptr)
    {
        fprintf(stderr, "root error!\n");
        xmlFreeDoc(doc);
        return 0;
    }

    if(xmlStrcmp(cur->name, reinterpret_cast<const xmlChar*>("serialise")))
    {
        printf("end\n");
        return 0;
    }

    cur = cur->children;
    //不编辑关卡引导
    int curr=0;
    for(int i=0;i<13;i++)
            cur = cur->next;
    xmlChar* attr_value = nullptr;
    while(cur != nullptr)
    {
        needReload = 0;
        name = nullptr;
        printf("Processing Level %d.%d.%d\n",(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        sprintf(path,filelocation,(curr/16)+1,(curr&12)/4+1,(curr&3)+1);
        printf("%s\n",path);
        fp = fopen(path,"w");
        fprintf(fp,"[QuellGen level data file]\n");
        fprintf(fp,"Level ID:%s\n",cur->name);
        //Get name--------
        switch(cur->name[4])
        {
            case 'd':
            {
                tmp = atoi((reinterpret_cast<const char*>(cur->name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_d%d\n",&posi);
                name = lvl_d.data()[posi-1];
                break;
            }
            case 'z':
            {
                tmp = atoi((reinterpret_cast<const char*>(cur->name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_z%d\n",&posi);
                name = lvl_z.data()[posi-1];
                break;
            }
            case 'g':
            {
                tmp = atoi((reinterpret_cast<const char*>(cur->name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_g%d\n",&posi);
                name = lvl_d.data()[posi-1];
                break;
            }
            case 'c':
            {
                tmp = (cur->name[9]=='_');//select "candy"
                    if(!tmp)
                    {
                        needReload=1;
                        goto outswitch;
                    }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_candy_%d\n",&posi);
                name = lvl_candy.data()[posi-1];
                break;
            }
            case 'b':
            {
                tmp = atoi((reinterpret_cast<const char*>(cur->name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_b%d\n",&posi);
                name = lvl_b.data()[posi-1];
                break;
            }
            case 'm':
            {
                tmp = atoi((reinterpret_cast<const char*>(cur->name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_m%d\n",&posi);
                name = lvl_m.data()[posi-1];
                break;
            }
            case 'q':
            {
                sscanf(reinterpret_cast<const char*>(cur->name),"lvl_qm_e%d\n",&posi);
                name = lvl_zen_e.data()[posi-1];
                break;
            }
            default:
            {
                needReload=1;
            }

            outswitch:if(needReload)
            {
                //printf("%s:%s\n",path,(char*)cur->name);
                //name = (char*)cur->name;
                name = lvl_classic.data()[classindex[reloadindex++]];
            }
        }
        //----------------
        fprintf(fp,"Level name:%s\n",name);
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
            while(static_cast<void>(datacount++),static_cast<int>(strtod(tmpchr2, &tmpchr2))==1)
            {
                lcurrent++;
                if(lcurrent==width) goto out2;
            }
                //datacount++;
            //for(int j=0;j<width-lcurrent-1;j++)
             //   strtod(tmpchr2, &tmpchr2);
             while(datacount++<width)
                static_cast<int>(strtod(tmpchr2, &tmpchr2))==1?rcurrent++:rcurrent;
            lspace = lspace>lcurrent?lcurrent:lspace;
            rspace = rspace>rcurrent?rcurrent:rspace;
            out2:;
        }
        fprintf(fp,"Width:%d\n",width-lspace-rspace);
        fprintf(fp,"Height:%d\n",height);
        fprintf(fp,"Left space:%d\n",lspace);
        fprintf(fp,"Right space:%d\n",rspace);
        fprintf(fp,"Layers:%c\n",layers[0]);
        //-----------------------------
        fprintf(fp,"Layer 0:\n");
        pos=attr_value;
        datacount=0;
        for(int i=0;i<height;i++)
        {
        //skip spaces
            pos+=lspace*2;
            for(int j=lspace;j<width-rspace;j++)
                 while(static_cast<void>(fprintf(fp,"%c",*pos)),static_cast<void>(datacount++),*pos++!=' ');
            fprintf(fp,"\n");
            pos+=rspace*2;
        }
        fprintf(fp,"Layer 1:\n");
        datacount=0;
        for(int i=0;i<height;i++)
        {
            pos+=lspace*2;
            for(int j=lspace;j<width-rspace;j++)
                 while(static_cast<void>(fprintf(fp,"%c",*pos)),static_cast<void>(datacount++),*pos++!=' ');
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
                        while(static_cast<void>(fprintf(fp,"%c",*pos)),static_cast<void>(datacount++),*pos++!=' ');
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
    filelocation[strlen(filelocation)-12]='\0';
    QString tmpstr = QString(filelocation);
    tmpstr.append("general.gmp");
    filelocation = tmpstr.toLocal8Bit().data();
    printf("%s\n",filelocation);
    fflush(stdin);
    fp = fopen(filelocation,"w");
    fprintf(fp,"[QuellGen level general file]\n\
Count of lvl_zen_e:%d\n\
Count of lvl_classic:%d\n\
Count of lvl_d:%d\n\
Count of lvl_z:%d\n\
Count of lvl_g:%d\n\
Count of lvl_m:%d\n\
Count of lvl_b:%d\n\
Count of lvl_candy:%d\n\
[End of file]",\
            static_cast<int>(lvl_zen_e.size()),\
            static_cast<int>(lvl_classic.size()),\
            static_cast<int>(lvl_d.size()),\
            static_cast<int>(lvl_z.size()),\
            static_cast<int>(lvl_g.size()),\
            static_cast<int>(lvl_m.size()),\
            static_cast<int>(lvl_b.size()),\
            static_cast<int>(lvl_candy.size())\
            );
    fclose(fp);
    MainWindow::self->setStatus("完成导入");
    return 0;
}

void ImportAction::loadinfo(char* docname,char* strname,char* filelocation)
{
    parseDoc(docname,strname,filelocation);
}

