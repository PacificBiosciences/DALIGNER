#ifndef DALIGNER_DBX_H
#define DALIGNER_DBX_H
/* Wrappers to extend HITS_DB.
 *
 * Note that none of the extra fields are ever stored on-disk.
 */
#include "DB.h"
#include <stdbool.h>

typedef struct {
	HITS_DB db;
/*
 * When "data" is non-null, it stores the entire DB
 * in memory, so we can avoid random-access disk operations.
 * But if null, then wrappers simply delegate.
 */
	char* data;
} HITS_DBX;

int Open_DBX(char *path, HITS_DBX *dbx, bool preload);
int  Load_ReadX(HITS_DBX *dbx, int i, char *read, int ascii);
//void Trim_DB(HITS_DBX *dbx);
void Close_DBX(HITS_DBX *dbx);

#endif
