SUBDIRS =
sbin_PROGRAMS = 

AM_CPPFLAGS = \
   -g \
   -I$(top_srcdir)/nubscript 

nubscli_CXXFLAGS = \
   -std=c++11 \
   -g 

nubscli_SOURCES = \
   nu_builtin_help.cc \
   nu_builtin_help.h \
   main.cc

AM_CXXFLAGS = ${nubscli_CXXFLAGS}

#nubscli_DEPENDENCIES=nubscript

nubscli_LDADD = \
   -L../nubscript/.libs/ -lnubscript

sbin_PROGRAMS += \
   nubscli 


