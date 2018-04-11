#include "DBX.h"
#include "DB.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

// From Jason, with 1 change
static char* Load_Read_Data(DAZZ_DB *db) {
  FILE  *bases  = (FILE*) db->bases;
  struct stat sbuf;
  char  *data;

  bases = fopen(Catenate(db->path,"","",".bps"),"r");
  if (bases == NULL) EXIT(1);
  stat(Catenate(db->path,"","",".bps"), &sbuf);
  data = (char *) malloc(sbuf.st_size);
  if (data == NULL) return NULL; // was EXIT(1), but we can proceed
  fread(data, sbuf.st_size, 1, bases);
  fclose(bases);
  return(data);
}

// Wrapper
int Open_DBX(char *path, DAZZ_DBX *dbx, bool preload) {
  dbx->data = NULL;
  int rc = Open_DB(path, &dbx->db);
  switch (rc) {
    case -1:
      return -1;
    case 0:
      break;
    case 1:
      assert(rc != 1);
      abort();
    default:
      assert(rc < -1 || rc > 1);
      abort();
  }
  if (preload) {
    dbx->data = Load_Read_Data(&dbx->db);
  }
  return 0;
}

// From Jason
static int Load_Read_From_RAM(DAZZ_DB *db, char *data, int i, char *read, int ascii) {
  int64      off;
  int        len, clen;
  DAZZ_READ *r = db->reads;

  if (i >= db->nreads) { EXIT(1); }

  off = r[i].boff;
  len = r[i].rlen;
  clen = COMPRESSED_LEN(len);
  if (clen > 0) { memcpy(read, data + off, clen); } //fread(read,clen,1,bases)
  Uncompress_Read(len, read);
  if (ascii == 1)
    { Lower_Read(read);
      read[-1] = '\0';
    }
  else if (ascii == 2)
    { Upper_Read(read);
      read[-1] = '\0';
    }
  else
    read[-1] = 4;
  return (0);
}

// Wrapper
int Load_ReadX(DAZZ_DBX *dbx, int i, char *read, int ascii) {
  if (dbx->data) {
    return Load_Read_From_RAM(&dbx->db, dbx->data, i, read, ascii);
  } else {
    return Load_Read(&dbx->db, i, read, ascii);
  }
}

// Wrapper
void Close_DBX(DAZZ_DBX *dbx) {
  Close_DB(&dbx->db);
  if (dbx->data) free(dbx->data);
}
