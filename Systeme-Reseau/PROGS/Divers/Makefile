sources = $(wildcard *.c)

modules = demon.c
progs = $(filter-out $(modules),$(sources))

execs = $(progs:.c=)

include ../common.mk

