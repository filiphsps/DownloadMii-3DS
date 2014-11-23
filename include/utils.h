#pragma once

unsigned long htonl(unsigned long v);
unsigned short htons(unsigned short v);
void sock_debuginit();
void sock_debugsendstr(char* mes);
void sock_debugwait();
