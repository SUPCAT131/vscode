#include "cgic.h"
#include <string.h>

char name[20] = {0};
char password[10] = {0};

char id[] = "root";
char ps[] = "123456";

int cgiMain(int argc, const char *argv[])
{

	/*获取网页 form表单中 用户输入的用户名和密码*/
	cgiFormString("ID",name,sizeof(name));
	cgiFormString("PASSWORD",password,sizeof(password));

	/*与数据库中存储的用户信息进行比较*/
	/*通过比较结果返回给boa 服务器网页数据*/
	if(0==strcmp(id,name) && 0==strcmp(ps,password)){
		printf("Set-Cookie:username=%s;path=/;",name);
		printf("Content-Type:text/html;charset=utf-8\n\n");
		/*boa将标准输出 printf fprintf 通过cgiOut重定向到管道了*/
		printf("<html>");
		printf("<body>");
		printf("<center>");
		//printf("<h1>登陆成功</h1>");
		//printf("<a href=\"../Iot_select.html\" target=\"self\"><h1>登录成功 点击继续</h1></a>");
		printf("<script>window.location.href='/Iot_select.html'</script>");
		printf("</center>");
		printf("</body>");
		printf("</html>");

		return 0;
	}else{
		printf("<html>");
		printf("<body>");
		printf("<center>");
		printf("<a href=\"../index.html\" target=\"self\"><h1>登录失败 点击返回</h1></a>");
		printf("</center>");
		printf("</body>");
		printf("</html>");

		return -1;
	}	
}
