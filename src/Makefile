###
# GreenPois0n Anthrax - src/Makefile
# Copyright (C) 2010 Chronic-Dev Team
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###
 
CC ?= clang
STRIP ?= strip
LDID ?=
ARCH ?=

LAUNCHD_TARGET = launchd
LAUNCHD_OBJECTS = launchd.o utils.o
LAUNCHD_CFLAGS ?= -std=c11 -Wall -Wextra -O2 -D_DEFAULT_SOURCE
LAUNCHD_LDFLAGS ?=

.PHONY: all clean

%.o: %.c
	$(CC) $(LAUNCHD_CFLAGS) -c $< -o $@

all: $(LAUNCHD_TARGET)

$(LAUNCHD_TARGET): $(LAUNCHD_OBJECTS)
ifneq ($(strip $(ARCH)),)
	$(CC) $(LAUNCHD_CFLAGS) -march=$(ARCH) -o $@ $(LAUNCHD_OBJECTS) $(LAUNCHD_LDFLAGS)
else
	$(CC) $(LAUNCHD_CFLAGS) -o $@ $(LAUNCHD_OBJECTS) $(LAUNCHD_LDFLAGS)
endif
	$(STRIP) $@
ifneq ($(strip $(LDID)),)
	$(LDID) -S $@
endif
	
clean:
	rm -rf *.o $(LAUNCHD_TARGET)
