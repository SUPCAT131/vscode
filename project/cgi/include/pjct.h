#ifndef __PJCT_H__
#define __PJCT_H__

typedef struct r_msgt  //用于读取信息的结构体
{
    char nomal; // 8bit [0:2] LED1 LED2 LED3 [3] FAN [4] 马达
    float hum;  // 湿度
    float tmp;  // 温度
    int light;  // 光强
}r_msgt;

typedef struct   //用于封装阈值信息的结构体
{
    int hum[2]; // [0] low 下限
    int tmp[2];
    int light[2];
}k_msgt;
            // 控制设备的字符串
char ctl;   // 8bit [0:2] LED1 LED2 LED3 [3] FAN [4] 马达

typedef struct  // 上述结构体封装为一个总结构体
{
    r_msgt r_m;
    k_msgt k_m;
    char ctl;   //8bit [0:2] LED1 LED2 LED3 [3] FAN [4] 马达
    char flg; //标志位 [0] r_m有内容 [1] k_m有内容 [2] 控制设备有内容 0000 0111 表示全有内容
}big_msgt;      

typedef struct
{
    long mtype;     //消息的类型，必须大于0
    int int_v[2];
}msg_t1;

#define MSGSIZE (sizeof(msg_t)-sizeof(long))

#endif