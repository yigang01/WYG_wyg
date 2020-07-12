#pragma once
#include"连接.h"
void duankai() {
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);//释放连接句柄
	SQLFreeHandle(SQL_HANDLE_ENV, henv);//释放环境句柄
}