#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>		/* for NF_ACCEPT */
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <net/if.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

#define BUF_LEN 128

int TCP_connection(char * server_ip)
{
    int s, n;
    struct sockaddr_in server_addr;
    //struct sockaddr_in server_addr : 서버의 소켓주소 구조체
    char _buf[BUF_LEN+1];



    if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {//소켓 생성과 동시에 소켓 생성 유효검사
        printf("can't create socket\n");
        exit(0);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    //서버의 소켓주소 구조체 server_addr을 NULL로 초기화

    server_addr.sin_family = AF_INET;
    //주소 체계를 AF_INET 로 선택
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    //32비트의 IP주소로 변환
    server_addr.sin_port = htons(0x0050);
    //daytime 서비스 포트 번호

    connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("connected\n");
    return s;
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("Usage: ./tcp_connection <server_ip> \n");
        return -1;
    }

    int s = TCP_connection(argv[1]);

    sleep(1000);

    return 0;
}
