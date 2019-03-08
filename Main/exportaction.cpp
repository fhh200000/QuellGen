#include <QCoreApplication>
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
    fp = fopen("/home/fhh/桌面/tmp/general.gmp","r");
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
    doc = xmlParseFile("/home/fhh/桌面/strings.xml");
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
    int bestsol=0;
    char* solution,*soludrop;
    int width=0,height=0,lspace=0,rspace=0,layercount;
    xmlNodePtr now=nullptr;
    int tmp,needReload,posi,reloadindex=0;
    for(int i=0;i<192;i++)
    {
        QString lvldata;
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
        fscanf(fp,"\n");
        printf("%d.%d.%d:%s\n",(i/16)+1,(i&12)/4+1,(i&3)+1,name);
        xmlNodeSetContent(now->children->next->next,reinterpret_cast<unsigned char*>(name));
        fscanf(fp,"Best solution:%d\n",&bestsol);
        solution = new char[bestsol*2+2];
        soludrop = new char[bestsol*2+2];
        fscanf(fp,"Solution:%[^\n]",solution);
        fscanf(fp,"\n");
        fscanf(fp,"Soludrop:%[^\n]",soludrop);
        fscanf(fp,"\n");
        fscanf(fp,"Width:%d\nHeight:%d\nLeft space:%d\nRight space:%d\n",&width,&height,&lspace,&rspace);
        //Getting levels
        fscanf(fp,"Layers:%d\n",&layercount);
        //Layer 0---------------------------
        char *lvlcurrow = new char[width*4];
        fscanf(fp,"Layer 0:\n");
        for(int l=0;l<height;l++)
        {
            //Add extra "1" to the front;
            for(int i=0;i<lspace;i++)
                lvldata.append("1 ");
            fscanf(fp,"%[^\n]",lvlcurrow);
            lvldata.append(lvlcurrow);
            fscanf(fp,"\n");
            for(int i=0;i<rspace;i++)
                //Add extra "1" to the back;
                lvldata.append("1 ");
        }
        //Layer 1---------------------------
        fscanf(fp,"Layer 1:\n");
        for(int l=0;l<height;l++)
        {
            //Add extra "0" to the front;
            for(int i=0;i<lspace;i++)
                lvldata.append("0 ");
            fscanf(fp,"%[^\n]",lvlcurrow);
            lvldata.append(lvlcurrow);
            fscanf(fp,"\n");
            for(int i=0;i<rspace;i++)
                //Add extra "0" to the back;
                lvldata.append("0 ");
        }
        //Layer 2(Optional)-----------------
        if(layercount-2)
        {
            fscanf(fp,"Layer 2:\n");
            for(int l=0;l<height;l++)
            {
                //Add extra "0" to the front;
                for(int i=0;i<lspace;i++)
                    lvldata.append("0 ");
                fscanf(fp,"%[^\n]",lvlcurrow);
                lvldata.append(lvlcurrow);
                fscanf(fp,"\n");
                for(int i=0;i<rspace;i++)
                    //Add extra "0" to the back;
                    lvldata.append("0 ");
            }
        }
        //------------------------------------
        xmlSetProp(curlvl,reinterpret_cast<const unsigned char*>("layout"),reinterpret_cast<unsigned char*>(lvldata.toLocal8Bit().data()));
        free(lvlcurrow);
        char layercounts[2];
        sprintf(layercounts,"%d",layercount);
        xmlSetProp(curlvl->children,reinterpret_cast<const unsigned char*>("layers"),reinterpret_cast<unsigned char*>(layercounts));
        //--------------
        xmlSetProp(curlvl->children,reinterpret_cast<const unsigned char*>("array_chars"),reinterpret_cast<unsigned char*>(solution));
        xmlSetProp(curlvl->children->next,reinterpret_cast<const unsigned char*>("array_chars"),reinterpret_cast<unsigned char*>(soludrop));
        delete(soludrop);
        delete(solution);
        curlvl = curlvl->next;
        fclose(fp);
    }
    xmlSaveFormatFile("/home/fhh/桌面/strings.3.xml",doc,1);
    xmlSaveFormatFile("/home/fhh/桌面/levels_zen.2.txt",doclvl,1);
    xmlFreeDoc(doc);
    return 0;
}

int main(void)
{
    saveinfo();
    return 0;
}
