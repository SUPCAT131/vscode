#include "../include/cgic.h"
#include "../include/pjct.h"
#include <string.h>

#include <sys/ipc.h>
#include <sys/msg.h>    // 消息队列

void showmsg()
{
    printf("Content-type: text/html;charset=utf-8\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<script type='text/javascript'>\n");
    printf("window.onload = function() {\n");
    printf("    setTimeout(function() {\n");
    printf("        closePage();\n"); // 调用关闭网页的函数
    printf("    }, 1000);  // 5000 毫秒后关闭页面（5 秒）\n");
    printf("};\n");
    printf("function closePage() {\n");
    printf("    window.close();\n");
    printf("}\n");
    printf("</script>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<h1>修改已成功提交</h1>\n");
    printf("</body>\n");
    printf("</html>\n");
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

void send_d_2(int msgqid,char* ctl)
{
    msg_t msg;
    msg.mtype=2;
    msg.data.ctl=*ctl;
    msgsnd(msgqid,&msg,MSGSIZE,0);
}
/* 
name 是页面中 input标签中的 name属性 
ctl 是开发文档中的 控制设备ed字符串
bit 是偏移位 以开发文档为主
*/
void set_ctl(char* ctl,int bit,char* name)
{
    char* check_box[]={"ON","OFF"};
    int user_check_result;
    if(cgiFormRadio(name,check_box,2,&user_check_result,0)==cgiFormSuccess) {
        if(user_check_result==0)
        *ctl |= 0x1<<bit;
        else if(user_check_result==1)
        *ctl &= ~(0x1<<bit);
    }
}
int cgiMain(int argc, const char *argv[])
{
    // printf("Content-type: text/html;charset=utf-8\n\n");
    
    char ctl=0;
    set_ctl(&ctl,0,"LED1");
    set_ctl(&ctl,1,"LED2");
    set_ctl(&ctl,2,"LED3");
    set_ctl(&ctl,3,"FAN");
    set_ctl(&ctl,4,"BEEP");
     // 告诉服务器返回的是 HTML 内容
    showmsg();
    
    // 创建消息队列
    key_t key;
    int msgqid;
        // 1. 获取键值
    key=ftok("/www/home",'s');
    if(key==-1)
    {
        showerr("get error key");
        return 0;
    }
        // 2. 创建消息队列
    msgqid = msgget(key, IPC_CREAT | 0666);
    if(msgqid == -1)
    {
        showerr("get msgget error");
        return 0;
    }
        // 3.向消息队列中发消息
    send_d_2(msgqid,&ctl);
    
    return 0;
}