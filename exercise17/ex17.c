#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// define constants
#define		MAX_DATA 512
#define		MAX_ROWS 100


/*------------------------------------------------------------------------- 
 * declare structures                                                    *
-------------------------------------------------------------------------*/
// Addess
struct Address {

	int		id;
	int		set;
	char	name[MAX_DATA];
	char	email[MAX_DATA];

};

// Database
struct Database {

	struct	Address		rows[MAX_ROWS];

};

// file connection
struct Connection {

	FILE	*file;
	struct	Database	*db;

};


/*-------------------------------------------------------------------------
 * define functions                                                      *
-------------------------------------------------------------------------*/
// kill program if error
void die(const char *message)
{

	if		(errno) {
			perror(message);
	}		else {
			printf("ERROR: %s\n", message);
	}
	
	exit(1);
}

// print the struct variable id, name and email
void Address_print(struct Address *addr)
{

	printf("%d %s %s\n", addr -> id, addr -> name, addr -> email);

}

// connect to database and file
void Database_load(struct Connection *conn)
{

	int		rc	= fread(conn -> db, sizeof(struct Database), 1, conn -> file);
	if		(rc != 1)		die("failed to load database.");

}

// make a database connection
struct Connection *Database_open(const char *filename, char mode)
{

	struct	Connection	*conn		= malloc(sizeof(struct Connection));
	if		(!conn)			die("Memory error");

	conn	-> db					= malloc(sizeof(struct Database));
	if		(!conn->db)		die("Memory error");

	if		(mode == 'c'){
			conn -> file				= fopen(filename, "w");
	}		else {
			conn -> file				= fopen(filename, "r+");

		if	(conn->file){
			Database_load(conn);
		}
	}

	if		(!conn->file)	die("Failed to open the file");

	return conn;
}

// close the database file and free memory
void Database_close(struct Connection *conn)
{

	if	(conn){
		if	(conn->file)	fclose(conn->file);
		if	(conn->db)		free(conn->db);
		free(conn);
	}

}

// write to the database
void Database_write(struct Connection *conn)
{

	rewind	(conn->file);

	int		rc	= fwrite(conn -> db, sizeof(struct Database), 1, conn -> file);
	if		(rc != 1)		die("failed to write database.");

	rc		= fflush(conn->file);
	if		(rc == -1)		die("Cannot flush database.");

}

//create a database and initialize it
void Database_create(struct Connection *conn)
{

	int		i	=0;

	for		(i = 0; i < MAX_ROWS; i++){
	
		//make a prototype to initialize it
		struct Address addr = {.id = i, .set = 0};
		//then assign it
		conn->db->rows[i]	= addr;

	}

}

//set database entry values
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{

	struct Address *addr	= &conn->db->rows[id];
	if		(addr->set)		die("Already set, delete it first");

	addr->set				= 1;
	// Warning: bug, read the "how to break it" and fix this
	char *res				= strncpy(addr->name, name, MAX_DATA); //if the input string is larger than MAX_DATA, the copied string is not NULL '\0' terminated

	/* code to fix bug uncomment to run */
	// addr->name[MAX_DATA-1]	= '\0'; 

	// demonstrate the strncpy bug
	if		(!res)			die("Name cop failed");

	res						= strncpy(addr->email, email, MAX_DATA);
	if		(!res)			die("Email cop failed");

}

//get database entry values
void Database_get(struct Connection *conn, int id)
{

	struct Address *addr	= &conn->db->rows[id];
	
	if		(addr->set) {
		Address_print(addr);
	}		else {
		die("ID is not set");
	}

}

//delete database entry
void Database_delete(struct Connection *conn, int id)
{

	struct Address addr		= {.id = id, .set = 0};
	conn->db->rows[id]		= addr;

}

//print the list of database elements (entry values)
void Database_list(struct Connection *conn)
{

	int		i				= 0;
	struct	Database *db	= conn->db;

	for (i = 0; i < MAX_ROWS; i++) {
	
		struct Address *cur	= &db->rows[i];

		if	(cur->set) {
			Address_print(cur);
		}

	}

}


/*-----------------------------------------------------------------------
 * main                                                                *
-----------------------------------------------------------------------*/

int	main (int argc, char *argv[])			
{

	// input error checking
	if	(argc < 3)				die("Usage: ex17 <dbfile> <action> [action params]");

	char	*filename			= argv[1];
	char	action				= argv[2][0];
	struct	Connection *conn	= Database_open(filename, action);
	int		id					= 0;

	if	(argc > 3)				id	= atoi(argv[3]);
	if	(id >= MAX_ROWS)		die("There are not that many recods");

	switch(action) {
	
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;

		case 'g':
			if	(argc != 4)		die("Need an id to GET");

			Database_get(conn, id);
			break;

		case 's':
			if	(argc != 6)		die("Need id, name, email to SET");

			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if	(argc != 4)		die("Need an id to delete");

			Database_delete(conn, id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die("Invalid action! Only: c=create g=get s=set d=delete l=list");

	}

	Database_close(conn);

	return 0;

}
