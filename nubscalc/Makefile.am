SUBDIRS =
sbin_PROGRAMS = 

AM_CPPFLAGS = \
   -g \
   -I$(top_srcdir)/nubscript 

nubscalc_CXXFLAGS = \
   -std=c++11 \
   -g 

nubscalc_SOURCES = \
   main.cc

AM_CXXFLAGS = ${nubscalc_CXXFLAGS}

nubscalc_LDADD = \
   -L../nubscript/.libs/ -lnubscript

sbin_PROGRAMS += \
   nubscalc 


