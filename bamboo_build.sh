#!/bin/bash -ex
type module >& /dev/null || source /mnt/software/Modules/current/init/bash

set -vex
module load gcc/6.4.0
module load git/2.8.3
module load ccache
NEXUS_BASEURL=http://ossnexus.pacificbiosciences.com/repository
NEXUS_URL=$NEXUS_BASEURL/unsupported/gcc-6.4.0

rm -rf prebuilt build
mkdir -p prebuilt/DAZZ_DB build/bin
curl -s -L $NEXUS_URL/DAZZ_DB-SNAPSHOT.tgz|tar zxf - -C prebuilt/DAZZ_DB
mkdir -p DAZZ_DB
cp prebuilt/DAZZ_DB/lib/*.a DAZZ_DB/
cp prebuilt/DAZZ_DB/include/*.h DAZZ_DB/

make -C DALIGNER clean
make -C DALIGNER LIBDIRS=$PWD/prebuilt/DAZZ_DB/lib -j
make -C DALIGNER PREFIX=$PWD/build install

make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean
PATH=.:${PATH} make -C DALIGNER -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile
make -f /dept/secondary/siv/testdata/hgap/synth5k/LA4Falcon/makefile clean

if [[ $bamboo_planRepository_branchName == "develop" ]]; then
  cd build
  tar zcf DALIGNER-SNAPSHOT.tgz bin
  curl -v -n --upload-file DALIGNER-SNAPSHOT.tgz $NEXUS_URL/DALIGNER-SNAPSHOT.tgz
fi
