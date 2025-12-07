/**
  * GreenPois0n Anthrax - utils.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Justin Williams
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include "syscalls.h"

#define FLIPENDIAN(x) flipEndian((unsigned char *)(&(x)), sizeof(x))

#define puts _puts
#define putc _putc

extern int console;

static inline void flipEndian(unsigned char* x, int length) {
	int i;
	unsigned char tmp;

	for(i = 0; i < (length / 2); i++) {
		tmp = x[i];
		x[i] = x[length - i - 1];
		x[length - i - 1] = tmp;
	}
}

void _putc(const char c);
void _puts(const char* s);

void puti(unsigned int integer);
int exec(const char* const argv[], char* const env[]);
int fsexec(const char* const argv[], char* const env[]);
int cp(const char* src, const char* dest);
int hfs_mount(const char* device, const char* mountdir, int options);
int install(const char* src, const char* dst, int uid, int gid, int mode);

#endif
