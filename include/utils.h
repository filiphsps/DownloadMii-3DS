#pragma once

#include <3ds.h>

unsigned long htonl(unsigned long v);
unsigned short htons(unsigned short v);
void sock_debuginit();
void sock_debugsendstr(char* mes);
void sock_debugwait();

static inline void unicodeToChar(char* dst, u16* src, int max)
{
	if (!src || !dst)return;
	int n = 0;
	while (*src && n<max - 1) { *(dst++) = (*(src++)) & 0xFF; n++; }
	*dst = 0x00;
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

Result loadfile(char *file, int *size, char** buffer);