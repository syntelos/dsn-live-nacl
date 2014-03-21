

GETOS := python $(NACL_SDK_ROOT)/tools/getos.py

OSNAME := $(shell $(GETOS))

PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)

PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-clang++

PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize


WARNINGS := -Wno-long-long -Wall -Wswitch-enum -pedantic -Werror

DOPT := -g  #  -O2

CXXFLAGS := $(DOPT) -pthread -std=gnu++98 $(WARNINGS) -I$(NACL_SDK_ROOT)/include # -std=c++0x (headers errors)

LDFLAGS := -L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi_gles2 -lppapi_cpp -lppapi -lpthread

SOURCES := DSNL.cc Matrix.cc Font.cc FontFutural.cc


all: dsn-live-nacl.pexe  # (serve: all)

dsn-live-nacl.pexe: dsn-live-nacl.bc
	$(PNACL_FINALIZE) -o $@ $<

dsn-live-nacl.bc: $(SOURCES)
	$(PNACL_CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) dsn-live-nacl.pexe dsn-live-nacl.bc


HTTPD_PY := python $(NACL_SDK_ROOT)/tools/httpd.py

.PHONY: serve
serve: all
	$(HTTPD_PY) -C $(CURDIR) --no-dir-check
