#undef UNICODE

#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

int main()
{
	printf("MySQL client version: %s\n", mysql_get_client_info());

	// 
	//	Open a connection
	//
	MYSQL *con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
	}

	if (mysql_real_connect(con, "localhost", "jeff", "jrfftypaep",
		"oubdb", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s %d\n", mysql_error(con), mysql_errno( con ) );
		mysql_close(con);
		exit(1);
	}

	//
	//	Insert some users 
	//
	if (mysql_query(con, "INSERT INTO user VALUES('jeff', 'jrfftypaep')") )
	{
		fprintf(stderr, "%s %d\n", mysql_error(con), mysql_errno(con));
		if (mysql_errno(con) != 1062)
		{
			mysql_close(con);
			exit(1);
		}
	}	
	
	if (mysql_query(con, "INSERT INTO user VALUES('sam', 'jrfftypaep')"))
	{
		fprintf(stderr, "%s %d\n", mysql_error(con), mysql_errno(con));
		if (mysql_errno(con) != 1062)
		{
			mysql_close(con);
			exit(1);
		}
	}

	//
	//	Query the db
	//
	if (mysql_query(con, "SELECT * FROM user"))
	{
		fprintf(stderr, "%s %d\n", mysql_error(con), mysql_errno(con));
		mysql_close(con);
		exit(1);
	}
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)
	{
		fprintf(stderr, "%s %d\n", mysql_error(con), mysql_errno(con));
		mysql_close(con);
		exit(1);
	}
	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);
	mysql_close(con);
	return 0;
}
