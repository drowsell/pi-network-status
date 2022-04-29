#include "webpage.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
	char connection_data[1024] = {'\0'};

	strcat(connection_data, "\t\t\t[");

	for(int i = 0; i< argc; i++){
		char tmp[1024] = {'\0'};
		sprintf(tmp, "\"%s\",", argv[i] ? argv[i] : "NULL");
		strcat(connection_data, tmp);
	}
   
	strcat(connection_data, "\"#ab0000\", \"#009933\"],\n");
	printf("%s", connection_data);

	FILE* f = fopen("bin/network/connection.dat", "a");

	if(f == NULL) {
		printf("Error: Could not create file.");
		exit(-1);
	}

	fprintf(f, "%s", connection_data);
	fclose(f);
		
	return 0;
}

int update_webpage(const char* file_source, const char* file_destination) 
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";

	// Open database
	rc = sqlite3_open("bin/database/connection.db", &db);
   
	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	
	char response_data[30000] = {'\0'};
	char line[1024] = {'\0'};
    	
	// Grab HTML data
    	FILE *html_data;
	
	// Open file with HTML data
	// We wish to copy this template.html
    	html_data = fopen(file_source, "r");
    	while (fgets(line, sizeof(line), html_data))
    	{
        	strcat(response_data, line);
		
		// Check for INSERT keyword
		// We want to write after this line
		char* check;
		check = strstr(line, "//INSERT//");
		if(check) 
		{
			printf("Connection Data\n");
			break;
		}
    	}

	// Execute SQL statement
	sql = "SELECT date, SUM(CASE WHEN status='DOWN' THEN 1 ELSE 0 END) NumDowns, SUM(CASE WHEN status='UP' THEN 1 ELSE 0 END) NumUps  FROM Connection GROUP BY date";
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

	// Open file which contains data from SQL query
	// This will be formatted for our webpage 
	// It contains information how many times the network was UP/DOWN
	char query_data[30000] = {'\0'};
    	FILE *connection_data;
	
    	connection_data = fopen("bin/network/connection.dat", "r");
    	while (fgets(line, sizeof(line), connection_data))
    	{
        	strcat(query_data, line);
    	}
	
	strcat(response_data, query_data);

	// Continue writing our webpage from template.html
    	while (fgets(line, sizeof(line), html_data))
    	{
        	strcat(response_data, line);
    	}

	// Write the HTML page to a new index.html
	FILE* index = fopen(file_destination, "w");

	if(index == NULL) {
		printf("Error: Could not create file.");
		exit(-1);
	}

	fprintf(index, "%s", response_data);
	fclose(index);

	// Erase connection.dat
	FILE* connection_file = fopen("connection.dat", "w");

	if(connection_file == NULL) {
		printf("Error: Could not create file.");
		exit(-1);
	}

	fprintf(connection_file, "");
	fclose(connection_file);

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
