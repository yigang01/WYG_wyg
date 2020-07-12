#include"连接.h"
#include"断开连接.h"
#include<stdlib.h>
int main()
{
	system("color 70");
	int s;
	printf("************************************************************************************\n");
	printf("************************************************************************************\n");
	printf("*******************************企业人事管理操作软件!******************************\n");
	printf("************************************************************************************\n");
	printf("************************************************************************************\n");
	printf("1:管理员登录      ");
	printf("2:员工登录      ");
	printf("3:退出\n");
	int quit1 = 0;
	while (!quit1)
	{
		printf("请输入你的选择：");
		scanf("%d", &s);
		switch (s)
		{
		case 1://系统管理员登录系统模块
		{
			lianjie();
			printf("请输入登录账号：\n");
			scanf("%s", Account);
			printf("请输入登录密码：\n");
			scanf("%s", Password);
			SQLCHAR sql3[] = "use Enterprise_management_system";
			SQLCHAR sql4[] = "select * from admin";
			ret = SQLExecDirect(hstmt, sql3, SQL_NTS);
			ret = SQLExecDirect(hstmt, sql4, SQL_NTS);
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLCHAR str1[50], str2[50];
				SQLINTEGER len_str1, len_str2;
				while (SQLFetch(hstmt) != SQL_NO_DATA)
				{
					SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
					SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);

					for (int i = 0; i < 8; i++)
					{
						a[i] = str1[i];
					}
					for (int i = 0; i < 6; i++)
					{
						p[i] = str2[i];
					}
					if (strcmp(Account, a) == 0 && strcmp(Password, p) == 0 || strcmp(Account, a) == 0 && strcmp(Password, p) == 0)
					{
						printf("登录成功\n");
						int x;
						duankai();
						printf("1:查询员工信息   2:添加员工信息   3:修改员工信息  4:删除员工信息\n");
						printf("5:查询部门信息   6:添加部门信息   7:修改部门信息  8:删除部门信息\n");
						printf("9:查看部门员工平均工资   10:修改部门员工平均工资    11:退出\n");
						int quit = 0;
						while (!quit)
						{
							printf("请输入你的选择:");
							scanf("%d", &x);
							switch (x)
							{
								//查询员工信息
							case 1:
							{
								lianjie();
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[] = { "select * from staff" };
								ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50];
									SQLINTEGER len_str1, len_str2, len_str3, len_str4, len_str5;
									printf("你所查询的所有员工信息如下：\n");
									while (SQLFetch(hstmt) != SQL_NO_DATA)
									{
										SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
										SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);
										SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
										SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
										printf("%s\t%s\t%s\t%s\t\n", str1, str2, str3, str4);
									}
								}
							}
								duankai();
								break;
								//增加员工信息
							case 2:
							{
								lianjie();
								char w[] = { "'," };
								char b[] = { "'" };
								char i[] = { ")" };
								char cNo[50];
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "insert into staff(sNo,sName,sPhone,sAddress) values('" };
								printf("请输入员工编号：");
								scanf("%s", &cNo);
								strcat((char*)sql2, cNo);
								strcat((char*)sql2, w);
								char cName[50];
								printf("请输入员工姓名：");
								scanf("%s", &cName);
								strcat((char*)sql2, b);
								strcat((char*)sql2, cName);
								strcat((char*)sql2, w);
								char sPhone[50];
								printf("请输入员工电话：");
								scanf("%s", &sPhone);
								strcat((char*)sql2, b);
								strcat((char*)sql2, sPhone);
								strcat((char*)sql2, w);
								char sAddress[50];
								printf("请输入员工地址：");
								scanf("%s", &sAddress);
								strcat((char*)sql2, b);
								strcat((char*)sql2, sAddress);
								strcat((char*)sql2, b);
								strcat((char*)sql2, i);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("添加成功\n");
								}
								else {
									printf("添加失败\n");
								}
							}
								duankai();
								break;
								//修改员工信息
							case 3:
							{
								//先删除
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "delete from staff where sNo = '" };
								printf("请输入你想修改的员工编号：");
								scanf("%s", &sNo);
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								//再插入
								printf("请依次进行修改：\n");
								char w[] = { "'," };
								char b[] = { "'" };
								char i[] = { ")" };
								char cNo[50];
								SQLCHAR sql3[] = { "use Enterprise_management_system" };
								SQLCHAR sql4[1000] = { "insert into staff(sNo,sName,sPhone,sAddress) values('" };
								printf("请输入员工编号：");
								scanf("%s", &cNo);
								strcat((char*)sql4, cNo);
								strcat((char*)sql4, w);
								char cName[50];
								printf("请输入员工姓名：");
								scanf("%s", &cName);
								strcat((char*)sql4, b);
								strcat((char*)sql4, cName);
								strcat((char*)sql4, w);
								char sPhone[50];
								printf("请输入员工电话：");
								scanf("%s", &sPhone);
								strcat((char*)sql4, b);
								strcat((char*)sql4, sPhone);
								strcat((char*)sql4, w);
								char sAddress[50];
								printf("请输入员工地址：");
								scanf("%s", &sAddress);
								strcat((char*)sql4, b);
								strcat((char*)sql4, sAddress);
								strcat((char*)sql4, b);
								strcat((char*)sql4, i);
								ret = SQLExecDirect(hstmt, sql4, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("修改成功\n");
								}
								else {
									printf("修改失败\n");
								}

							}
								duankai();
								break;
								//删除员工信息
							case 4:
							{
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "delete from staff where sNo = '" };
								printf("请输入你想删除的员工编号：");
								scanf("%s", &sNo);
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("删除成功\n");
								}
								else {
									printf("删除失败\n");
								}
							}
								duankai();
								break;
								//查询部门
							case 5:
							{
								lianjie();
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[] = { "select * from department" };
								ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50];
									SQLINTEGER len_str1, len_str2, len_str3, len_str4, len_str5;
									printf("你所查询的所有部门信息如下：\n");
									printf("部门编号 部门信息\n");
									while (SQLFetch(hstmt) != SQL_NO_DATA)
									{
										SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
										SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);
										/*SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
										SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);*/
										printf("%s\t%s\t\n", str1, str2);
									}
								}
							}
								duankai();
								break;
								//添加部门信息
							case 6:
							{
								lianjie();
								char w[] = { "'," };
								char b[] = { "'" };
								char i[] = { ")" };
								char cNo[50];
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "insert into department(dNo,dName) values('" };
								printf("请输入部门编号：");
								scanf("%s", &cNo);
								strcat((char*)sql2, cNo);
								strcat((char*)sql2, w);
								char cName[50];
								printf("请输入员工姓名：");
								scanf("%s", &cName);
								strcat((char*)sql2, b);
								strcat((char*)sql2, cName);
								strcat((char*)sql2, b);
								strcat((char*)sql2, i);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("添加成功\n");
								}
								else {
									printf("添加失败\n");
								}
							}
								duankai();
								break;
								//修改部门信息
							case 7:
							{
								//先删除
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "delete from department where dNo = '" };
								printf("请输入你想修改的部门编号：");
								scanf("%s", &sNo);
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								//添加
								printf("请依次按照内容修改\n");
								lianjie();
								char w[] = { "'," };
								char b[] = { "'" };
								char i[] = { ")" };
								char cNo[50];
								SQLCHAR sql11[] = { "use Enterprise_management_system" };
								SQLCHAR sql21[1000] = { "insert into department(dNo,dName) values('" };
								printf("请输入部门编号：");
								scanf("%s", &cNo);
								strcat((char*)sql21, cNo);
								strcat((char*)sql21, w);
								char cName[50];
								printf("请输入部门姓名：");
								scanf("%s", &cName);
								strcat((char*)sql21, b);
								strcat((char*)sql21, cName);
								strcat((char*)sql21, b);
								strcat((char*)sql21, i);
								ret = SQLExecDirect(hstmt, sql21, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("修改成功\n");
								}
								else {
									printf("修改失败\n");
								}
							}
								duankai();
								break;
								//删除部门信息
							case 8:
							{
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "delete from department where dNo = '" };
								printf("请输入你想删除的部门编号：");
								scanf("%s", &sNo);
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("删除成功\n");
								}
								else {
									printf("删除失败\n");
								}
							}
								duankai();
								break;
								//查看部门平均工资
							case 9:
							{
								lianjie();
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[] = { "select * from d_money" };
								ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50];
									SQLINTEGER len_str1, len_str2, len_str3, len_str4, len_str5;
									printf("你所查询的所有部门工资信息如下：\n");
									printf("部门编号 部门工资\n");
									while (SQLFetch(hstmt) != SQL_NO_DATA)
									{
										SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
										SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);
										/*SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
										SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);*/
										printf("%s\t%s\t\n", str1, str2);
									}
								}
							}
								duankai();
								break;
							case 10:
							{
								//先删除
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[1000] = { "delete from d_money where dNo = '" };
								printf("请输入你想修改的部门编号：");
								scanf("%s", &sNo);
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								//添加
								printf("请依次按照内容修改\n");
								lianjie();
								char w[] = { "'," };
								char b[] = { "'" };
								char i[] = { ")" };
								char cNo[50];
								SQLCHAR sql12[] = { "use Enterprise_management_system" };
								SQLCHAR sql22[1000] = { "insert into department(dNo,dName) values('" };
								printf("请输入部门编号：");
								scanf("%s", &cNo);
								strcat((char*)sql22, cNo);
								strcat((char*)sql22, w);
								char cName[50];
								printf("请输入部门工资：");
								scanf("%s", &cName);
								strcat((char*)sql22, b);
								strcat((char*)sql22, cName);
								strcat((char*)sql22, b);
								strcat((char*)sql22, i);
								ret = SQLExecDirect(hstmt, sql22, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									printf("修改成功\n");
								}
								else {
									printf("修改失败\n");
								}
							}
								duankai();
								break;
							case 11:
							{
								quit = 1;
							}
								duankai();
								break;
							}
						}
					}

				}
			}
		}
			duankai();
			break;


			//员工登录
		case 2:
		{
			lianjie();
			printf("请输入登录账号：\n");
			scanf("%s", Account);
			printf("请输入登录密码：\n");
			scanf("%s", Password);
			SQLCHAR sql3[] = "use Enterprise_management_system";
			SQLCHAR sql4[] = "select * from admin";
			ret = SQLExecDirect(hstmt, sql3, SQL_NTS);
			ret = SQLExecDirect(hstmt, sql4, SQL_NTS);
			if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				SQLCHAR str1[50], str2[50];
				SQLINTEGER len_str1, len_str2;
				while (SQLFetch(hstmt) != SQL_NO_DATA)
				{
					SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
					SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);

					for (int i = 0; i < 8; i++)
					{
						a[i] = str1[i];
					}
					for (int i = 0; i < 6; i++)
					{
						p[i] = str2[i];
					}
					if (strcmp(Account, a) == 0 && strcmp(Password, p) == 0 || strcmp(Account, a) == 0 && strcmp(Password, p) == 0)
					{
						printf("登录成功\n");
						int x;
						duankai();
						printf("1:查询员工信息   2:查询部门工资  3:退出\n");
						int quit2 = 0;
						while (!quit2)
						{
							printf("请输入你的选择:");
							scanf("%d", &x);
							switch (x)
							{
							case 1:
							{
								//查询员工信息
								lianjie();
								char sNo[50];
								char a[] = { "'" };
								printf("请输入你想查询的员工编号：");
								scanf("%s", &sNo);
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[] = { "select * from staff where sNo = '" };
								strcat((char*)sql2, sNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50];
									SQLINTEGER len_str1, len_str2, len_str3, len_str4, len_str5;
									printf("你所查询的员工信息如下：\n");
									while (SQLFetch(hstmt) != SQL_NO_DATA)
									{
										SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
										SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);
										SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
										SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);
										printf("%s\t%s\t%s\t%s\t\n", str1, str2, str3, str4);
									}
								}
							}
								break;
							case 2:
							{
								//查询部门工资
								lianjie();
								char dNo[50];
								char a[] = { "'" };
								printf("请输入你想查询的部门编号：");
								scanf("%s", &dNo);
								SQLCHAR sql1[] = { "use Enterprise_management_system" };
								SQLCHAR sql2[] = { "select * from d_money where dNo = '" };
								strcat((char*)sql2, dNo);
								strcat((char*)sql2, a);
								ret = SQLExecDirect(hstmt, sql1, SQL_NTS);
								ret = SQLExecDirect(hstmt, sql2, SQL_NTS);
								if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
								{
									SQLCHAR str1[50], str2[50], str3[50], str4[50], str5[50];
									SQLINTEGER len_str1, len_str2, len_str3, len_str4, len_str5;
									printf("你所查询的员工信息如下：\n");
									while (SQLFetch(hstmt) != SQL_NO_DATA)
									{
										SQLGetData(hstmt, 1, SQL_C_CHAR, str1, 50, &len_str1);   //获取第一列数据
										SQLGetData(hstmt, 2, SQL_C_CHAR, str2, 50, &len_str2);
										/*SQLGetData(hstmt, 3, SQL_C_CHAR, str3, 50, &len_str3);
										SQLGetData(hstmt, 4, SQL_C_CHAR, str4, 50, &len_str4);*/
										printf("部门编号   部门员工平均工资\n");
										printf("%s\t%s\t\n", str1, str2);
									}
								}
							}
								break;
							case 3:
							{
								quit2 = 1;
							}
								break;
							}
						}
					}
				}
			}
		}
			//p
		case 3:
		{
			quit1 = 1;
		}
			duankai();
			break;

		}
		system("pause");
		return 0;
	}
}