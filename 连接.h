#pragma once
#include<stdio.h>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<string.h>
#pragma warning(disable:4996)
char Account[50], Password[50], a[50], p[50];
SQLRETURN   ret;
SQLHENV    henv;
SQLHDBC    hdbc;
SQLHSTMT  hstmt;
void lianjie()
{
	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//申请环境句柄
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);//申请数据库连接句柄

	ret = SQLConnect(hdbc, (SQLCHAR*)"test", SQL_NTS, (SQLCHAR*)"sa", SQL_NTS, (SQLCHAR*)"123456", SQL_NTS);
	/*data_test为配置的ODBC数据源名称*/
	if (!(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO))
	{
		printf("连接数据库失败!\n");
	}
	else {
		printf("连接数据库成功!\n");
	}                                      /*到这是用odbc连接到数据库，可以用到我们建立的study数据库里的数据了*/
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
}