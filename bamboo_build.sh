#!/bin/bash -e
type module >& /dev/null || source /mnt/software/Modules/current/init/bash

module load gcc
module load git
module load meson
module load ninja
module load ccache

set -vex

export CCACHE_COMPILERCHECK='%compiler% -dumpversion'

case "${bamboo_planRepository_branchName}" in
  develop|master)
    module load dazzdb/${bamboo_planRepository_branchName}
    export PREFIX_ARG="/mnt/software/d/daligner/${bamboo_planRepository_branchName}"
    export BUILD_NUMBER="${bamboo_globalBuildNumber:-0}"
    ;;
  *)
    module load dazzdb/develop
    export PREFIX_ARG=/PREFIX
    export BUILD_NUMBER="0"
    ;;
esac

# rm -rf ./build
meson --buildtype=release --strip --libdir=lib --prefix="${PREFIX_ARG}" -Dtests=false --wrap-mode nofallback ./build .

TERM='dumb' ninja -C ./build -v

DESTDIR="$(pwd)/DESTDIR"
rm -rf "${DESTDIR}"
TERM='dumb' DESTDIR="${DESTDIR}" ninja -C ./build -v install

make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean
PATH="${DESTDIR}${PREFIX_ARG}/bin":${PATH} LD_LIBRARY_PATH="${DESTDIR}${PREFIX_ARG}/lib":${LD_LIBRARY_PATH} make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile
make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean

rm -rf "${DESTDIR}"

case "${bamboo_planRepository_branchName}" in
  develop|master)
    DESTDIR=
    TERM='dumb' DESTDIR="${DESTDIR}" ninja -C ./build -v install
    chmod -R a+rwx "${DESTDIR}${PREFIX_ARG}"/*
    module load daligner/${bamboo_planRepository_branchName}
    ldd -r $(which DBshow)
    ;;
esac
