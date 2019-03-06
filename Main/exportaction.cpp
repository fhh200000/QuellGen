#include <cstdio>
#include <libxml/parser.h>
#include <cstring>
#include <vector>
#define MAX_PATH_LENGTH 128
using namespace std;
int saveinfo(void)
{
    char path[MAX_PATH_LENGTH]={0};
    FILE *fp;
    unsigned long count;
    fp = fopen("/home/fhh/桌面/tmp3/general.gmp","r");
    fscanf(fp,"[QuellGen level general file]\n");
    fscanf(fp,"Count of lvl_zen_e:%ld\n",&count);
    vector<xmlNodePtr> lvl_zen_e = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_classic:%ld\n",&count);
    vector<xmlNodePtr> lvl_classic = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_d:%ld\n",&count);
    vector<xmlNodePtr> lvl_d = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_z:%ld\n",&count);
    vector<xmlNodePtr> lvl_z = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_g:%ld\n",&count);
    vector<xmlNodePtr> lvl_g = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_m:%ld\n",&count);
    vector<xmlNodePtr> lvl_m = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_b:%ld\n",&count);
    vector<xmlNodePtr> lvl_b = vector<xmlNodePtr>(count);
    fscanf(fp,"Count of lvl_candy:%ld\n",&count);
    vector<xmlNodePtr> lvl_candy = vector<xmlNodePtr>(count);
    //Get nodes of every level
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlKeepBlanksDefault(0);
    doc = xmlParseFile("/home/fhh/桌面/strings.2.xml");
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
    //匹配到第一条-----------------
    printf("Now loading String data structure……\n");
    while(strcmp(reinterpret_cast<char*>(xmlNodeGetContent(cur->children)),"STR_LEVEL_ZEN_E1"))
        cur = cur->next;
    //---------------------------
    for(ulong i=0;i<lvl_zen_e.size();i++)
    {
        lvl_zen_e.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_classic.size()-2;i++)
    {
        lvl_classic.data()[i] = cur;
        cur = cur->next;
        if(i==4)
        {
            i++;
            lvl_classic.data()[5]=nullptr;//Fixed a bug caused by FTG
        }
    }
    for(ulong i=0;i<lvl_d.size();i++)
    {
        lvl_d.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_z.size();i++)
    {
        lvl_z.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_g.size();i++)
    {
        lvl_g.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_m.size();i++)
    {
        lvl_m.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_b.size();i++)
    {
        lvl_b.data()[i] = cur;
        cur = cur->next;
    }
    for(ulong i=0;i<lvl_candy.size();i++)
    {
        lvl_candy.data()[i] = cur;
        cur = cur->next;
    }
    //This is our Magic Code!
    int classindex[] = {21,12,11,2,22,0,27,29,37,13,15,32,28,16,38,3,25,33,39,26,36,9,19,20,23,14,8,7,30,10,34,1,31,18,17,35,24,6,4};
    //Then, we open the level xml
    xmlDocPtr doclvl;
    xmlNodePtr curlvl;
    xmlKeepBlanksDefault(0);
    doclvl = xmlParseFile("/home/fhh/桌面/levels_zen.txt");
    curlvl = xmlDocGetRootElement(doclvl);
    printf("Now loading level file......\n");
    if(curlvl == nullptr)
    {
        fprintf(stderr, "root error!\n");
        xmlFreeDoc(doc);
        return 0;
    }
    if(xmlStrcmp(curlvl->name, reinterpret_cast<const xmlChar*>("serialise")))
    {
        printf("end\n");
        return 0;
    }
    curlvl = curlvl->children;
    //After that, we switch to the first level
    while(curlvl->name[4]!='d')
    {
        curlvl = curlvl->next;
    }
    //Then Everything is OK
    //Now We are prepared to load split files.
    char name[32]={0};
    char id[32]={0};
    xmlNodePtr now=nullptr;
    int tmp,needReload,posi,reloadindex=0;
    for(int i=0;i<192;i++)
    {
        sprintf(path,"/home/fhh/桌面/tmp/%d.%d.%d.gmp",(i/16)+1,(i&12)/4+1,(i&3)+1);
        fp = fopen(path,"r");
        fscanf(fp,"[QuellGen level data file]\n");
        fscanf(fp,"Level ID:%s\n",id);
        //判断关卡类型
        switch(id[4])
        {
            case 'd':
            {
                tmp = atoi(((id))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf((id),"lvl_d%d\n",&posi);
                now = lvl_d[static_cast<ulong>(posi)-1];
                break;
            }
            case 'z':
            {
                tmp = atoi(((id))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf((id),"lvl_z%d\n",&posi);
                now = lvl_z[static_cast<ulong>(posi)-1];
                break;
            }
            case 'g':
            {
                tmp = atoi(((id))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf((id),"lvl_g%d\n",&posi);
                now = lvl_g[static_cast<ulong>(posi)-1];
                break;
            }
            case 'c':
            {
                tmp = (id[9]=='_');//select "candy"
                    if(!tmp)
                    {
                        needReload=1;
                        goto outswitch;
                    }
                sscanf((id),"lvl_candy_%d\n",&posi);
                now = lvl_candy[static_cast<ulong>(posi)-1];
                break;
            }
            case 'b':
            {
                tmp = atoi(((id))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf((id),"lvl_b%d\n",&posi);
                now = lvl_b[static_cast<ulong>(posi)-1];
                break;
            }
            case 'm':
            {
                tmp = atoi(((id))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf((id),"lvl_m%d\n",&posi);
                now = lvl_m[static_cast<ulong>(posi)-1];
                break;
            }
            case 'q':
            {
                sscanf((id),"lvl_qm_e%d\n",&posi);
                now = lvl_zen_e[static_cast<ulong>(posi)-1];
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
                if(id[4]=='c'&&id[5]=='r')
                {
                    now = lvl_zen_e[0];
                    break;
                }
                now = lvl_classic[static_cast<ulong>(classindex[reloadindex++])];
            }
        }
        //-------------------------------
        fscanf(fp,"Level name:%[^\n]",name);
        printf("%d.%d.%d:%s\n",(i/16)+1,(i&12)/4+1,(i&3)+1,name);
        xmlNodeSetContent(now->children->next->next,reinterpret_cast<unsigned char*>(name));
        fscanf(fp,"\n");
        fclose(fp);
    }
    xmlSaveFormatFile("/home/fhh/桌面/strings.3.xml",doc,1);
    xmlFreeDoc(doc);
    /*
    vector<char*> lvl_zen_e = vector<char*>();
    vector<char*> lvl_classic = vector<char*>();
    vector<char*> lvl_d = vector<char*>();
    vector<char*> lvl_z = vector<char*>();
    vector<char*> lvl_g = vector<char*>();
    vector<char*> lvl_m = vector<char*>();
    vector<char*> lvl_b = vector<char*>();
    vector<char*> lvl_candy = vector<char*>();
    vector<char*>* id;
    int posi=0;
    int classindex[] = {21,12,11,2,22,0,27,29,37,13,15,32,28,16,38,3,25,33,39,26,36,9,19,20,23,14,8,7,30,10,34,1,31,18,17,35,24,6,51,4,52,52};
    FILE *fp = nullptr;
    char name[32] = {0};
    int tmp,needReload;
    for(int i=0;i<=193;i++)
    {
        sprintf(path,filelocation,(i/16)+1,(i&12)/4+1,(i&3)+1);
        //printf("%s\n",path);
        //printf("%d\n",i);
        if((static_cast<void>(fp = fopen(path,"r+")),fp)==nullptr)
            return;
        fscanf(fp,"[QuellGen level data file]\n");
        fscanf(fp,"Level ID:%s\n",name);
        //判断关卡类型
        switch(name[4])
        {
            case 'd':
            {
                tmp = atoi((reinterpret_cast<const char*>(name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(name),"lvl_d%d\n",&posi);
                name = lvl_d.data()[posi-1];
                break;
            }
            case 'z':
            {
                tmp = atoi((reinterpret_cast<const char*>(name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(name),"lvl_z%d\n",&posi);
                name = lvl_z.data()[posi-1];
                break;
            }
            case 'g':
            {
                tmp = atoi((reinterpret_cast<const char*>(name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(name),"lvl_g%d\n",&posi);
                name = lvl_d.data()[posi-1];
                break;
            }
            case 'c':
            {
                tmp = (name[9]=='_');//select "candy"
                    if(!tmp)
                    {
                        needReload=1;
                        goto outswitch;
                    }
                sscanf(reinterpret_cast<const char*>(name),"lvl_candy_%d\n",&posi);
                name = lvl_candy.data()[posi-1];
                break;
            }
            case 'b':
            {
                tmp = atoi((reinterpret_cast<const char*>(name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(name),"lvl_b%d\n",&posi);
                name = lvl_b.data()[posi-1];
                break;
            }
            case 'm':
            {
                tmp = atoi((reinterpret_cast<const char*>(name))+5);
                if(!tmp)
                {
                    needReload=1;
                    goto outswitch;
                }
                sscanf(reinterpret_cast<const char*>(name),"lvl_m%d\n",&posi);
                name = lvl_m.data()[posi-1];
                break;
            }
            case 'q':
            {
                sscanf(reinterpret_cast<const char*>(name),"lvl_qm_e%d\n",&posi);
                name = lvl_zen_e.data()[posi-1];
                break;
            }
            default:
            {
                needReload=1;
            }
        }
        outswitch:;
    }*/
    return 0;
}

int main(void)
{
    saveinfo();
    return 0;
}
