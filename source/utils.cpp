#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <iostream>
#include <sstream>
#include <3ds.h>
#include "utils.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


const int commandPort=5000;

using namespace std;

int sock = 0;

unsigned long htonl(unsigned long v)
{
	u8* v2=(u8*)&v;
	return (v2[0]<<24)|(v2[1]<<16)|(v2[2]<<8)|(v2[3]);
}

unsigned short htons(unsigned short v)
{
	u8* v2=(u8*)&v;
	return (v2[0]<<8)|(v2[1]);
}


void sock_debuginit()
{
    SOC_Initialize((u32*)memalign(0x1000, 0x100000), 0x100000);

    int listenfd;
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(commandPort);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    sock = accept(listenfd, (struct sockaddr*)NULL, NULL);
    closesocket(listenfd);
}
void sock_debugsendstr(char* mes)
{
    send(sock, mes, strlen(mes), 0);
}
void sock_debugwait()
{
    char d[] = {0x01, 0x01};
    send(sock, d, 2, 0);
    while (d[0] != 'E' && d[1] != 'X')
		recv(sock, d, 0x2, 0); //just a wait
}

Result loadfile(char *file, int *size, char** buffer)
{
	FILE *fp;
	long lSize;

	fp = fopen(file, "rb");
	if (!fp) {
		perror(file);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	lSize = ftell(fp);
	rewind(fp);

	/* allocate memory for entire content */
	*buffer = (char*)calloc(1, lSize + 1);
	if (!*buffer){
		fclose(fp);
		fputs("memory alloc fails", stderr);
		return -1;
	}

	/* copy the file into the buffer */
	if (1 != fread(*buffer, lSize, 1, fp)) {
		fclose(fp);
		free(*buffer);
		fputs("entire read fails", stderr);
		return -1;
	}

	size = (int *)lSize;
	fclose(fp);
	return 0;
}

std::string insert_newlines(const std::string &in, const size_t every_n)
{
	std::string out;
	out.reserve(in.size() + in.size() / every_n);
	for (std::string::size_type i = 0; i < in.size(); i++) {
		out.push_back(in[i]);
		if (!((i + 1) % every_n)) {
			out.push_back('\n');
		}
	}
	return out;
}