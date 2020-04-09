#ifndef _db_h
#define _db_h

#define DB_FILE "./.testing_devpkg/db" //"/usr/local/.devpkg/db"
#define DB_DIR	"./.testing_devpkg" //"/usr/local/.devpkg"


int DB_init();
int DB_list();
int DB_update(const char *url);
int DB_find(const char *url);

#endif
