#
GETOS := python $(NACL_SDK_ROOT)/tools/getos.py

OSNAME := $(shell $(GETOS))

PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)

PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-clang++

PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize

HOST_CXX := clang++

#
WARNINGS := -Wno-long-long -Wall -Wswitch-enum -pedantic -Werror

SHARED_CXXFLAGS := -pthread $(WARNINGS) -g  # -std=gnu++98 # -O2 # -std=c++0x (headers errors)

HOST_CXXFLAGS := $(SHARED_CXXFLAGS) -DDSNL_HOST

PNACL_CXXFLAGS := $(SHARED_CXXFLAGS) -DDSNL_NACL -I$(NACL_SDK_ROOT)/include

#
PNACL_LDFLAGS := -L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi_gles2 -lppapi_cpp -lppapi -lpthread

HOST_LDFLAGS := -lpthread

#
SHARED_SOURCES := Font.cc FontFutural.cc Fv3Color.cc Fv3Matrix.cc Fv3Vector.cc Fv3VertexArray.cc glh.cc

PNACL_SOURCES := DSNL.cc $(SHARED_SOURCES)

HOST_SOURCES := TEST.cc $(SHARED_SOURCES)



all: dsn-live-nacl.pexe  # (serve: all)

dsn-live-nacl.pexe: dsn-live-nacl.bc
	$(PNACL_FINALIZE) -o $@ $<

dsn-live-nacl.bc: $(PNACL_SOURCES)
	$(PNACL_CXX) $(PNACL_CXXFLAGS) -o $@ $^  $(PNACL_LDFLAGS)

test: $(HOST_SOURCES)
	$(HOST_CXX) $(HOST_CXXFLAGS) -o $@ $^  $(HOST_LDFLAGS)

clean:
	$(RM) dsn-live-nacl.pexe dsn-live-nacl.bc test


HTTPD_PY := python $(NACL_SDK_ROOT)/tools/httpd.py

.PHONY: serve
serve: all
	$(HTTPD_PY) -C $(CURDIR) --no-dir-check
