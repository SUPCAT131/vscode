
#include "../include/pjct.h"
#include <string.h>
#include <stdlib.h>     // atoi
#include <stdio.h>

#include <sys/ipc.h>
#include <sys/msg.h>    // 消息队列

int temp_up=0;
int temp_low=0;
int hum_up=0;
int hum_low=0;
int illu_up=0;
int illu_low=0;

// 测试接收 单 阈值数据 测试通过
void showmsg1(k_msgt *km)
{
    printf("--2 k_m.tmp[1] =%d\n", km->tmp[1] );
    printf("--2 k_m.tmp[0] =%d\n", km->tmp[0]);
    printf("--2 k_m.hum[1] =%d\n", km->hum[1] );
    printf("--2 k_m.hum[0] =%d\n", km->hum[0] );
    printf("--2 k_m.light[1] =%d\n", km->light[1]);
    printf("--2 k_m.light[0] =%d\n", km->light[0]);
}
void showmsg2(char* ctl)
{
    printf("ctl = %#x\n",*ctl);
    if(*ctl&(0x1<<0)) printf("LED1 ON\n");
        else printf("LED1 OFF\n");
    if(*ctl&(0x1<<1)) printf("LED2 ON\n");
        else printf("LED2 OFF\n");
    if(*ctl&0x1<<2) printf("LED3 ON\n");
        else printf("LED3 OFF\n");
    if(*ctl&0x1<<3) printf("FAN ON\n");
        else printf("FAN OFF\n");
    if(*ctl&0x1<<4) printf("马达 ON\n");
        else printf("马达 OFF\n");
}
void showerr(char *errmsg)
{
    printf("<html>\n");
    printf("<head><title>CGI Output</title></head>\n");
    printf("<body>\n");
    printf("<p>errmsg : %s</p>",errmsg);
    printf("</body>\n");
    printf("</html>\n");
}
// 阈值接收函数 测试通过
void recv_s_1(k_msgt* km,int msgqid)
{
    msg_t msg;
    msg.mtype=1;
    msgrcv(msgqid,&msg,MSGSIZE,msg.mtype,0);
    km->hum[0]=msg.data.int_v[0];
    km->hum[1]=msg.data.int_v[1];
    msgrcv(msgqid,&msg,MSGSIZE,msg.mtype,0);
    km->tmp[0]=msg.data.int_v[0];
    km->tmp[1]=msg.data.int_v[1];
    msgrcv(msgqid,&msg,MSGSIZE,msg.mtype,0);
    km->light[0]=msg.data.int_v[0];
    km->light[1]=msg.data.int_v[1];
}
void recv_d_2(int msgqid,char* ctl)
{
    msg_t msg;
    msg.mtype=2;
    msgrcv(msgqid,&msg,MSGSIZE,msg.mtype,0);
    printf("recv_d_2 ctl %d\n",msg.data.ctl);
    memcpy(ctl,&msg.data.ctl,sizeof(*ctl));
}
int main(int argc, const char *argv[])
{

    // printf("Content-Type:text/html;charset=utf-8\n\n"); // 告诉服务器返回的是 HTML 内容

    // 创建消息队列
    key_t key;
    int msgqid;
        // 1. 获取键值
    key=ftok("/www/home",'s');
    if(key==-1)
    {
        //showerr("get error key");
        printf("--err get error key\n");
        return 0;
    }
        // 2. 创建消息队列
    msgqid = msgget(key, IPC_CREAT | 0666);
    if(msgqid == -1)
    {
        //showerr("get msgget error");
        printf("--get msgget error\n");
        return 0;
    }
        // 3.消息队列接收消息 
    int ret;
    msg_t msg;
    // msg_t2 msg2;
    big_msgt bigms={0};
    k_msgt k_m={0};
    // msg1.mtype = 1;
    // msg2.mtype = 2;
    char ctl=0;
    while (1)
    {
        // memset(&k_m,0,sizeof(k_m));
        // recv_s_1(&k_m,msgqid);
        // showmsg1(&k_m);
        // if(msg.mtype == 1000) break;
        ctl = 0;
        recv_d_2(msgqid,&ctl);
        showmsg2(&ctl);
    }
    return 0;
}