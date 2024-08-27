#pragma once

#include<mysql.h>
#include<mysql_connection.h>
#include<msclr/marshal_cppstd.h>

using namespace System;

inline MYSQL* connecting(String^ name, String^ pass)
{
	msclr::interop::marshal_context converter;

	std::string Name = converter.marshal_as<std::string>(name);
	std::string Pass = converter.marshal_as<std::string>(pass);

	const char* host = "localhost";
	char* username = &Name[0];
	char* password = &Pass[0];
	char db[10] = "cms";
	unsigned int port = 3306;

	MYSQL* conn = mysql_init(0);

	try
	{
		conn = mysql_real_connect(conn, host, username, password, db, port, NULL, 0);
		return conn;
	}
	catch (const sql::SQLException&)
	{
		return conn;
	}
}

