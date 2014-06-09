EXTRA_DIST = *.h po/*

oscd_modul_LTLIBRARIES = daq_FT3.la
daq_FT3_la_LDFLAGS = -module -avoid-version -no-undefined
daq_FT3_la_SOURCES = mod_FT3.cpp FT3_prt.cpp BUC.cpp BVI.cpp BVTC.cpp BVT.cpp BIP.cpp PAUK.cpp BTU.cpp UTHET.cpp BTR.cpp BTE.cpp
daq_FT3_la_LIBTOOLFLAGS = --tag=disable-static

I18N_mod = $(oscd_modulpref)FT3
include ../../../../I18N.mk