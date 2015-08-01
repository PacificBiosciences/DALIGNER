We have removed DB and QV files, since there are identical in DAZZ_DB.

Now, this package will not build unless the DAZZ_DB directory is supplied.

    CPPFLAGS+= -Idazzdb-build-dir
    LDFLAGS+= -Ldazzdb-build-dir

For now, we use a relative path, `../DAZZ_DB`, assuming we are both submodules.
