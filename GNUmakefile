THISDIR:=$(abspath $(dir $(realpath $(lastword ${MAKEFILE_LIST}))))
LIBDIRS?=${THISDIR}/../DAZZ_DB
CFLAGS+= -O3 -Wall -Wextra -fno-strict-aliasing -Wno-unused-result
CPPFLAGS+= -MMD -MP -I${THISDIR}/../DAZZ_DB
LDLIBS+= -ldazzdb -lm -lpthread
LDFLAGS+= $(patsubst %,-L%,${LIBDIRS})
MOST = daligner HPCdaligner HPCmapper LAsort LAmerge LAsplit LAcat LAshow LAcheck LA4Falcon DB2Falcon
ALL:=${MOST} daligner_p
vpath %.c ${THISDIR}
vpath %.a ${THISDIR}/../DAZZ_DB

all: ${ALL}
daligner: filter.o
daligner_p: filter_p.o
${ALL}: align.o

install:
	cp -f ${ALL} ${PREFIX}/bin
clean:
	rm -f ${ALL}
	rm -f ${DEPS}
	rm -fr *.dSYM *.o

.PHONY: clean all

SRCS:=$(notdir $(wildcard ${THISDIR}/*.c))
DEPS:=$(patsubst %.c,%.d,${SRCS})
-include ${DEPS}
