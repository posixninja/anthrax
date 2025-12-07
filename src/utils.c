/**
  * GreenPois0n Anthrax - utils.c
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

#include <string.h>
#include "utils.h"
#include "syscalls.h"
#include "hfs_mount.h"

int console = 0;

int install(const char* src, const char* dst, int uid, int gid, int mode) {
	int ret = 0;

	ret = cp(src, dst);
	if (ret < 0) {
		return ret;
	}

	ret = chown(dst, uid, gid);
	if (ret < 0) {
		return ret;
	}

	ret = chmod(dst, mode);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

void _puts(const char* s) {
	while((*s) != '\0') {
		write(1, s, 1);
		s++;
	}
	sync();
}

void _putc(const char c) {
	char byte[2] = { 0, 0 };
	byte[0] = c;
	write(1, byte, 1);
}

void puti(unsigned int integer) {
	int i = 0;
	char nyble = 0;
	const char* digits = "0123456789abcdef";

	for(i = 7; i >= 0; i--) {
		nyble = (integer >> (4 * i)) & 0xF;
		putc(digits[(int)nyble]);
	}
}

int cp(const char *src, const char *dest) {
	ssize_t count = 0;
	char buf[0x800];
	struct stat status;

	while (stat(src, &status) != 0) {
		puts("Unable to find source file\n");
		return -1;
	}

	int in = open(src, O_RDONLY, 0);
	if (in < 0) {
		return -1;
	}

	int out = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0) {
		close(in);
		return -1;
	}

	do {
		count = read(in, buf, 0x800);
		if (count > 0) {
			count = write(out, buf, count);
		}
	} while (count > 0);

	close(in);
	close(out);

	if (count < 0) {
		return -1;
	}

	return 0;
}

int hfs_mount(const char* device, const char* mountdir, int options) {
	struct hfs_mount_args args;
	memset(&args, 0, sizeof(args));
	args.fspec = (char *)device;
#if defined(__APPLE__)
	return mount("hfs", mountdir, options, &args);
#else
	unsigned long linux_flags = 0;
#ifdef MS_RDONLY
	if (options & MNT_RDONLY) {
		linux_flags |= MS_RDONLY;
	}
#endif
#ifdef MS_REMOUNT
	if (options & MNT_UPDATE) {
		linux_flags |= MS_REMOUNT;
	}
#endif
	return mount(device, mountdir, "hfs", linux_flags, NULL);
#endif
}

int fsexec(const char* const argv[], char* const env[]) {
	if(vfork() != 0) {
		while(wait4(-1, NULL, WNOHANG, NULL) <= 0) {
			sleep(1);
		}
	} else {
		chdir("/mnt");
		if (chroot("/mnt") != 0) {
			return -1;
		}
		execve(argv[0], (char* const*)argv, env);
	}
	return 0;
}

int exec(const char* const argv[], char* const env[]) {
	if(vfork() != 0) {
		while(wait4(-1, NULL, WNOHANG, NULL) <= 0) {
			sleep(1);
		}
	} else {
		execve(argv[0], (char* const*)argv, env);
	}
	return 0;
}
