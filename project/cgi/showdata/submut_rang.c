#include "../include/cgic.h"
#include "../include/pjct.h"
#include <string.h>
#include <stdlib.h>

char c_temp_up[40]={0};
char c_temp_low[40]={0};
char c_hum_up[40]={0};
char c_hum_low[40]={0};
char c_illu_up[40]={0};
char c_illu_low[40]={0};

int temp_up=0;
int temp_low=0;
int hum_up=0;
int hum_low=0;
int illu_up=0;
int illu_low=0;
void showmsg()
{
    
    
    printf("<html>\n");
    printf("<head><title>CGI Output</title></head>\n");
    printf("<body>\n");
    printf("<table border=\"1\">\n");
    printf("<tr><th>变量</th><th>原始值</th><th>转换后的值</th></tr>\n");
    printf("<tr><td>c_temp_up</td><td>%s</td><td>%d</td></tr>\n", c_temp_up, atoi(c_temp_up));
    printf("<tr><td>c_temp_low</td><td>%s</td><td>%d</td></tr>\n", c_temp_low, atoi(c_temp_low));
    printf("<tr><td>c_hum_up</td><td>%s</td><td>%d</td></tr>\n", c_hum_up, atoi(c_hum_up));
    printf("<tr><td>c_hum_low</td><td>%s</td><td>%d</td></tr>\n", c_hum_low, atoi(c_hum_low));
    printf("<tr><td>c_illu_up</td><td>%s</td><td>%d</td></tr>\n", c_illu_up, atoi(c_illu_up));
    printf("<tr><td>c_illu_low</td><td>%s</td><td>%d</td></tr>\n", c_illu_low, atoi(c_illu_low));
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");
}

int cgiMain(int argc, const char *argv[])
{
    cgiFormString("temp_up",c_temp_up,sizeof(c_temp_up));
    cgiFormString("temp_low",c_temp_low,sizeof(c_temp_low));
    cgiFormString("hum_up",c_hum_up,sizeof(c_hum_up));
    cgiFormString("hum_low",c_hum_low,sizeof(c_hum_low));
    cgiFormString("illu_up",c_illu_up,sizeof(c_illu_up));
    cgiFormString("illu_low",c_illu_low,sizeof(c_illu_low));
    printf("Content-Type:text/html;charset=utf-8\n\n"); // 告诉服务器返回的是 HTML 内容
    // showmsg();

    k_msgt k_m1={
        .hum[0]=atoi(c_hum_low),
        .hum[1]=atoi(c_hum_up),
        .tmp[0]=atoi(c_temp_low),
        .tmp[1]=atoi(c_temp_up),
        .light[0]=atoi(c_illu_low),
        .light[1]=atoi(c_hum_up),
    };
    r_msgt r_m1={0};
    big_msgt bigms={
        .k_m=k_m1,
        .r_m=r_m1,
        .ctl=0,
        .flg=0x1<<1,
    };

    

    return 0;
}