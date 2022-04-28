#include "webpage.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
	char connection_data[1024] = {'\0'};

	strcat(connection_data, "[");

	for(int i = 0; i< argc; i++){
		//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		char tmp[1024] = {'\0'};
		sprintf(tmp, "\"%s\",", argv[i] ? argv[i] : "NULL");
		strcat(connection_data, tmp);
	}
   
	strcat(connection_data, "\"#ab0000\", \"#009933\"],\n");
	//printf("\"#ab0000\", \"#009933\"],\n");
	printf("%s\n", connection_data);

	FILE* f = fopen("connection.dat", "a");

	if(f == NULL) {
		printf("Error: Could not create file.");
		exit(-1);
	}

	fprintf(f, "%s", connection_data);
	fclose(f);
		
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
	
	char response_data[30000] = {'\0'};
	char line[1024] = {'\0'};
    	
	// Grab HTML data
    	FILE *html_data;
	
	// Open file with HTML data
    	html_data = fopen("template.html", "r");
    	while (fgets(line, sizeof(line), html_data))
    	{
        	strcat(response_data, line);

		char* check;
		check = strstr(line, "//INSERT//");
		if(check) 
		{
			printf("%s\n", line);
			break;
		}
    	}

	// Create SQL statement
	sql = "SELECT date, SUM(CASE WHEN status='UP' THEN 1 ELSE 0 END) NumUps, SUM(CASE WHEN status='DOWN' THEN 1 ELSE 0 END) NumDowns FROM Connection GROUP BY date";
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


	char query_data[30000] = {'\0'};
    	
    	FILE *connection_data;
	
    	connection_data = fopen("connection.dat", "r");
    	while (fgets(line, sizeof(line), connection_data))
    	{
        	strcat(query_data, line);
    	}
	
	strcat(response_data, query_data);

    	while (fgets(line, sizeof(line), html_data))
    	{
        	strcat(response_data, line);
    	}

	FILE* f = fopen("test.html", "w");

	if(f == NULL) {
		printf("Error: Could not create file.");
		exit(-1);
	}

	fprintf(f, "%s", response_data);
	fclose(f);

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
