#ifndef DALIGNER_DBX_H
#define DALIGNER_DBX_H
/* Wrappers to extend DAZZ_DB.
 *
 * Note that none of the extra fields are ever stored on-disk.
 */
#include "DB.h"
#include <stdbool.h>

typedef struct {
	DAZZ_DB db;
/*
 * When "data" is non-null, it stores the entire DB
 * in memory, so we can avoid random-access disk operations.
 * But if null, then wrappers simply delegate.
 */
	char* data;
} DAZZ_DBX;

int Open_DBX(char *path, DAZZ_DBX *dbx, bool preload);
int  Load_ReadX(DAZZ_DBX *dbx, int i, char *read, int ascii);
//void Trim_DB(DAZZ_DBX *dbx);
void Close_DBX(DAZZ_DBX *dbx);

#endif
