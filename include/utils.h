#pragma once

#include <3ds.h>
#include <iostream>

unsigned long htonl(unsigned long v);
unsigned short htons(unsigned short v);
void sock_debuginit();
void sock_debugsendstr(char* mes);
void sock_debugwait();

using namespace std;

static inline void unicodeToChar(char* dst, u16* src, int max)
{
	if (!src || !dst)return;
	int n = 0;
	while (*src && n<max - 1) { *(dst++) = (*(src++)) & 0xFF; n++; }
	*dst = 0x00;
}

std::string insert_newlines(const std::string &in, const size_t every_n);

Result loadfile(char *file, int *size, char** buffer);
bool replace(std::string& str, const std::string& from, const std::string& to);