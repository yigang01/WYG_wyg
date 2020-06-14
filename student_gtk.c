/*************************************************************************
    > File Name: student_gtk.c
    > Author: maple
    > Mail: deadlysins.sx@gmail.com 
    > Created Time: 2015年04月12日 星期日 14时34分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include<string.h>
#include<sqlite3.h>
void callback_button(GtkWidget *btn,GtkWidget *entry[3]);
char *  str_str(char *A,char *B);
char *str_filled(char *str);
void callback_button1(GtkWidget *btn);
void callback_button2(GtkWidget *btn);
void callback_button3(GtkWidget *btn);
void callback_button4(GtkWidget *btn);

static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data);
void lookfor(GtkWidget *btn,GtkWidget *shuzu[7]);
void lookfor1(GtkWidget *btn,GtkWidget *shuzu[7]);
void lookfor2(GtkWidget *btn,GtkWidget *shuzu[7]);
void  lookfor3(GtkWidget *btn,int n);
void lookfor4(GtkWidget *btn,GtkWidget *shuzu[7]);
char *table[7]={"","","","","","",""};
int xuanzhong[6]={0,0,0,0,0,0};
GtkWidget *shuzu[7];
char *temp="";
GtkTextBuffer *buffer;
int main(int argc,char* argv[])
{ 
  GtkWidget *wnd;
  GtkWidget *label;
  GtkWidget *label1;
  GtkWidget *btn1;
  GtkWidget *fixed;
  GtkWidget *entry1;
  GtkWidget *entry2;
  GtkWidget *entry[3];

  gtk_init(&argc,&argv);
  wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title((GtkWindow*)wnd,"成绩管理系统登录");
  gtk_widget_set_usize(wnd,500,200);
  gtk_container_set_border_width(GTK_CONTAINER(wnd),15);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(wnd),fixed);

  label = gtk_label_new("用户");
  label1 = gtk_label_new("密码");
  btn1 = gtk_button_new_with_label("登录");
  entry1 = gtk_entry_new_with_max_length(20);
  entry2 = gtk_entry_new_with_max_length(20);
  gtk_fixed_put(GTK_FIXED(fixed),label,80,40);
  gtk_fixed_put(GTK_FIXED(fixed),label1,80,80);
  gtk_fixed_put(GTK_FIXED(fixed),btn1,265,120);
  gtk_fixed_put(GTK_FIXED(fixed),entry1,150,40);
  gtk_fixed_put(GTK_FIXED(fixed),entry2,150,80);
  gtk_entry_set_visibility(entry2,FALSE);
  entry[0] = entry1;
  entry[1] = entry2;
  entry[2] = wnd;
  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(callback_button),&entry);
  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
  gtk_widget_show_all(wnd);
  gtk_main();
  return 0;
}
//登录成功函数//////////////////////////////////////////////////
void callback_button(GtkWidget *btn,GtkWidget *entry[3])
{
  char *login = NULL;
  char *password = NULL;
  gboolean btn_state;
  login = gtk_entry_get_text((GtkEntry *)entry[0]);
  password = gtk_entry_get_text((GtkEntry *)entry[1]);
  if(strcmp(login,"cyp")==0&&strcmp(password,"123")==0)
  {
	  GtkWidget *wnd; 
	  GtkWidget *label;
	  GtkWidget *btn1;
	  GtkWidget *btn2;
	  GtkWidget *btn3;
	  GtkWidget *btn4;
	  GtkWidget *fixed;
	  wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title((GtkWindow*)wnd," 登录成功");
	 gtk_widget_set_usize(wnd,500,400);
	 gtk_container_set_border_width(GTK_CONTAINER(wnd),15);
  
	  fixed = gtk_fixed_new();
	  gtk_container_add(GTK_CONTAINER(wnd),fixed);
	
	  btn1 = gtk_button_new_with_label("查看个人信息");
	  btn2 = gtk_button_new_with_label("添加个人信息");
	  btn3 = gtk_button_new_with_label("修改个人信息");
	  btn4 = gtk_button_new_with_label("条件查询信息");
	  label = gtk_label_new("欢迎使用学生成绩查询系统");

	  gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
	  gtk_fixed_put(GTK_FIXED(fixed),btn1,60,100);
	  gtk_fixed_put(GTK_FIXED(fixed),btn2,300,100);
	  gtk_fixed_put(GTK_FIXED(fixed),btn3,60,200);
	  gtk_fixed_put(GTK_FIXED(fixed),btn4,300,200);
      release_resourse(entry[2],NULL,NULL);
	  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
	  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(callback_button1),NULL);  
	  g_signal_connect(G_OBJECT(btn2),"pressed",G_CALLBACK(callback_button2),NULL);  
	  g_signal_connect(G_OBJECT(btn3),"pressed",G_CALLBACK(callback_button3),NULL);  
	  g_signal_connect(G_OBJECT(btn4),"pressed",G_CALLBACK(callback_button4),NULL);  
	  gtk_widget_show_all(wnd);
	 gtk_main();
  }
  else
  {
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
	  gtk_widget_set_usize(dialog,300,100);
	  label = gtk_label_new("用户名或密码错误！请重新输入");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();
  }
}
////////////窗口关闭函数/////////////////////////////////
static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data)
{
	gtk_main_quit();
	return FALSE;
}
//////////个人信息查看////////////////////////////////////////
void callback_button1(GtkWidget *btn)
{
      GtkWidget *wnd; 
	  GtkWidget *label;
	  GtkWidget *label1;
	  GtkWidget *label2;
	  GtkWidget *label3;
	  GtkWidget *label4;
      GtkWidget *label5;
      GtkWidget *label6;
      char *label_table[6];
	  GtkWidget *btn1;
      GtkWidget *btn2;
	  GtkWidget *btn3;
	  GtkWidget *entry;
	  GtkWidget *fixed;
       GtkWidget *shuzu[8];
	 
 	 wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title((GtkWindow*)wnd,"个人信息查看");
	 gtk_widget_set_usize(wnd,400,600);
	 gtk_container_set_border_width(GTK_CONTAINER(wnd),15);

	  fixed = gtk_fixed_new();
	  gtk_container_add(GTK_CONTAINER(wnd),fixed);
	
      entry = gtk_entry_new_with_max_length(20);
	  btn1 = gtk_button_new_with_label("确定");
	 // btn2 = gtk_button_new_with_label("上一个");
	  //btn3 = gtk_button_new_with_label("下一个");
	  label = gtk_label_new("学号");
	  label1 = gtk_label_new("学号");
	  label2 = gtk_label_new("姓名");
	  label3 = gtk_label_new("性别");
	  label4 = gtk_label_new("语文");
	  label5 = gtk_label_new("数学");
	  label6 = gtk_label_new("外语");

	  gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
	  gtk_fixed_put(GTK_FIXED(fixed),btn1,300,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn2,40,340);
	  gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
	 // gtk_fixed_put(GTK_FIXED(fixed),btn3,300,340);
	  gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
	  gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
	  gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
	  gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
	  gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
	  gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
	 
	  shuzu[0]=entry;
	  shuzu[1]=label1;
	  shuzu[2]=label2;
	  shuzu[3]=label3;
	  shuzu[4]=label4;
	  shuzu[5]=label5;
	  shuzu[6]=label6;
	  shuzu[7]=wnd;
	  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(lookfor),&shuzu);
	  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
	  gtk_widget_show_all(wnd);
	 gtk_main();
}
//////////数据库个人信息查询函数/////////////////////////
 void  lookfor(GtkWidget *btn,GtkWidget *shuzu[8])
{
    int k;
    char *temp=NULL;
	sqlite3 *pdb = NULL;
	sqlite3_open("student_base",&pdb);
	char *sql = "select * from student where  id ='2012211564'";
	char *ErrMsg = 0;
	int result,i,j;
	char **dbResult=NULL;
	int nRow=0,nCloumn;
	GtkEntry *entry = (GtkEntry*)shuzu[0] ;
    const gchar *id = gtk_entry_get_text(entry);
	sql =str_str("select * from student where id ='",id);
	sql =str_str(sql,"'");
    printf("%s\n",sql);
	result = sqlite3_get_table(pdb,sql,&dbResult,&nRow,&nCloumn,&ErrMsg);

	if(nRow==0)
	{
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
	  gtk_widget_set_usize(dialog,200,200);
	  label = gtk_label_new("查询失败！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();
	}
	else
	{
		for(i = 0;i < nRow;i++)
		for(j = 0;j < nCloumn;j++)
		{
		 if(j==0)
               table[j]=str_str("学号： ",dbResult[(i+1)*nCloumn+j]);
		 if(j==1)
               table[j]=str_str("姓名： ",dbResult[(i+1)*nCloumn+j]); 
		 if(j==2)
               table[j]=str_str("性别： ",dbResult[(i+1)*nCloumn+j]);
		 if(j==3)
               table[j]=str_str("语文： ",dbResult[(i+1)*nCloumn+j]);
		 if(j==4)
               table[j]=str_str("数学： ",dbResult[(i+1)*nCloumn+j]);
		 if(j==5)
               table[j]=str_str("外语： ",dbResult[(i+1)*nCloumn+j]);
		}
	}
for (k=1;k<7;k++)
  gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
  gtk_widget_show_all(shuzu[7]);
  sqlite3_free_table(dbResult);
  sqlite3_close(pdb);
}
//////////字符测连接///////////////////////////////////////////////////////
char *str_str(char *A,char *B)
{

		int i = 0,j=0;
		int a=strlen(A);
		int b=strlen(B);
		char *ptr = NULL;
		ptr = malloc((a+b+1)*sizeof(char));
		while(A[i]!='\0')
		{

		ptr[i] = A[i];
		i++;
		}												
			
	   while(B[j]!='\0')
	   {

		 ptr[i]=B[j];
		 i++;j++;
	}
	ptr[i]='\0';
	return ptr;
}
////////////////////个人信息插入//////////////////////////////////////////

 void  lookfor1(GtkWidget *btn,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
	sqlite3 *pdb = NULL;
	sqlite3_open("student_base",&pdb);
	char *sql = "insert into student values('";
	char *ErrMsg = 0;
	int result,i,j;
	int sign = 1;
	char *szErrMsg;
	char **dbResult=NULL;
	GtkEntry *entry = (GtkEntry*)shuzu[1] ;
    const gchar *id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
		sign = 0;
	else
	{
	sql =str_str(sql,id);
	sql =str_str(sql,"','");
	}
	entry = (GtkEntry*)shuzu[2] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
		sign = 0;
	else
	{
	sql =str_str(sql,id);
	sql =str_str(sql,"','");
	}
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shuzu[3])))
	{
	sql =str_str(sql,"男");
	sql =str_str(sql,"',");
	}
	else
	{
	sql =str_str(sql,"女");
	sql =str_str(sql,"',");
	}
	entry = (GtkEntry*)shuzu[4] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = "0";
	sql =str_str(sql,id);
	sql =str_str(sql,",");
	entry = (GtkEntry*)shuzu[5] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = "0";
	sql =str_str(sql,id);
	sql =str_str(sql,",");
	entry = (GtkEntry*)shuzu[6] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = "0";
	sql =str_str(sql,id);
	sql =str_str(sql,")");
    //printf("%s\n",sql);
	if(sign==0)
	{
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
	  gtk_widget_set_usize(dialog,200,200);
	  label = gtk_label_new("基本信息不全，无法插入！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();
	}
	else
	{
    
	  sqlite3_exec(pdb,sql,0,0,&szErrMsg);
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
	  gtk_widget_set_usize(dialog,200,200);
	  label = gtk_label_new("插入成功！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();

	}
  sqlite3_free_table(dbResult);
  sqlite3_close(pdb);
}
/////////////// 插入个人信息！//////////////////////////////////////////////////////////////
void callback_button2(GtkWidget *btn)
{
      GtkWidget *wnd; 
	  GtkWidget *label1;
	  GtkWidget *label2;
	  GtkWidget *label3;
	  GtkWidget *label4;
      GtkWidget *label5;
      GtkWidget *label6;
	  GtkWidget *btn1;
	  GtkWidget *btn2;
	  GtkWidget *btn3;
      GtkWidget *box;
	  GtkWidget *entry1;
	  GtkWidget *entry2;
	  GtkWidget *entry3;
	  GtkWidget *entry4;
	  GtkWidget *entry5;
	  GtkWidget *entry6;
	  GtkWidget *fixed;
       GtkWidget *shuzu[7];
	 GSList *group;
 	 wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title((GtkWindow*)wnd,"添加个人信息");
	 gtk_widget_set_usize(wnd,400,600);
	 gtk_container_set_border_width(GTK_CONTAINER(wnd),15);

	  fixed = gtk_fixed_new();
	  gtk_container_add(GTK_CONTAINER(wnd),fixed);
	
	  box = gtk_hbox_new(TRUE,5);
//      entry = gtk_entry_new_with_max_length(20);
      entry1 = gtk_entry_new_with_max_length(20);
      entry2 = gtk_entry_new_with_max_length(20);
      entry3 = gtk_entry_new_with_max_length(20);
      entry4 = gtk_entry_new_with_max_length(20);
      entry5 = gtk_entry_new_with_max_length(20);
      entry6 = gtk_entry_new_with_max_length(20);
	  btn1 = gtk_button_new_with_label("确定");
//	  label = gtk_label_new("学号");
	  label1 = gtk_label_new("学号");
	  label2 = gtk_label_new("姓名");
	  label3 = gtk_label_new("性别");
	  label4 = gtk_label_new("语文");
	  label5 = gtk_label_new("数学");
	  label6 = gtk_label_new("外语");

	  //gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn1,300,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn2,40,340);
	  //gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
	  gtk_fixed_put(GTK_FIXED(fixed),btn1,240,340);
	  gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
	  gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
	  gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
	  gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
	  gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
	  gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
	  gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
	  gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
	  gtk_fixed_put(GTK_FIXED(fixed),box,120,180);
	  gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
	  gtk_fixed_put(GTK_FIXED(fixed),entry5,120,260);
	  gtk_fixed_put(GTK_FIXED(fixed),entry6,120,300);
	  btn2 = gtk_radio_button_new_with_label(NULL,"男");
	  gtk_box_pack_start(GTK_BOX(box),btn2,TRUE,TRUE,0);
      group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(btn2));
	  btn3 = gtk_radio_button_new_with_label(group,"女");
	  gtk_box_pack_start(GTK_BOX(box),btn3,TRUE,TRUE,0);

	  shuzu[0]=wnd;
	  shuzu[1]=entry1;
	  shuzu[2]=entry2;
	  shuzu[3]=btn2;
	  shuzu[4]=entry4;
	  shuzu[5]=entry5;
	  shuzu[6]=entry6;
	  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(lookfor1),&shuzu);
	  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
  	 gtk_widget_show_all(wnd);
	 gtk_main();
}
///////////////////修改个人信息/////////////////////////////////
void callback_button3(GtkWidget *btn)
{
      GtkWidget *wnd; 
	  GtkWidget *label1;
	  GtkWidget *label2;
	  GtkWidget *label3;
	  GtkWidget *label4;
      GtkWidget *label5;
      GtkWidget *label6;
	  GtkWidget *btn1;
	  GtkWidget *btn2;
	  GtkWidget *btn3;
	  GtkWidget *btn4;
      GtkWidget *box;
	  GtkWidget *entry1;
	  GtkWidget *entry2;
	  GtkWidget *entry3;
	  GtkWidget *entry4;
	  GtkWidget *entry5;
	  GtkWidget *entry6;
	  GtkWidget *fixed;
       GtkWidget *shuzu[7];
	 GSList *group;
 	 wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title((GtkWindow*)wnd,"按学号修改个人信息");
	 gtk_widget_set_usize(wnd,400,600);
	 gtk_container_set_border_width(GTK_CONTAINER(wnd),15);

	  fixed = gtk_fixed_new();
	  gtk_container_add(GTK_CONTAINER(wnd),fixed);
	
	  box = gtk_hbox_new(TRUE,5);
//      entry = gtk_entry_new_with_max_length(20);
      entry1 = gtk_entry_new_with_max_length(20);
      entry2 = gtk_entry_new_with_max_length(20);
      entry3 = gtk_entry_new_with_max_length(20);
      entry4 = gtk_entry_new_with_max_length(20);
      entry5 = gtk_entry_new_with_max_length(20);
      entry6 = gtk_entry_new_with_max_length(20);
	  btn1 = gtk_button_new_with_label("确定");
//	  label = gtk_label_new("学号");
	  label1 = gtk_label_new("学号");
	  label2 = gtk_label_new("姓名");
	  label3 = gtk_label_new("性别");
	  label4 = gtk_label_new("语文");
	  label5 = gtk_label_new("数学");
	  label6 = gtk_label_new("外语");

	  //gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn1,300,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn2,40,340);
	  //gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
	  gtk_fixed_put(GTK_FIXED(fixed),btn1,240,340);
	  gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
	  gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
	  gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
	  gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
	  gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
	  gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
	  gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
	  gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
	  gtk_fixed_put(GTK_FIXED(fixed),box,120,180);
	  gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
	  gtk_fixed_put(GTK_FIXED(fixed),entry5,120,260);
	  gtk_fixed_put(GTK_FIXED(fixed),entry6,120,300);
	  btn2 = gtk_radio_button_new_with_label(NULL,"默认");
	  gtk_box_pack_start(GTK_BOX(box),btn2,TRUE,TRUE,0);
      group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(btn2));
	  btn3 = gtk_radio_button_new_with_label(group,"男");
	  gtk_box_pack_start(GTK_BOX(box),btn3,TRUE,TRUE,0);
      group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(btn3));
	  btn4 = gtk_radio_button_new_with_label(group,"女");
	  gtk_box_pack_start(GTK_BOX(box),btn4,TRUE,TRUE,0);

	  shuzu[0]=btn3;
	  shuzu[1]=entry1;
	  shuzu[2]=entry2;
	  shuzu[3]=btn2;
	  shuzu[4]=entry4;
	  shuzu[5]=entry5;
	  shuzu[6]=entry6;
	  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(lookfor2),&shuzu);
	  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
  	 gtk_widget_show_all(wnd);
	 gtk_main();
}
/////////////////////////////////////////////////
//
 void  lookfor2(GtkWidget *btn,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
	sqlite3 *pdb = NULL;
	sqlite3_open("student_base",&pdb);
	char *sql = "insert into student values('";
	char *ErrMsg = 0;
	int result,i,j;
	int sign = 1;
	char *szErrMsg;
	char **dbResult=NULL;
	
	char *sql1 = "select * from student where  id ='2012211564'";
	char *ErrMsg1 = 0;
	int nRow=0,nCloumn;
	GtkEntry *entry = (GtkEntry*)shuzu[1] ;
    const gchar *id = gtk_entry_get_text(entry);
    const gchar *id1 = gtk_entry_get_text(entry);
	sql1 =str_str("select * from student where id ='",id1);
	sql1 =str_str(sql1,"'");
  //  printf("%s\n",sql1);
	sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
	 //temp1=str_filled(dbResult[(i+1)*nCloumn+j]);
	
//	GtkEntry *entry = (GtkEntry*)shuzu[1] ;
 //   const gchar *id = gtk_entry_get_text(entry);
 //   const gchar *id1 = gtk_entry_get_text(entry);i
 //
 if(nRow==1)
 {

	if(strlen(id)==0)
		sign = 0;
	else
	{
	sql =str_str(sql,id);
	sql =str_str(sql,"','");
	}
	entry = (GtkEntry*)shuzu[2] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	//	sign = 0;
	{
	sql =str_str(sql,dbResult[nCloumn+1]);
	sql =str_str(sql,"','");
	}
	else
	{
	sql =str_str(sql,id);
	sql =str_str(sql,"','");
	}
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shuzu[3])))
	{
	sql =str_str(sql,dbResult[nCloumn+2]);
	sql =str_str(sql,"',");
	}
	else if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shuzu[0])))
	{
	sql =str_str(sql,"男");
	sql =str_str(sql,"',");
	}
	else
	{
	sql =str_str(sql,"女");
	sql =str_str(sql,"',");
	}

	entry = (GtkEntry*)shuzu[4] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = dbResult[nCloumn+3];
	sql =str_str(sql,id);
	sql =str_str(sql,",");
	entry = (GtkEntry*)shuzu[5] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = dbResult[nCloumn+4];
	sql =str_str(sql,id);
	sql =str_str(sql,",");
	entry = (GtkEntry*)shuzu[6] ;
    id = gtk_entry_get_text(entry);
	if(strlen(id)==0)
	id = dbResult[nCloumn+5];
	sql =str_str(sql,id);
	sql =str_str(sql,")");
//    printf("%s\n",sql);
    //printf("nRow = %s\nsign=%s\n",nRow,sign);
 }
	//char *sql1 = "select * from student where  id ='2012211564'";
	//char *ErrMsg1 = 0;
//	int nRow=0,nCloumn;
//	sql1 =str_str("select * from student where id ='",id1);
//	sql1 =str_str(sql1,"'");
  //  printf("%s\n",sql1);
	
  //sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
//printf("nRow = %s\nsign=%s\n",nRow,sign);
	if(nRow==0|sign==0)
	{
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog)," 操作提示");
	  gtk_widget_set_usize(dialog,200,200);
	  label = gtk_label_new("无法修改！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();
	}
	else
	{
      sql1="delete from student where id = '";
	  sql1=str_str(sql1,id1);
	  sql1=str_str(sql1,"'");
	  sqlite3_exec(pdb,sql1,0,0,&szErrMsg);
	  sqlite3_exec(pdb,sql,0,0,&szErrMsg);
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
	  gtk_widget_set_usize(dialog,200,200);
	  label = gtk_label_new("修改成功！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();

	}
  sqlite3_free_table(dbResult);
  sqlite3_close(pdb);
}
/////////////// 按条件查询！//////////////////////////////////////////////////////////////
void callback_button4(GtkWidget *btn)
{
      GtkWidget *wnd; 
	  GtkWidget *label1;
	  GtkWidget *label11;
	  GtkWidget *label2;
	  GtkWidget *label3;
	  GtkWidget *label4;
      GtkWidget *label5;
      GtkWidget *label6;
	  GtkWidget *label44;
      GtkWidget *label55;
      GtkWidget *label66;
	  GtkWidget *btn1;
	  GtkWidget *btn2;
	  GtkWidget *btn3;
	  GtkWidget *btn4;
	  GtkWidget *btn11;
	  GtkWidget *btn22;
	  GtkWidget *btn33;
	  GtkWidget *btn44;
	  GtkWidget *btn55;
	  GtkWidget *btn66;
      GtkWidget *box;
      GtkWidget *box1;
      GtkWidget *box2;
	  GtkWidget *entry1;
	  GtkWidget *entry2;
	  GtkWidget *entry3;
	  GtkWidget *entry4;
	  GtkWidget *entry5;
	  GtkWidget *entry6;
	  GtkWidget *fixed;
	  GtkWidget *entry44;
	  GtkWidget *entry55;
	  GtkWidget *entry66;
	  GtkWidget *scrolled;
	  GtkWidget *text;
	  //GtkTextBuffer *buffer;
	  GtkWidget *shuzu[9];
	 GSList *group;
	 xuanzhong[0]=0;
	 xuanzhong[1]=0;
	 xuanzhong[2]=0;
	 xuanzhong[3]=0;
	 xuanzhong[4]=0;
	 xuanzhong[5]=0;
      char *strx="cyp";
      char *strx1="lj";
 	 wnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title((GtkWindow*)wnd,"按条件查询个人信息");
	 gtk_widget_set_usize(wnd,1000,700);
	 gtk_container_set_border_width(GTK_CONTAINER(wnd),15);

	  fixed = gtk_fixed_new();
	  gtk_container_add(GTK_CONTAINER(wnd),fixed);
	
	  box = gtk_hbox_new(TRUE,5);
	  box1 = gtk_hbox_new(TRUE,15);
	  box2 = gtk_hbox_new(TRUE,6);
      gtk_widget_set_size_request(box2,420,160);
//      entry = gtk_entry_new_with_max_length(20);
      entry1 = gtk_entry_new_with_max_length(20);
      entry2 = gtk_entry_new_with_max_length(20);
      entry3 = gtk_entry_new_with_max_length(20);
      entry4 = gtk_entry_new_with_max_length(20);
      entry5 = gtk_entry_new_with_max_length(20);
      entry6 = gtk_entry_new_with_max_length(20);
      gtk_widget_set_size_request(entry4,60,25);
      gtk_widget_set_size_request(entry5,60,25);
      gtk_widget_set_size_request(entry6,60,25);
      entry44 = gtk_entry_new_with_max_length(20);
      entry55 = gtk_entry_new_with_max_length(20);
      entry66 = gtk_entry_new_with_max_length(20);
      gtk_widget_set_size_request(entry44,60,25);
      gtk_widget_set_size_request(entry55,60,25);
      gtk_widget_set_size_request(entry66,60,25);
	  btn1 = gtk_button_new_with_label("开始匹配");
//	  label = gtk_label_new("学号");
	  label1 = gtk_label_new("条件匹配");
	  label11 = gtk_label_new("显示选项");
	  label2 = gtk_label_new("姓名");
	  label3 = gtk_label_new("性别");
	  label4 = gtk_label_new("语文");
	  label5 = gtk_label_new("数学");
	  label6 = gtk_label_new("外语");
	  label44 = gtk_label_new("到");
	  label55 = gtk_label_new("到");
	  label66 = gtk_label_new("到");
      
	  scrolled = gtk_scrolled_window_new(NULL,NULL);
      gtk_widget_show(scrolled);
      text = gtk_text_view_new();
	  //strx=str_filled(strx);
	  //strx=str_str(strx,"\n");
	 // strx1=str_filled(strx1);
	  strx1="";
	  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
	  gtk_text_buffer_set_text(buffer,strx1,-1);
	  //gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"Hello World!",-1);
	  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled),text);
	  //frame = gtk_frame_new("dut");
      //gtk_frame_set_label_align(GTK_FRAME(frame),0.5,0);
	 // gtk_fixed_put(GTK_FIXED(fixed),frame,300,100);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn1,300,40);
	  //gtk_fixed_put(GTK_FIXED(fixed),btn2,40,340);
	  //gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
	  gtk_fixed_put(GTK_FIXED(fixed),btn1,230,350);
	  gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
	  gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
	  gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
	  gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
	  gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
	  gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);	
	  gtk_fixed_put(GTK_FIXED(fixed),label44,200,220);
	  gtk_fixed_put(GTK_FIXED(fixed),label55,200,260);
	  gtk_fixed_put(GTK_FIXED(fixed),label66,200,300);		
	  gtk_fixed_put(GTK_FIXED(fixed),label11,360,100);
	  //gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
	  gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
	  gtk_fixed_put(GTK_FIXED(fixed),box,120,180);
	  gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
	  gtk_fixed_put(GTK_FIXED(fixed),entry5,120,260);
	  gtk_fixed_put(GTK_FIXED(fixed),entry6,120,300);
	  gtk_fixed_put(GTK_FIXED(fixed),entry44,250,220);
	  gtk_fixed_put(GTK_FIXED(fixed),entry55,250,260);
	  gtk_fixed_put(GTK_FIXED(fixed),entry66,250,300);
  	  gtk_fixed_put(GTK_FIXED(fixed),box1,360,140);
  	  gtk_fixed_put(GTK_FIXED(fixed),box2,360,160);
	  gtk_box_pack_start(GTK_BOX(box2),scrolled,TRUE,TRUE,0);
	  btn2 = gtk_radio_button_new_with_label(NULL,"男");
	  gtk_box_pack_start(GTK_BOX(box),btn2,TRUE,TRUE,0);
      group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(btn2));
	  btn3 = gtk_radio_button_new_with_label(group,"女");
	  gtk_box_pack_start(GTK_BOX(box),btn3,TRUE,TRUE,0);
      group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(btn3));
	  btn4 = gtk_radio_button_new_with_label(group,"男女");
	  gtk_box_pack_start(GTK_BOX(box),btn4,TRUE,TRUE,0);
 

	  btn11 = gtk_check_button_new_with_label("学号");
	  gtk_container_add(GTK_CONTAINER(box1),btn11);
	  btn22 = gtk_check_button_new_with_label("姓名");
	  gtk_container_add(GTK_CONTAINER(box1),btn22);
	  btn33 = gtk_check_button_new_with_label("性别");
	  gtk_container_add(GTK_CONTAINER(box1),btn33);
	  btn44 = gtk_check_button_new_with_label("语文");
	  gtk_container_add(GTK_CONTAINER(box1),btn44);
	  btn55 = gtk_check_button_new_with_label("数学");
	  gtk_container_add(GTK_CONTAINER(box1),btn55);
	  btn66 = gtk_check_button_new_with_label("外语");
	  gtk_container_add(GTK_CONTAINER(box1),btn66);
    

	  shuzu[0]=entry4;
	  shuzu[1]=entry5;
	  shuzu[2]=entry6;
	  shuzu[3]=entry44;
	  shuzu[4]=entry55;
	  shuzu[5]=entry66;
	  shuzu[6]=entry2;
	  shuzu[7]=btn2;
      shuzu[8]=btn3;
	  //g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(lookfor2),&shuzu);
	  g_signal_connect(G_OBJECT(wnd),"delete_event",G_CALLBACK(release_resourse),NULL);
	  g_signal_connect(G_OBJECT(btn11),"pressed",G_CALLBACK(lookfor3),0);
	  g_signal_connect(G_OBJECT(btn22),"pressed",G_CALLBACK(lookfor3),1);
	  g_signal_connect(G_OBJECT(btn33),"pressed",G_CALLBACK(lookfor3),2);
	  g_signal_connect(G_OBJECT(btn44),"pressed",G_CALLBACK(lookfor3),3);
	  g_signal_connect(G_OBJECT(btn55),"pressed",G_CALLBACK(lookfor3),4);
	  g_signal_connect(G_OBJECT(btn66),"pressed",G_CALLBACK(lookfor3),5);
	  g_signal_connect(G_OBJECT(btn1),"pressed",G_CALLBACK(lookfor4),&shuzu);
  	 gtk_widget_show_all(wnd);
	 gtk_main();
}
/////////////////////////////////////////////////////
char*str_filled(char *str1)
 {
	 int n = strlen(str1);
	 int i=0;
	 char *ptr=malloc(10*sizeof(char));
	 while(i<10&&i<n)
	 {
		 ptr[i]=str1[i];
		 i++;
	 }
	 while(i<20)
	 {
		 ptr[i]=' ';
		 i++;
	 }
	 ptr[i]='\0';
	 return ptr;
 }
///////////////////////////////////////////////////////////////////////////////////
	
 void  lookfor3(GtkWidget *btn,int n)
{
    xuanzhong[n]=xuanzhong[n]+1;
	xuanzhong[n]=xuanzhong[n]%2;
}
//////////////////////////////////////////////////////////////////////////////////
 void  lookfor4(GtkWidget *btn,GtkWidget *shuzu[8])
{
    int k;
    //char *temp=" ";
    char *temp1=NULL;
	sqlite3 *pdb = NULL;
	sqlite3_open("student_base",&pdb);
	char *sql =NULL;
	char *ErrMsg = 0;
	int result,i,j;
	char **dbResult=NULL;
	int nRow=0,nCloumn,sex_sign=0,name_sign=0;
	int fanwei[3][2];
	char *ptr[7];
	GtkEntry *entry = (GtkEntry*)shuzu[0] ;
    const gchar *shu = gtk_entry_get_text(entry);
    fanwei[0][0] = atoi(shu);
	ptr[0]=shu;
	if(strlen(shu)==0)
		ptr[0]="0";
	entry = (GtkEntry*)shuzu[1] ;
    shu = gtk_entry_get_text(entry);
    fanwei[1][0] = atoi(shu);
	ptr[1]=shu;
	if(strlen(shu)==0)
		ptr[1]="0";
	entry = (GtkEntry*)shuzu[2] ;
    shu = gtk_entry_get_text(entry);
    fanwei[2][0] = atoi(shu);
	ptr[2]=shu;
	if(strlen(shu)==0)
		ptr[2]="0";
	entry = (GtkEntry*)shuzu[3] ;
    shu = gtk_entry_get_text(entry);
    fanwei[0][1] = atoi(shu);
	ptr[3]=shu;
	if(strlen(shu)==0)
		ptr[3]="100";
	entry = (GtkEntry*)shuzu[4] ;
    shu = gtk_entry_get_text(entry);
    fanwei[1][1] = atoi(shu);
	ptr[4]=shu;
	if(strlen(shu)==0)
		ptr[4]="100";
	entry = (GtkEntry*)shuzu[5] ;
    shu = gtk_entry_get_text(entry);
    fanwei[2][1] = atoi(shu);
	ptr[5]=shu;
	if(strlen(shu)==0)
		ptr[5]="100";
	entry = (GtkEntry*)shuzu[6] ;
    const gchar *name = gtk_entry_get_text(entry);
	if(strlen(name)==0)
          name_sign=0;
	else 
		name_sign=1;
   if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shuzu[7])))
     sex_sign=0;
	else  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(shuzu[8])))
	sex_sign=1;
	else 
	sex_sign=2;
	int ii,jj;
	for(ii=0;ii<3;ii++)
		for(jj=0;jj<2;jj++)
	///		printf("fanwei[%d][%d] = %d\n",ii,jj,fanwei[ii][jj]);
	//printf("name= %s\n",name);
	//printf("sex_sign = %d\n",sex_sign);
	//printf("shu = %S\n",ptr[0]);
	
	sql ="select * from student where ";
	if (name_sign==1)
	{
	sql =str_str(sql,"name = '");	
	sql =str_str(sql,name);
	sql =str_str(sql,"' and ");
	}
	else
	{}
	sql =str_str(sql," Chinese >");
    sql =str_str(sql,ptr[0]);
	sql =str_str(sql," and Chinese <");
	sql =str_str(sql,ptr[3]);
	sql =str_str(sql," and Math >");
    sql =str_str(sql,ptr[1]);
	sql =str_str(sql," and Math <");
	sql =str_str(sql,ptr[4]);
	sql =str_str(sql," and English >");
    sql =str_str(sql,ptr[2]);
	sql =str_str(sql," and English <");
	sql =str_str(sql,ptr[5]);
	    if(sex_sign==0)
	 sql=str_str(sql," and sex='男'");
	 else if(sex_sign==1)
		 sql=str_str(sql," and sex='女'");
	 else {};
    //printf("%s\n",sql);
    result = sqlite3_get_table(pdb,sql,&dbResult,&nRow,&nCloumn,&ErrMsg);
    //printf("n = %d\n",nRow);
	if(nRow==0)
	{
	  GtkWidget *dialog;
	  GtkWidget *label;
	  dialog = gtk_dialog_new();
	  gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
	  gtk_widget_set_usize(dialog,100,100);
	  label = gtk_label_new("查询失败！");
	  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
      g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
      gtk_widget_show_all(dialog);
	  gtk_main();
	}
	else
	{
		temp="";
		for(i = 0;i < nRow;i++)
		{
		for(j = 0;j < nCloumn;j++)
		{
              	
              // printf("%s--->%s\n",dbResult[j],dbResult[(i+1)*nCloumn+j]);
               if(xuanzhong[j]==1)
				  temp1=str_filled(dbResult[(i+1)*nCloumn+j]);
			  else
				  temp1="                      ";
			      temp=str_str(temp,temp1);
		}
		if(i<(nRow-1))
		temp = str_str(temp,"\n");
		}

	}

//  printf("temp = %s\n",temp);
  gtk_text_buffer_set_text(buffer,temp,-1);
  sqlite3_free_table(dbResult);
  sqlite3_close(pdb);
}

