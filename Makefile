# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/wonderful/thirdparty/blocksds/core

# User config

NAME		:= sprites_basic
GAME_TITLE	:= Basic example
GAME_SUBTITLE	:= 2D graphics: Sprites

COMPDB := 1

# Source code paths
# -----------------

GFXDIRS		:= graphics


LIBS    := -lmm9 -lnds9
LIBDIRS		:= $(BLOCKSDS)/libs/maxmod
AUDIODIRS    :=  audio


include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile