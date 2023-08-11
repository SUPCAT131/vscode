#include "../include/cgic.h"
#include "../include/pjct.h"
#include <string.h>
#include <stdlib.h>     // atoi

#include <sys/ipc.h>
#include <sys/msg.h>    // 消息队列


char c_temp_up[40]={0};
char c_temp_low[40]={0};
char c_hum_up[40]={0};
char c_hum_low[40]={0};
char c_illu_up[40]={0};
char c_illu_low[40]={0};

void showmsg()
{
    // v1.0 --效果普通
    // printf("Content-Type:text/html;charset=utf-8\n\n");
    // printf("<html>\n");
    // printf("<head><title>CGI Output</title></head>\n");
    // printf("<body>\n");
    // printf("<table border=\"1\">\n");
    // printf("<tr><th>变量</th><th>原始值</th><th>转换后的值</th></tr>\n");
    // printf("<tr><td>c_temp_up</td><td>%s</td><td>%d</td></tr>\n", c_temp_up, atoi(c_temp_up));
    // printf("<tr><td>c_temp_low</td><td>%s</td><td>%d</td></tr>\n", c_temp_low, atoi(c_temp_low));
    // printf("<tr><td>c_hum_up</td><td>%s</td><td>%d</td></tr>\n", c_hum_up, atoi(c_hum_up));
    // printf("<tr><td>c_hum_low</td><td>%s</td><td>%d</td></tr>\n", c_hum_low, atoi(c_hum_low));
    // printf("<tr><td>c_illu_up</td><td>%s</td><td>%d</td></tr>\n", c_illu_up, atoi(c_illu_up));
    // printf("<tr><td>c_illu_low</td><td>%s</td><td>%d</td></tr>\n", c_illu_low, atoi(c_illu_low));
    // printf("</table>\n");
    // printf("</body>\n");
    // printf("</html>\n");

    // v2.0 --效果不好
    // printf("Content-type: text/html;charset=utf-8\n\n");
    // printf("<html>\n");
    // printf("<head>\n");
    // printf("<title>CGI Form Result</title>\n");
    // printf("<script type='text/javascript'>\n");
    // printf("function showPopup() {\n");
    // printf("    alert('处理结果：\\n温度上限：%s\\n温度下限：%s\\n湿度上限：%s\\n湿度下限：%s\\n光强上限：%s\\n光强下限：%s');\n", c_temp_up, c_temp_low, c_hum_up, c_hum_low, c_illu_up, c_illu_low);
    // printf("}\n");
    // printf("</script>\n");
    // printf("</head>\n");
    // printf("<body onload='showPopup()'>\n");
    // printf("<h1>表单数据已处理</h1>\n");
    // printf("</body>\n");
    // printf("</html>\n");

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
void send_s_1(int msgqid,k_msgt* km)
{
    msg_t msg;
    msg.mtype=1;
    msg.data.int_v[0]=km->hum[0];
    msg.data.int_v[1]=km->hum[1];
    msgsnd(msgqid,&msg,MSGSIZE,0);
    msg.data.int_v[0]=km->tmp[0];
    msg.data.int_v[1]=km->tmp[1];
    msgsnd(msgqid,&msg,MSGSIZE,0);
    msg.data.int_v[0]=km->light[0];
    msg.data.int_v[1]=km->light[1];
    msgsnd(msgqid,&msg,MSGSIZE,0);
}

int cgiMain(int argc, const char *argv[])
{
    cgiFormString("temp_up",c_temp_up,sizeof(c_temp_up));
    cgiFormString("temp_low",c_temp_low,sizeof(c_temp_low));
    cgiFormString("hum_up",c_hum_up,sizeof(c_hum_up));
    cgiFormString("hum_low",c_hum_low,sizeof(c_hum_low));
    cgiFormString("illu_up",c_illu_up,sizeof(c_illu_up));
    cgiFormString("illu_low",c_illu_low,sizeof(c_illu_low));
     // 告诉服务器返回的是 HTML 内容
    showmsg();

    k_msgt k_m1={
        .hum[0]=atoi(c_hum_low),
        .hum[1]=atoi(c_hum_up),
        .tmp[0]=atoi(c_temp_low),
        .tmp[1]=atoi(c_temp_up),
        .light[0]=atoi(c_illu_low),
        .light[1]=atoi(c_illu_up),
    };
    
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
    send_s_1(msgqid,&k_m1);
    
    return 0;
}