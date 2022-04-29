#include <sqlite3.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    sqlite3 *db;
    char *err_msg = 0;

    if (argc == 4) {
	    printf("%s %s %s\n", argv[1], argv[2], argv[3]);
    }
    else {
	    printf("ERROR: 3 arguments expected\n");
	    return -1;
    }
    
    int rc = sqlite3_open("connection.db", &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    
    // Creates a table
    char *sql0 = "CREATE TABLE IF NOT EXISTS Connection(date TEXT, time TEXT, status TEXT);"; 

    // Inserts Network Connection data into database
    char *sql1 = sqlite3_mprintf("INSERT INTO Connection VALUES('%q', '%q', '%q');", argv[1], argv[2], argv[3]);

    rc = sqlite3_exec(db, sql0, 0, 0, &err_msg);
    
    if (rc == SQLITE_OK) {
    	rc = sqlite3_exec(db, sql1, 0, 0, &err_msg);
    }

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}
