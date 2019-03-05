#include "exportaction.h"
#define MAX_PATH_LENGTH 128
using namespace std;
int saveinfo(void)
{
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
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_classic.size()-2;i++)
    {
        lvl_classic.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
        if(i==5)
        {
            i++;
            lvl_classic.data()[6]=nullptr;//Fixed a bug caused by FTG
        }
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_d.size();i++)
    {
        lvl_d.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_z.size();i++)
    {
        lvl_z.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_g.size();i++)
    {
        lvl_g.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_m.size();i++)
    {
        lvl_m.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_b.size();i++)
    {
        lvl_b.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    for(ulong i=0;i<lvl_candy.size();i++)
    {
        lvl_candy.data()[i] = cur;
        printf("%s\n",xmlNodeGetContent(cur));
        cur = cur->next;
    }
    printf("SUBROUTINE----------------------\n");
    //This is our Magic Code!
    int classindex[] = {21,12,11,2,22,0,27,29,37,13,15,32,28,16,38,3,25,33,39,26,36,9,19,20,23,14,8,7,30,10,34,1,31,18,17,35,24,6,4};
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
    char path[MAX_PATH_LENGTH]={0};
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
