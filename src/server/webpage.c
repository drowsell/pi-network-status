#include "webpage.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
 

   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      
   }
   
   printf("\n");
   return 0;
}

int update_webpage(const char* file_path) 
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("../database/connection.db", &db);
   
	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	
	// Create SQL statement
	sql = "SELECT * from Connection";

	// Execute SQL statement
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
	if( rc != SQLITE_OK ) 
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	else 
	{
		fprintf(stdout, "Operation done successfully\n");
	}

	sqlite3_close(db);
	
	return 0;
}

void retrieve_webpage(const char* file_path, char* buffer, int buffer_size) 
{
    	char http_header[30000] = "HTTP/1.1 200 OK\r\n\n";
    	char response_data[30000] = {'\0'};

	printf("%s\n", response_data);

    	// Grab HTML data
    	FILE *html_data;

	// Open file with HTML data
    	html_data = fopen(file_path, "r");
    	char line[1024];
    	while (fgets(line, sizeof(line), html_data))
    	{
        	strcat(response_data, line);
    	}

	// Insert HTTP header infront of data
	strcat(http_header, response_data);

	// Copy data to buffer
	strncpy(buffer, http_header, buffer_size);
}
