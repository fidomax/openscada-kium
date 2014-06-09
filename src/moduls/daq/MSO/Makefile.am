EXTRA_DIST = *.h po/*

oscd_modul_LTLIBRARIES = daq_MSO.la
daq_MSO_la_LDFLAGS = -module -avoid-version -no-undefined
daq_MSO_la_SOURCES = moduls.cpp mso_daq.cpp mso_prt.cpp MezTT.cpp MezTC.cpp MezTU.cpp
daq_MSO_la_LIBTOOLFLAGS = --tag=disable-static

I18N_mod = $(oscd_modulpref)MSO
include ../../../../I18N.mk
