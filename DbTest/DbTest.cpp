// DbTest.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
//
int main()
{
	printf("MySQL client version: %s\n", mysql_get_client_info());
	return 0;
}

