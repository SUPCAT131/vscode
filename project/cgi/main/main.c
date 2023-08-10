
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
// void showmsg()
// {
//     printf("<html>\n");
//     printf("<head><title>CGI Output</title></head>\n");
//     printf("<body>\n");
//     printf("<table border=\"1\">\n");
//     printf("<tr><th>变量</th><th>接收的值</th></tr>\n");
//     printf("<tr><td>c_temp_up</td><td>%d</td></tr>\n", temp_up );
//     printf("<tr><td>c_temp_low</td><td>%d</td></tr>\n", temp_low);
//     printf("<tr><td>c_hum_up</td><td>%d</td></tr>\n", hum_up );
//     printf("<tr><td>c_hum_low</td><td>%d</td></tr>\n", hum_low );
//     printf("<tr><td>c_illu_up</td><td>%d</td></tr>\n", illu_up);
//     printf("<tr><td>c_illu_low</td><td>%d</td></tr>\n", illu_low );
//     printf("</table>\n");
//     printf("</body>\n");
//     printf("</html>\n");
// }
void showmsg2()
{
    printf("c_temp_up =%d\n", temp_up );
    printf("c_temp_low =%d\n", temp_low);
    printf("c_hum_up =%d\n", hum_up );
    printf("c_hum_low =%d\n", hum_low );
    printf("c_illu_up =%d\n", illu_up);
    printf("c_illu_low =%d\n", illu_low );
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
    msg_t msg1;
    big_msgt bigms={0};
    msg1.mtype = 1;
    msg1.msg=&bigms;
    while (1)
    {
        msgrcv(msgqid,&msg1,sizeof(bigms),msg1.mtype,0);
        temp_up=bigms.k_m.tmp[1];
        temp_low=bigms.k_m.tmp[0];
        hum_up=bigms.k_m.hum[1];
        hum_low=bigms.k_m.hum[0];
        illu_up=bigms.k_m.light[1];
        illu_low=bigms.k_m.light[0];
        showmsg2();
        if(msg1.mtype == 1000) break;
    }
    return 0;
}