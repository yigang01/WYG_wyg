/*************************************************************************
    > File Name: traffic_system.c
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月02日 星期二 16时49分31秒
    实现一个交通违章管理系统，分别对机动车、驾驶员、警察、违章处罚、通知书
    进行增删查改操作，最后还可给违章驾驶员发送一张违章通知单，本系统运用gtk
    和sqlite3以及一点c语言知识来编写的，代码总长2928行
 ************************************************************************/

#include<stdio.h>
#include<gtk/gtk.h>
#include<string.h>
#include<stdlib.h>
#include<sqlite3.h>
GtkWidget *shuzu[5];
char *  str_str(char *A,char *B);
char *table[5]={"","","","",""};
char *temp="";
char *str_filled(char *str);
void callback_button(GtkWidget *button,GtkWidget *entry[3]);
//登陆成功进入的界面内容调用的回调函数
void callback_button1(GtkWidget *button,GtkWidget *entry[3]);
void callback_button2(GtkWidget *button,GtkWidget *entry[3]);
void callback_button3(GtkWidget *button,GtkWidget *entry[3]);
void callback_button4(GtkWidget *button,GtkWidget *entry[3]);
//机动车辆界面内容调用的回调函数
void callback_buttonc1(GtkWidget *button);
void callback_buttonc2(GtkWidget *button);
void callback_buttonc3(GtkWidget *button);
void callback_buttonc4(GtkWidget *button);
void lookforc1(GtkWidget *button,GtkWidget *shuzu[5]);
void lookforc2(GtkWidget *button,GtkWidget *shuzu[5]);
void lookforc3(GtkWidget *button,GtkWidget *shuzu[5]);
void lookforc4(GtkWidget *button,GtkWidget *shuzu[3]);
//驾驶员界面内容调用的回调函数
void callback_buttond1(GtkWidget *button);
void callback_buttond2(GtkWidget *button);
void callback_buttond3(GtkWidget *button);
void callback_buttond4(GtkWidget *button);
void lookford1(GtkWidget *button,GtkWidget *shuzu[7]);
void lookford2(GtkWidget *button,GtkWidget *shuzu[7]);
void lookford3(GtkWidget *button,GtkWidget *shuzu[7]);
void lookford4(GtkWidget *button,GtkWidget *shuzu[7]);
//交警界面内容调用的回调函数
void callback_buttonp1(GtkWidget *button);
void callback_buttonp2(GtkWidget *button);
void callback_buttonp3(GtkWidget *button);
void callback_buttonp4(GtkWidget *button);
void lookforp1(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforp2(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforp3(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforp4(GtkWidget *button,GtkWidget *shuzu[7]);
//违章信息界面内容调用的回调函数
void callback_buttonn1(GtkWidget *button);
void callback_buttonn2(GtkWidget *button);
void callback_buttonn3(GtkWidget *button);
void callback_buttonn4(GtkWidget *button);
void lookforn1(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforn2(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforn3(GtkWidget *button,GtkWidget *shuzu[7]);
void lookforn4(GtkWidget *button,GtkWidget *shuzu[7]);
//通知书信息姐买你内容调用的回调函数
void callback_button6(GtkWidget *button);
void callback_buttonb1(GtkWidget *button);
void callback_buttonb2(GtkWidget *button);
void callback_buttonb3(GtkWidget *button);
void callback_buttonb4(GtkWidget *button);
void lookforb1(GtkWidget *button,GtkWidget *shuzu[10]);
void lookforb2(GtkWidget *button,GtkWidget *shuzu[10]);
void lookforb3(GtkWidget *button,GtkWidget *shuzu[10]);
void lookforb4(GtkWidget *button,GtkWidget *shuzu[10]);

//通知单显示
void callback_button5(GtkWidget *button);
void show(GtkWidget *button,GtkWidget *shuzu[25]);
//窗口关闭函数
static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data);
//绘制背景图函数
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
    gtk_widget_set_app_paintable(widget, TRUE);     //允许窗口可以绘图
    gtk_widget_realize(widget); 
    gtk_widget_queue_draw(widget);
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);
    GdkPixmap *pixmap = NULL;
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
    g_object_unref(src_pixbuf);
    g_object_unref(dst_pixbuf);
    g_object_unref(pixmap);
}
int main(int argc,char* argv[])
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *button1;
    GtkWidget *fixed;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry[3];

    gtk_init(&argc,&argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"交通违章管理系统登陆");//标题
    gtk_widget_set_usize(window,400,200);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    chang_background(window, 400, 200, "wyg.jpg");
    //创建一个固定布局,创建标签和按钮并把标签按钮和行编辑都放在这个固定布局里面
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    label = gtk_label_new("用户");
    label1 = gtk_label_new("密码");
    button1 = gtk_button_new_with_label("登录");
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    gtk_fixed_put(GTK_FIXED(fixed),label,80,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,80,80);
    gtk_fixed_put(GTK_FIXED(fixed),button1,265,120);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,150,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,150,80);
    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);//设置密码不可见，entry2是一个编辑密码行，所以肯定不可见
    entry[0] = entry1;
    entry[1] = entry2;
    entry[2] = window;
    //写回调函数
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_button),&entry);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
//如果登陆成功，会回调callback_button函数
void callback_button(GtkWidget *button,GtkWidget *entry[3])
{
    char *name = NULL;
    char *password = NULL;
    gboolean btn_state;
    name = gtk_entry_get_text((GtkEntry *)entry[0]);
    password = gtk_entry_get_text((GtkEntry *)entry[1]);
    if(strcmp(name,"wyg") == 0 && strcmp(password,"123456wyg") == 0)//判断账号密码是否匹配
    {
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title((GtkWindow*)window,"登陆成功");
        gtk_widget_set_usize(window,500,400);
        gtk_container_set_border_width(GTK_CONTAINER(window),15);
        GtkWidget *fixed = gtk_fixed_new();
        gtk_container_add(GTK_CONTAINER(window),fixed);
        gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
        chang_background(window, 500, 400, "wyg1.jpg");
        //在登陆成功进去的页面放入该放的东西
        GtkWidget *button1;
        GtkWidget *button2;
        GtkWidget *button3;
        GtkWidget *button4;
        GtkWidget *button5;
        GtkWidget *button6;
        GtkWidget *label;
        button1 = gtk_button_new_with_label("机动车辆");
        button2 = gtk_button_new_with_label("驾驶员");
        button3 = gtk_button_new_with_label("交通警察");
        button4 = gtk_button_new_with_label("违章处罚");
        button5 = gtk_button_new_with_label("交通违章通知书");
        button6 = gtk_button_new_with_label("通知书");
        label = gtk_label_new("欢迎使用交通违章管理系统");
        gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
        gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
        gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
        gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
        gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
        gtk_fixed_put(GTK_FIXED(fixed),button5,300,300);
        gtk_fixed_put(GTK_FIXED(fixed),button6,60,300);
        release_resourse(entry[2],NULL,NULL);
        g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
        g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_button1),NULL);
        g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_button2),NULL);
        g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_button3),NULL);
        g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_button4),NULL);  
        g_signal_connect(G_OBJECT(button5),"pressed",G_CALLBACK(callback_button5),NULL);  
        g_signal_connect(G_OBJECT(button6),"pressed",G_CALLBACK(callback_button6),NULL);  
        gtk_widget_show_all(window);
        gtk_main();
    }
    else
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();//创建一个对话框
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,300,100);//设置对话框大小
        label = gtk_label_new("用户名或密码错误！请重新输入");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();
    }
}

//交通违章通知书
void callback_button5(GtkWidget *button)
{
    GtkWidget *label1 = gtk_label_new("交通违章通知书");
    GtkWidget *label2 = gtk_label_new("编号");
    GtkWidget *label3 = gtk_label_new("姓名:");
    GtkWidget *label4 = gtk_label_new("驾驶证号:");
    GtkWidget *label5 = gtk_label_new("地址:");
    GtkWidget *label6 = gtk_label_new("邮编:");
    GtkWidget *label7 = gtk_label_new("电话:");
    GtkWidget *label8 = gtk_label_new("机动车牌照号:");
    GtkWidget *label9 = gtk_label_new("型号:");
    GtkWidget *label10 = gtk_label_new("制造厂:");
    GtkWidget *label11 = gtk_label_new("生产日期:");
    GtkWidget *label12 = gtk_label_new("违章日期:");
    GtkWidget *label13 = gtk_label_new("时间:");
    GtkWidget *label14 = gtk_label_new("地点:");
    GtkWidget *label15 = gtk_label_new("违章记载:");
    GtkWidget *label16 = gtk_label_new("警察签字:");
    GtkWidget *label17 = gtk_label_new("警察编号:");
    GtkWidget *label18 = gtk_label_new("被处罚人签字:");
    GtkWidget *label19 = gtk_label_new("处罚方法:");
    GtkWidget *label20 = gtk_label_new("警告:");
    GtkWidget *label21 = gtk_label_new("罚款:");
    GtkWidget *label22 = gtk_label_new("暂扣驾驶证:");
    GtkWidget *label23 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label24 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label25 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label26 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label27 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label28 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *label29 = gtk_label_new("----------------------------------------------------------------------------------------------------------------");
    GtkWidget *window;
    GtkWidget *button1 = gtk_button_new_with_label("确定");
    GtkWidget *fixed;
    GtkWidget *entry1 = gtk_entry_new_with_max_length(15);
    char *label_table[18];
    GtkWidget *shuzu[25];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"交通违章通知书");
    gtk_widget_set_usize(window,600,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_fixed_put(GTK_FIXED(fixed),label1,120,12);
    gtk_fixed_put(GTK_FIXED(fixed),label2,270,12);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,300,5);
    gtk_fixed_put(GTK_FIXED(fixed),button1,500,5);
    gtk_fixed_put(GTK_FIXED(fixed),label23,5,40);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,60);
    gtk_fixed_put(GTK_FIXED(fixed),label4,250,60);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label6,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label7,250,140);
    gtk_fixed_put(GTK_FIXED(fixed),label24,5,160);
    gtk_fixed_put(GTK_FIXED(fixed),label8,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label9,250,180);
    gtk_fixed_put(GTK_FIXED(fixed),label10,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label11,250,220);
    gtk_fixed_put(GTK_FIXED(fixed),label25,5,240);
    gtk_fixed_put(GTK_FIXED(fixed),label12,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),label13,250,260);
    gtk_fixed_put(GTK_FIXED(fixed),label14,60,300);
    gtk_fixed_put(GTK_FIXED(fixed),label15,250,300);
    gtk_fixed_put(GTK_FIXED(fixed),label26,5,320);
    gtk_fixed_put(GTK_FIXED(fixed),label19,60,340);
    gtk_fixed_put(GTK_FIXED(fixed),label20,150,380);
    gtk_fixed_put(GTK_FIXED(fixed),label21,250,380);
    gtk_fixed_put(GTK_FIXED(fixed),label22,350,380);
    gtk_fixed_put(GTK_FIXED(fixed),label27,5,400);
    gtk_fixed_put(GTK_FIXED(fixed),label16,60,420);
    gtk_fixed_put(GTK_FIXED(fixed),label17,250,420);
    gtk_fixed_put(GTK_FIXED(fixed),label28,5,440);
    gtk_fixed_put(GTK_FIXED(fixed),label18,60,460);
    gtk_fixed_put(GTK_FIXED(fixed),label29,5,480);

    shuzu[0]=entry1;
    shuzu[1]=label3;
    shuzu[2]=label4;
    shuzu[3]=label5;
    shuzu[4]=label6;
    shuzu[5]=label7;
    shuzu[6]=label8;
    shuzu[7]=label9;
    shuzu[8]=label10;
    shuzu[9]=label11;
    shuzu[10]=label12;
    shuzu[11]=label13;
    shuzu[12]=label14;
    shuzu[13]=label15;
    shuzu[14]=label19;
    shuzu[15]=label16;
    shuzu[16]=label17;
    shuzu[17]=label18;
    shuzu[18]=label20;
    shuzu[19]=label21;
    shuzu[20]=label22;
    shuzu[21]=label1;
    shuzu[22]=label2;
    shuzu[23]=window;

    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(show),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//通知单的数据库操作函数
void show(GtkWidget *button,GtkWidget *shuzu[25])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select driveName,drive.driveNo,driveAddress,driveEmail,drivePhone,car.carNo,carType,carProduct,carDate,informDate,informTime,informAddress,informRead,punishDeal,policeName,police.policeNo driveName from car,drive,police,punish,inform where car.carNo=inform.carNo and drive.driveNo=inform.driveNo and police.policeNo=inform.policeNo and punish.punishNo=inform.punishNo and inform.punishNo ='001'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *punishNo = gtk_entry_get_text(entry);
    sql =str_str("select driveName,drive.driveNo,driveAddress,driveEmail,drivePhone,car.carNo,carType,carProduct,carDate,informDate,informTime,informAddress,informRead,punishDeal,policeName,police.policeNo driveName from car,drive,police,punish,inform where car.carNo=inform.carNo and drive.driveNo=inform.driveNo and police.policeNo=inform.policeNo and punish.punishNo=inform.punishNo and inform.punishNo ='",punishNo);
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
                table[j]=str_str("姓名： ",dbResult[(i+1)*nCloumn+j]);
            if(j==1)
                table[j]=str_str("驾驶证号： ",dbResult[(i+1)*nCloumn+j]); 
            if(j==2)
                table[j]=str_str("地址： ",dbResult[(i+1)*nCloumn+j]);
            if(j==3)
                table[j]=str_str("邮编： ",dbResult[(i+1)*nCloumn+j]);
            if(j==4)
                table[j]=str_str("电话： ",dbResult[(i+1)*nCloumn+j]);
            if(j==5)   
                table[j]=str_str("机动车牌照号： ",dbResult[(i+1)*nCloumn+j]);
            if(j==6)   
                table[j]=str_str("型号： ",dbResult[(i+1)*nCloumn+j]);
            if(j==7)   
                table[j]=str_str("制造厂： ",dbResult[(i+1)*nCloumn+j]);
            if(j==8)   
                table[j]=str_str("生产日期： ",dbResult[(i+1)*nCloumn+j]);
            if(j==9)   
                table[j]=str_str("违章日期： ",dbResult[(i+1)*nCloumn+j]);
            if(j==10)   
                table[j]=str_str("时间： ",dbResult[(i+1)*nCloumn+j]);
            if(j==11)   
                table[j]=str_str("地点： ",dbResult[(i+1)*nCloumn+j]);
            if(j==12)   
                table[j]=str_str("违章记载： ",dbResult[(i+1)*nCloumn+j]);
            if(j==13)   
                table[j]=str_str("处罚方法： ",dbResult[(i+1)*nCloumn+j]);
            if(j==14)   
                table[j]=str_str("警察签字： ",dbResult[(i+1)*nCloumn+j]);
            if(j==15)   
                table[j]=str_str("警察编号： ",dbResult[(i+1)*nCloumn+j]);
            //if(j==17)   
                //table[j]=str_str("被处罚人签字： ",dbResult[(i+1)*nCloumn+j]);
        }    
    }
    for (k=1;k<17;k++)
    gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
    gtk_widget_show_all(shuzu[22]);
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);
}

//关闭窗口
static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    gtk_main_quit();
    return FALSE;
}

//机动车辆
void callback_button1(GtkWidget *button,GtkWidget *entry[3])
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"机动车辆");
    gtk_widget_set_usize(window,500,400);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    chang_background(window, 500, 400, "wyg2.jpg");
    //去写机动车辆里面的内容
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;
    button1 = gtk_button_new_with_label("查看机动车辆信息");
    button2 = gtk_button_new_with_label("添加机动车辆信息");
    button3 = gtk_button_new_with_label("修改机动车辆信息");
    button4 = gtk_button_new_with_label("删除机动车辆信息");
    label = gtk_label_new("欢迎使用机动车辆系统");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
    gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
    gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
    gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
   //release_resourse(entry[2],NULL,NULL);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_buttonc1),NULL);//查询车辆信息的回调函数
    g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_buttonc2),NULL);//插入车辆信息的回调函数
    g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_buttonc3),NULL);//修改车辆信息的回调函数
    g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_buttonc4),NULL);//删除车辆信息的回调函数   
    gtk_widget_show_all(window);
    gtk_main();
}
//查询机动车辆信息
void callback_buttonc1(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    char *label_table[4];
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *fixed;
    GtkWidget *shuzu[6];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"查看机动车信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label = gtk_label_new("车牌号");
    label1 = gtk_label_new("车牌号");
    label2 = gtk_label_new("车型号");
    label3 = gtk_label_new("厂商名字");
    label4 = gtk_label_new("生产时间");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
    gtk_fixed_put(GTK_FIXED(fixed),button1,300,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    shuzu[0] = entry;
    shuzu[1] = label1;
    shuzu[2] = label2;
    shuzu[3] = label3;
    shuzu[4] = label4;
    shuzu[5] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforc1),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//对机动车辆查询信息的数据库操作
void lookforc1(GtkWidget *button,GtkWidget *shuzu[6])
{
    int k;
    char* temp = NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select * from car where carNo  ='A00000'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *carNo = gtk_entry_get_text(entry);
    sql =str_str("select * from car where carNo ='",carNo);
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
                    table[j]=str_str("车牌号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==1)
                    table[j]=str_str("车型号： ",dbResult[(i+1)*nCloumn+j]); 
                if(j==2)
                    table[j]=str_str("厂商名字： ",dbResult[(i+1)*nCloumn+j]);
                if(j==3)
                    table[j]=str_str("生产日期： ",dbResult[(i+1)*nCloumn+j]);
            }
    }
    for(k=1;k<5;k++)
        gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
        gtk_widget_show_all(shuzu[5]);
        sqlite3_free_table(dbResult);
        sqlite3_close(pdb);
}
//字符测连接
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
//添加机动车辆信息
void callback_buttonc2(GtkWidget *button)
{
    GtkWidget *window; 
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *fixed;
    GtkWidget *shuzu[5];
    //GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"添加机动车信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("车牌号");
    label2 = gtk_label_new("车型号");
    label3 = gtk_label_new("厂商名字");
    label4 = gtk_label_new("生产日期");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,120,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
    shuzu[0]=window;
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforc2),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//添加机动车辆信息的数据库操作
void  lookforc2(GtkWidget *button,GtkWidget *shuzu[5])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into car(carNo,carType,carproduct,carDate) values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *carNo = gtk_entry_get_text(entry);
    if(strlen(carNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,carNo);
        sql =str_str(sql,"','");
    }
    entry = (GtkEntry*)shuzu[2];
    carNo = gtk_entry_get_text(entry);
    if(strlen(carNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,carNo);
        sql =str_str(sql,"','");            
    }
    entry = (GtkEntry*)shuzu[3] ;
    carNo = gtk_entry_get_text(entry);
    if(strlen(carNo) == 0)
        carNo = "0";
    sql =str_str(sql,carNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[4] ;
    carNo = gtk_entry_get_text(entry);
    if(strlen(carNo)==0)
        carNo = "0";
    sql =str_str(sql,carNo);
    sql =str_str(sql,"')");
    printf("%s\n",sql);
    if(sign==0)
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,200,200);
        label = gtk_label_new("基本信息不全，无法添加！");
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
        label = gtk_label_new("添加成功！");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();                                                    
    }
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);
}
//修改机动车辆信息
void callback_buttonc3(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *fixed;
    GtkWidget *shuzu[5];
    GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"修改机动车辆信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("车牌号");
    label2 = gtk_label_new("车型号");
    label3 = gtk_label_new("厂商名字");
    label4 = gtk_label_new("生产日期");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,120,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforc3),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//修改机动车信息的数据操作
void  lookforc3(GtkWidget *button,GtkWidget *shuzu[5])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into car values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;

    char *sql1 = "select * from car where  carNo ='A00001'";
    char *ErrMsg1 = 0;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *carNo = gtk_entry_get_text(entry);
    const gchar *carNo1 = gtk_entry_get_text(entry);
    sql1 =str_str("select * from car where carNo ='",carNo1);
    sql1 =str_str(sql1,"'");
    sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
    if(nRow==1)
    {
        if(strlen(carNo) == 0)
            sign = 0;
        else
        {
            sql =str_str(sql,carNo);
            sql =str_str(sql,"','");
        }
        entry = (GtkEntry*)shuzu[2];
        carNo = gtk_entry_get_text(entry);
        if(strlen(carNo)==0)
        {
            sql =str_str(sql,dbResult[nCloumn+1]);
            sql =str_str(sql,"','");
        }
        else
        {
            sql =str_str(sql,carNo);
            sql =str_str(sql,"','");            
        }
        entry = (GtkEntry*)shuzu[3];
        carNo = gtk_entry_get_text(entry);
        if(strlen(carNo)==0)
        carNo = dbResult[nCloumn+2];
        sql =str_str(sql,carNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[4] ;
        carNo = gtk_entry_get_text(entry);
        if(strlen(carNo)==0)
        carNo = dbResult[nCloumn+3];
        sql =str_str(sql,carNo);
        sql =str_str(sql,"')");
        printf("%s\n",sql);
    }
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
        sql1="delete from car where carNo = '";
        sql1=str_str(sql1,carNo1);
        sql1=str_str(sql1,"'");
        printf("%s\n",sql1);
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
//删除机动车辆信息
void callback_buttonc4(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *fixed;
    GtkWidget *entry;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"删除机动车辆信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("请输入你想删除的机动车辆的车牌号");
    label2 = gtk_label_new("车牌号");
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,80);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),button1,100,200);
    gtk_fixed_put(GTK_FIXED(fixed),entry,120,140);
    shuzu[0] = window;
    shuzu[1] = entry;
    shuzu[2] = button1;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforc4),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//对车辆信息进行删除数据库操作
void lookforc4(GtkWidget *button,GtkWidget *shuzu[3])
{
     int k;
     char *temp=NULL;
     sqlite3 *pdb = NULL;
     sqlite3_open("db_car1.sql",&pdb);
     char *sql = "delete from car where carNo = '";
     char *ErrMsg = 0;
     int result,i,j;
     int sign = 1;
     char *szErrMsg;
     char **dbResult=NULL;
     GtkEntry *entry = (GtkEntry*)shuzu[1];
     const gchar *carNo = gtk_entry_get_text(entry);
     if(strlen(carNo) == 0)
     {
        sign = 0;
     }
     if(sign==0)
     {
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("没有该车辆，无法删除！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                               
     }
     else
     {
         sql = str_str(sql,carNo);
         sql = str_str(sql,"'");
         printf("%s\n",sql);
         sqlite3_exec(pdb,sql,0,0,&szErrMsg);
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("删除成功！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                                   
     }
}
//驾驶员
void callback_button2(GtkWidget *button,GtkWidget *entry[3])
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"驾驶员");
    gtk_widget_set_usize(window,500,400);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    chang_background(window, 500, 400, "wyg3.jpg");
    //去写驾驶员里面的内容
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;
    button1 = gtk_button_new_with_label("查看驾驶员信息");
    button2 = gtk_button_new_with_label("添加驾驶员信息");
    button3 = gtk_button_new_with_label("修改驾驶员信息");
    button4 = gtk_button_new_with_label("删除驾驶员信息");
    label = gtk_label_new("欢迎使用驾驶员系统");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
    gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
    gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
    gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_buttond1),NULL);//查询驾驶员信息的回调函数
    g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_buttond2),NULL);//插入驾驶员信息的回调函数
    g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_buttond3),NULL);//修改驾驶员信息的回调函数
    g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_buttond4),NULL);//删除驾驶员信息的回调函数   
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//查询驾驶员信息
void callback_buttond1(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    char *label_table[5];
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *fixed;
    GtkWidget *shuzu[7];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"查看驾驶员信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label = gtk_label_new("驾驶证号");
    label1 = gtk_label_new("驾驶证号");
    label2 = gtk_label_new("驾驶员姓名");
    label3 = gtk_label_new("驾驶员地址");
    label4 = gtk_label_new("驾驶员邮编");
    label5 = gtk_label_new("驾驶员电话");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
    gtk_fixed_put(GTK_FIXED(fixed),button1,300,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    shuzu[0] = entry;
    shuzu[1] = label1;
    shuzu[2] = label2;
    shuzu[3] = label3;
    shuzu[4] = label4;
    shuzu[5] = label5;
    shuzu[6] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookford1),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//查看驾驶员信息的数据库操作
void  lookford1(GtkWidget *button1,GtkWidget *shuzu[7])
{
    int k;
    char* temp = NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select * from drive where driveNo  ='123456789'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *driveNo = gtk_entry_get_text(entry);
    sql =str_str("select * from drive where driveNo ='",driveNo);
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
                    table[j]=str_str("驾驶证号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==1)
                    table[j]=str_str("驾驶员姓名： ",dbResult[(i+1)*nCloumn+j]); 
                if(j==2)
                    table[j]=str_str("驾驶员地址： ",dbResult[(i+1)*nCloumn+j]);
                if(j==3)
                    table[j]=str_str("驾驶员邮编： ",dbResult[(i+1)*nCloumn+j]);
                if(j==4)
                    table[j]=str_str("驾驶员电话： ",dbResult[(i+1)*nCloumn+j]);
            }
    }
    for(k=1;k<6;k++)
        gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
        gtk_widget_show_all(shuzu[6]);
        sqlite3_free_table(dbResult);
        sqlite3_close(pdb);
}
//添加驾驶员信息
void callback_buttond2(GtkWidget *button)
{
    GtkWidget *window; 
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *entry5;
    GtkWidget *fixed;
    GtkWidget *shuzu[6];
    //GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"添加机驾驶员信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    entry5 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("驾驶证号");
    label2 = gtk_label_new("驾驶员姓名");
    label3 = gtk_label_new("驾驶员地址");
    label4 = gtk_label_new("驾驶员邮编");
    label5 = gtk_label_new("驾驶员电话");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,150,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,150,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,150,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,150,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry5,150,260);
    shuzu[0]=window;
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    shuzu[5]=entry5;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookford2),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//添加驾驶员信息的数据库操作函数
void lookford2(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into drive(driveNo,driveName,driveAddress,driveEmail,drivePhone) values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *driveNo = gtk_entry_get_text(entry);
    if(strlen(driveNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,driveNo);
        sql =str_str(sql,"','");
    }
    entry = (GtkEntry*)shuzu[2];
    driveNo = gtk_entry_get_text(entry);
    if(strlen(driveNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,driveNo);
        sql =str_str(sql,"','");            
    }
    entry = (GtkEntry*)shuzu[3] ;
    driveNo = gtk_entry_get_text(entry);
    if(strlen(driveNo) == 0)
        driveNo = "0";
    sql =str_str(sql,driveNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[4] ;
    driveNo = gtk_entry_get_text(entry);
    if(strlen(driveNo) == 0)
        driveNo = "0";
    sql =str_str(sql,driveNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[5] ;
    driveNo = gtk_entry_get_text(entry);
    if(strlen(driveNo)==0)
        driveNo = "0";
    sql =str_str(sql,driveNo);
    sql =str_str(sql,"')");
    printf("%s\n",sql);
    if(sign==0)
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,200,200);
        label = gtk_label_new("基本信息不全，无法添加！");
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
        label = gtk_label_new("添加成功！");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();                                                    
    }
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);

}
//修改驾驶员信息
void callback_buttond3(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *entry5;
    GtkWidget *fixed;
    GtkWidget *shuzu[6];
    GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"修改驾驶员信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    entry5 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("驾驶证号");
    label2 = gtk_label_new("驾驶员姓名");
    label3 = gtk_label_new("驾驶员地址");
    label4 = gtk_label_new("驾驶员邮编");
    label5 = gtk_label_new("驾驶员电话");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,150,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,150,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,150,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,150,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry5,150,260);
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    shuzu[5]=entry5; 
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookford3),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//修改驾驶员信息数据库操作
void lookford3(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into drive values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;

    char *sql1 = "select * from drive where  driveNo ='1234567'";
    char *ErrMsg1 = 0;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *driveNo = gtk_entry_get_text(entry);
    const gchar *driveNo1 = gtk_entry_get_text(entry);
    sql1 =str_str("select * from drive where driveNo ='",driveNo1);
    sql1 =str_str(sql1,"'");
    sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
    if(nRow==1)
    {
        if(strlen(driveNo) == 0)
            sign = 0;
        else
        {
            sql =str_str(sql,driveNo);
            sql =str_str(sql,"','");
        }
        entry = (GtkEntry*)shuzu[2];
        driveNo = gtk_entry_get_text(entry);
        if(strlen(driveNo)==0)
        {
            sql =str_str(sql,dbResult[nCloumn+1]);
            sql =str_str(sql,"','");
        }
        else
        {
            sql =str_str(sql,driveNo);
            sql =str_str(sql,"','");            
        }
        entry = (GtkEntry*)shuzu[3];
        driveNo = gtk_entry_get_text(entry);
        if(strlen(driveNo)==0)
        driveNo = dbResult[nCloumn+2];
        sql =str_str(sql,driveNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[4];
        driveNo = gtk_entry_get_text(entry);
        if(strlen(driveNo)==0)
        driveNo = dbResult[nCloumn+3];
        sql =str_str(sql,driveNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[5] ;
        driveNo = gtk_entry_get_text(entry);
        if(strlen(driveNo)==0)
        driveNo = dbResult[nCloumn+4];
        sql =str_str(sql,driveNo);
        sql =str_str(sql,"')");
        printf("%s\n",sql);
    }
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
        sql1="delete from drive where driveNo = '";
        sql1=str_str(sql1,driveNo1);
        sql1=str_str(sql1,"'");
        printf("%s\n",sql1);
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
//删除驾驶员信息
void callback_buttond4(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *fixed;
    GtkWidget *entry;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"删除驾驶员信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("请输入你想删除的驾驶员的驾驶证号");
    label2 = gtk_label_new("驾驶证号");
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,80);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),button1,100,200);
    gtk_fixed_put(GTK_FIXED(fixed),entry,120,140);
    shuzu[0] = window;
    shuzu[1] = entry;
    shuzu[2] = button1;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookford4),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//删除驾驶员信息数据库操作
void lookford4(GtkWidget *button,GtkWidget *shuzu[7])
{
     int k;
     char *temp=NULL;
     sqlite3 *pdb = NULL;
     sqlite3_open("db_car1.sql",&pdb);
     char *sql = "delete from drive where driveNo = '";
     char *ErrMsg = 0;
     int result,i,j;
     int sign = 1;
     char *szErrMsg;
     char **dbResult=NULL;
     GtkEntry *entry = (GtkEntry*)shuzu[1];
     const gchar *driveNo = gtk_entry_get_text(entry);
     if(strlen(driveNo) == 0)
     {
        sign = 0;
     }
     if(sign==0)
     {
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("没有该驾驶员信息，无法删除！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                               
     }
     else
     {
         sql = str_str(sql,driveNo);
         sql = str_str(sql,"'");
         printf("%s\n",sql);
         sqlite3_exec(pdb,sql,0,0,&szErrMsg);
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("删除成功！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                                   
     }
}

//交通警察
void callback_button3(GtkWidget *button,GtkWidget *entry[3])
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"交通警察");
    gtk_widget_set_usize(window,500,400);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    chang_background(window, 500, 400, "wyg4.jpg");
    //去写驾驶员里面的内容
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;
    button1 = gtk_button_new_with_label("查看交警信息");
    button2 = gtk_button_new_with_label("添加交警信息");
    button3 = gtk_button_new_with_label("修改交警信息");
    button4 = gtk_button_new_with_label("删除交警信息");
    label = gtk_label_new("欢迎使用交通警察系统");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
    gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
    gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
    gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_buttonp1),NULL);//查询交通警察信息的回调函数
    g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_buttonp2),NULL);//插入交通警察信息的回调函数
    g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_buttonp3),NULL);//修改交通警察信息的回调函数
    g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_buttonp4),NULL);//删除交通警察信息的回调函数
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//查看交警信息
void callback_buttonp1(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *label2;
    char *label_table[2];
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *fixed;
    GtkWidget *shuzu[4];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"查看交警信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label = gtk_label_new("交警编号");
    label1 = gtk_label_new("交警编号");
    label2 = gtk_label_new("交警姓名");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
    gtk_fixed_put(GTK_FIXED(fixed),button1,300,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,160);
    shuzu[0] = entry;
    shuzu[1] = label1;
    shuzu[2] = label2;
    shuzu[3] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforp1),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//查询交警信息数据库操作
void lookforp1(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char* temp = NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select * from police where policeNo  ='00000'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *policeNo = gtk_entry_get_text(entry);
    sql =str_str("select * from police where policeNo ='",policeNo);
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
                    table[j]=str_str("交警编号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==1)
                    table[j]=str_str("交警姓名： ",dbResult[(i+1)*nCloumn+j]); 
            }
    }
    for(k=1;k<3;k++)
        gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
        gtk_widget_show_all(shuzu[3]);
        sqlite3_free_table(dbResult);
        sqlite3_close(pdb);
}
//添加交警信息
void callback_buttonp2(GtkWidget *button)
{
    GtkWidget *window; 
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *fixed;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"添加交警信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("交警编号");
    label2 = gtk_label_new("交警姓名");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    shuzu[0]=window;
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforp2),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//添加交警信息的数据库操作
void lookforp2(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into police(policeNo,policeName) values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *policeNo = gtk_entry_get_text(entry);
    if(strlen(policeNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,policeNo);
        sql =str_str(sql,"','");
    }
    entry = (GtkEntry*)shuzu[2];
    policeNo = gtk_entry_get_text(entry);
    if(strlen(policeNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,policeNo);
        sql =str_str(sql,"')");
        printf("%s\n",sql);
    }
    if(sign==0)
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,200,200);
        label = gtk_label_new("基本信息不全，无法添加！");
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
        label = gtk_label_new("添加成功！");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();                                                    
    }
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);

}
//修改交警信息
void callback_buttonp3(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *fixed;
    GtkWidget *shuzu[3];
    GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"修改交警信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("交警编号");
    label2 = gtk_label_new("交警姓名");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,160);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,160);
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforp3),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//修改交警信息数据库操作
void lookforp3(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into police values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;

    char *sql1 = "select * from police where  policeNo ='00001'";
    char *ErrMsg1 = 0;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *policeNo = gtk_entry_get_text(entry);
    const gchar *policeNo1 = gtk_entry_get_text(entry);
    sql1 =str_str("select * from police where policeNo ='",policeNo1);
    sql1 =str_str(sql1,"'");
    sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
    if(nRow==1)
    {
        if(strlen(policeNo) == 0)
            sign = 0;
        else
        {
            sql =str_str(sql,policeNo);
            sql =str_str(sql,"','");
        }
        entry = (GtkEntry*)shuzu[2];
        policeNo = gtk_entry_get_text(entry);
        if(strlen(policeNo)==0)
        {
            sql =str_str(sql,dbResult[nCloumn+1]);
            sql =str_str(sql,"','");
        }
        else
        {
            sql =str_str(sql,policeNo);
            sql =str_str(sql,"')");
            printf("%s\n",sql);
        }
    }
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
        sql1="delete from police where policeNo = '";
        sql1=str_str(sql1,policeNo1);
        sql1=str_str(sql1,"'");
        printf("%s\n",sql1);
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
//删除交警信息
void callback_buttonp4(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *fixed;
    GtkWidget *entry;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"删除交警信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("请输入你想要删除交警的交警编号");
    label2 = gtk_label_new("交警编号");
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,80);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),button1,100,200);
    gtk_fixed_put(GTK_FIXED(fixed),entry,120,140);
    shuzu[0] = window;
    shuzu[1] = entry;
    shuzu[2] = button1;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforp4),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//删除交警信息的数据操作
void lookforp4(GtkWidget *button,GtkWidget *shuzu[7])
{
     int k;
     char *temp=NULL;
     sqlite3 *pdb = NULL;
     sqlite3_open("db_car1.sql",&pdb);
     char *sql = "delete from police where policeNo = '";
     char *ErrMsg = 0;
     int result,i,j;
     int sign = 1;
     char *szErrMsg;
     char **dbResult=NULL;
     GtkEntry *entry = (GtkEntry*)shuzu[1];
     const gchar *policeNo = gtk_entry_get_text(entry);
     if(strlen(policeNo) == 0)
     {
        sign = 0;
     }
     if(sign==0)
     {
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("没有该交警，无法删除！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                               
     }
     else
     {
         sql = str_str(sql,policeNo);
         sql = str_str(sql,"'");
         printf("%s\n",sql);
         sqlite3_exec(pdb,sql,0,0,&szErrMsg);
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("删除成功！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                                   
     }

}
//违章信息
void callback_button4(GtkWidget *button,GtkWidget *entry[3])
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"违章信息");
    gtk_widget_set_usize(window,500,400);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    chang_background(window, 500, 400, "wyg5.jpg");
    //去写机动车辆里面的内容
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;
    button1 = gtk_button_new_with_label("查看违章处罚信息");
    button2 = gtk_button_new_with_label("添加违章处罚信息");
    button3 = gtk_button_new_with_label("修改违章处罚信息");
    button4 = gtk_button_new_with_label("删除违章处罚信息");
    label = gtk_label_new("欢迎使用违章处罚系统");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
    gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
    gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
    gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
   //release_resourse(entry[2],NULL,NULL);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_buttonn1),NULL);//查询车辆信息的回调函数
    g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_buttonn2),NULL);//插入车辆信息的回调函数
    g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_buttonn3),NULL);//修改车辆信息的回调函数
    g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_buttonn4),NULL);//删除车辆信息的回调函数   
    gtk_widget_show_all(window);
    gtk_main();
}
//查看违章信息
void callback_buttonn1(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *label2;
    char *label_table[2];
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *fixed;
    GtkWidget *shuzu[4];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"查看处罚信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label = gtk_label_new("处罚编号");
    label1 = gtk_label_new("处罚编号");
    label2 = gtk_label_new("处罚方式");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
    gtk_fixed_put(GTK_FIXED(fixed),button1,300,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,160);
    shuzu[0] = entry;
    shuzu[1] = label1;
    shuzu[2] = label2;
    shuzu[3] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforn1),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
void lookforn1(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char* temp = NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select * from punish where punishNo  ='00000'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *punishNo = gtk_entry_get_text(entry);
    sql =str_str("select * from punish where punishNo ='",punishNo);
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
                    table[j]=str_str("处罚编码： ",dbResult[(i+1)*nCloumn+j]);
                if(j==1)
                    table[j]=str_str("处罚方式： ",dbResult[(i+1)*nCloumn+j]); 
            }
    }
    for(k=1;k<3;k++)
        gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
        gtk_widget_show_all(shuzu[3]);
        sqlite3_free_table(dbResult);
        sqlite3_close(pdb);
}
//添加违章信息
void callback_buttonn2(GtkWidget *button)
{
    GtkWidget *window; 
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *fixed;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"添加违章处罚信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("处罚编号");
    label2 = gtk_label_new("处罚方式");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    shuzu[0]=window;
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforn2),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
void lookforn2(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into punish(punishNo,punishDeal) values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
    }
    entry = (GtkEntry*)shuzu[2];
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"')");
        printf("%s\n",sql);
    }
    if(sign==0)
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,200,200);
        label = gtk_label_new("基本信息不全，无法添加！");
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
        label = gtk_label_new("添加成功！");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();                                                    
    }
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);

}
//修改违章信息
void callback_buttonn3(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *fixed;
    GtkWidget *shuzu[3];
    GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"修改处罚信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("处罚编号");
    label2 = gtk_label_new("处罚方式");
    gtk_fixed_put(GTK_FIXED(fixed),button1,240,340);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,160);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,160);
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforn3),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
void lookforn3(GtkWidget *button,GtkWidget *shuzu[7])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into punish values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;

    char *sql1 = "select * from punish where  punishNo ='00001'";
    char *ErrMsg1 = 0;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *punishNo = gtk_entry_get_text(entry);
    const gchar *punishNo1 = gtk_entry_get_text(entry);
    sql1 =str_str("select * from punish where punishNo ='",punishNo1);
    sql1 =str_str(sql1,"'");
    sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
    if(nRow==1)
    {
        if(strlen(punishNo) == 0)
            sign = 0;
        else
        {
            sql =str_str(sql,punishNo);
            sql =str_str(sql,"','");
        }
        entry = (GtkEntry*)shuzu[2];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        {
            sql =str_str(sql,dbResult[nCloumn+1]);
            sql =str_str(sql,"','");
        }
        else
        {
            sql =str_str(sql,punishNo);
            sql =str_str(sql,"')");
            printf("%s\n",sql);
        }
    }
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
        sql1="delete from punish where punishNo = '";
        sql1=str_str(sql1,punishNo1);
        sql1=str_str(sql1,"'");
        printf("%s\n",sql1);
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
//删除违章信息
void callback_buttonn4(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *fixed;
    GtkWidget *entry;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"删除违章处罚信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("请输入你想要删除违章处罚的处罚编号");
    label2 = gtk_label_new("处罚编号");
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,80);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),button1,100,200);
    gtk_fixed_put(GTK_FIXED(fixed),entry,120,140);
    shuzu[0] = window;
    shuzu[1] = entry;
    shuzu[2] = button1;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforn4),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
void lookforn4(GtkWidget *button,GtkWidget *shuzu[7])
{
     int k;
     char *temp=NULL;
     sqlite3 *pdb = NULL;
     sqlite3_open("db_car1.sql",&pdb);
     char *sql = "delete from punish where punishNo = '";
     char *ErrMsg = 0;
     int result,i,j;
     int sign = 1;
     char *szErrMsg;
     char **dbResult=NULL;
     GtkEntry *entry = (GtkEntry*)shuzu[1];
     const gchar *punishNo = gtk_entry_get_text(entry);
     if(strlen(punishNo) == 0)
     {
        sign = 0;
     }
     if(sign==0)
     {
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("没有该违章处罚信息，无法删除！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                               
     }
     else
     {
         sql = str_str(sql,punishNo);
         sql = str_str(sql,"'");
         printf("%s\n",sql);
         sqlite3_exec(pdb,sql,0,0,&szErrMsg);
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("删除成功！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                                   
     }
}
//通知书
void callback_button6(GtkWidget *button)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"通知书");
    gtk_widget_set_usize(window,500,400);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    chang_background(window, 500, 400, "wyg3.jpg");
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *label;
    button1 = gtk_button_new_with_label("查看通知书信息");
    button2 = gtk_button_new_with_label("添加通知书信息");
    button3 = gtk_button_new_with_label("修改通知书信息");
    button4 = gtk_button_new_with_label("删除通知书信息");
    label = gtk_label_new("欢迎通知书系统");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,20);
    gtk_fixed_put(GTK_FIXED(fixed),button1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),button2,300,100);
    gtk_fixed_put(GTK_FIXED(fixed),button3,60,200);
    gtk_fixed_put(GTK_FIXED(fixed),button4,300,200);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_buttonb1),NULL);//查询通知书信息的回调函数
    g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(callback_buttonb2),NULL);//插入通知书信息的回调函数
    g_signal_connect(G_OBJECT(button3),"pressed",G_CALLBACK(callback_buttonb3),NULL);//修改通知书信息的回调函数
    g_signal_connect(G_OBJECT(button4),"pressed",G_CALLBACK(callback_buttonb4),NULL);//删除通知书信息的回调函数   
    gtk_widget_show_all(window);
    gtk_main();
}
//通知书查询
void callback_buttonb1(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;
    GtkWidget *label7;
    GtkWidget *label8;
    char *label_table[8];
    GtkWidget *button1;
    GtkWidget *entry;
    GtkWidget *fixed;
    GtkWidget *shuzu[10];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"查看通知书信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label = gtk_label_new("编号");
    label1 = gtk_label_new("编号");
    label2 = gtk_label_new("日期");
    label3 = gtk_label_new("时间");
    label4 = gtk_label_new("地点");
    label5 = gtk_label_new("违章记载");
    label6 = gtk_label_new("车牌号");
    label7 = gtk_label_new("驾驶证号");
    label8 = gtk_label_new("警察编号");
    gtk_fixed_put(GTK_FIXED(fixed),label,40,40);
    gtk_fixed_put(GTK_FIXED(fixed),button1,300,40);
    gtk_fixed_put(GTK_FIXED(fixed),entry,100,40);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
    gtk_fixed_put(GTK_FIXED(fixed),label7,60,340);
    gtk_fixed_put(GTK_FIXED(fixed),label8,60,380);
    shuzu[0] = entry;
    shuzu[1] = label1;
    shuzu[2] = label2;
    shuzu[3] = label3;
    shuzu[4] = label4;
    shuzu[5] = label5;
    shuzu[6] = label6;
    shuzu[7] = label7;
    shuzu[8] = label8;
    shuzu[9] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforb1),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//通知书数据库操作
void lookforb1(GtkWidget *button,GtkWidget *shuzu[10])
{
    int k;
    char* temp = NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "select * from inform where punishNo  ='00000'";
    char *ErrMsg = 0;
    int result,i,j;
    char **dbResult=NULL;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[0];
    const gchar *punishNo = gtk_entry_get_text(entry);
    sql =str_str("select * from inform where punishNo ='",punishNo);
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
                    table[j]=str_str("编号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==1)
                    table[j]=str_str("日期： ",dbResult[(i+1)*nCloumn+j]); 
                if(j==2)
                    table[j]=str_str("时间： ",dbResult[(i+1)*nCloumn+j]);
                if(j==3)
                    table[j]=str_str("地点： ",dbResult[(i+1)*nCloumn+j]);
                if(j==4)
                    table[j]=str_str("违章记载： ",dbResult[(i+1)*nCloumn+j]);
                if(j==5)
                    table[j]=str_str("车牌号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==6)
                    table[j]=str_str("驾驶证号： ",dbResult[(i+1)*nCloumn+j]);
                if(j==7)
                    table[j]=str_str("警察编号： ",dbResult[(i+1)*nCloumn+j]);
            }
    }
    for(k=1;k<9;k++)
        gtk_label_set_text(GTK_LABEL(shuzu[k]),table[k-1]);
        gtk_widget_show_all(shuzu[9]);
        sqlite3_free_table(dbResult);
        sqlite3_close(pdb);

}
//添加通知书内容
void callback_buttonb2(GtkWidget *button)
{
    GtkWidget *window; 
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;
    GtkWidget *label7;
    GtkWidget *label8;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *entry5;
    GtkWidget *entry6;
    GtkWidget *entry7;
    GtkWidget *entry8;
    GtkWidget *fixed;
    GtkWidget *shuzu[9];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"添加通知书");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    entry5 = gtk_entry_new_with_max_length(20);
    entry6 = gtk_entry_new_with_max_length(20);
    entry7 = gtk_entry_new_with_max_length(20);
    entry8 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("编号");
    label2 = gtk_label_new("日期");
    label3 = gtk_label_new("时间");
    label4 = gtk_label_new("地点");
    label5 = gtk_label_new("违章记载");
    label6 = gtk_label_new("车牌号");
    label7 = gtk_label_new("驾驶证号");
    label8 = gtk_label_new("警察编号");
    gtk_fixed_put(GTK_FIXED(fixed),button1,150,450);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
    gtk_fixed_put(GTK_FIXED(fixed),label7,60,340);
    gtk_fixed_put(GTK_FIXED(fixed),label8,60,380);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,120,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry5,120,260);
    gtk_fixed_put(GTK_FIXED(fixed),entry6,120,300);
    gtk_fixed_put(GTK_FIXED(fixed),entry7,120,340);
    gtk_fixed_put(GTK_FIXED(fixed),entry8,120,380);
    shuzu[0]=window;
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    shuzu[5]=entry5;
    shuzu[6]=entry6;
    shuzu[7]=entry7;
    shuzu[8]=entry8;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforb2),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
}
//添加通知书数据库操作
void lookforb2(GtkWidget *button,GtkWidget *shuzu[10])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into inform(punishNo,informDate,informTime,informAddress,informRead,carNo,driveNo,policeNo) values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
    }
    entry = (GtkEntry*)shuzu[2];
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
    {
        sign = 0;
    }
    else
    {
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");            
    }
    entry = (GtkEntry*)shuzu[3] ;
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[4] ;
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[5] ;
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[6] ;
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[7] ;
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo) == 0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"','");
    entry = (GtkEntry*)shuzu[8];
    punishNo = gtk_entry_get_text(entry);
    if(strlen(punishNo)==0)
        punishNo = "0";
    sql =str_str(sql,punishNo);
    sql =str_str(sql,"')");
    printf("%s\n",sql);
    if(sign==0)
    {
        GtkWidget *dialog;
        GtkWidget *label;
        dialog = gtk_dialog_new();
        gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
        gtk_widget_set_usize(dialog,200,200);
        label = gtk_label_new("基本信息不全，无法添加！");
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
        label = gtk_label_new("添加成功！");
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
        g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
        gtk_widget_show_all(dialog);
        gtk_main();                                                    
    }
    sqlite3_free_table(dbResult);
    sqlite3_close(pdb);

}
//修改通知书
void callback_buttonb3(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget *label4;
    GtkWidget *label5;
    GtkWidget *label6;
    GtkWidget *label7;
    GtkWidget *label8;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *entry4;
    GtkWidget *entry5;
    GtkWidget *entry6;
    GtkWidget *entry7;
    GtkWidget *entry8;
    GtkWidget *fixed;
    GtkWidget *shuzu[9];
    GSList *group;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"修改通知书信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    entry3 = gtk_entry_new_with_max_length(20);
    entry4 = gtk_entry_new_with_max_length(20);
    entry5 = gtk_entry_new_with_max_length(20);
    entry6 = gtk_entry_new_with_max_length(20);
    entry7 = gtk_entry_new_with_max_length(20);
    entry8 = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("编号");
    label2 = gtk_label_new("日期");
    label3 = gtk_label_new("时间");
    label4 = gtk_label_new("地点");
    label5 = gtk_label_new("违章记载");
    label6 = gtk_label_new("车牌号");
    label7 = gtk_label_new("驾驶证号");
    label8 = gtk_label_new("警察编号");
    gtk_fixed_put(GTK_FIXED(fixed),button1,250,450);
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,100);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),label3,60,180);
    gtk_fixed_put(GTK_FIXED(fixed),label4,60,220);
    gtk_fixed_put(GTK_FIXED(fixed),label5,60,260);
    gtk_fixed_put(GTK_FIXED(fixed),label6,60,300);
    gtk_fixed_put(GTK_FIXED(fixed),label7,60,340);
    gtk_fixed_put(GTK_FIXED(fixed),label8,60,380);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,120,100);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,120,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry3,120,180);
    gtk_fixed_put(GTK_FIXED(fixed),entry4,120,220);
    gtk_fixed_put(GTK_FIXED(fixed),entry5,120,260);
    gtk_fixed_put(GTK_FIXED(fixed),entry6,120,300);
    gtk_fixed_put(GTK_FIXED(fixed),entry7,120,340);
    gtk_fixed_put(GTK_FIXED(fixed),entry8,120,380);
    shuzu[1]=entry1;
    shuzu[2]=entry2;
    shuzu[3]=entry3;
    shuzu[4]=entry4;
    shuzu[5]=entry5;
    shuzu[6]=entry6;
    shuzu[7]=entry7;
    shuzu[8]=entry8;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforb3),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
void lookforb3(GtkWidget *button,GtkWidget *shuzu[10])
{
    int k;
    char *temp=NULL;
    sqlite3 *pdb = NULL;
    sqlite3_open("db_car1.sql",&pdb);
    char *sql = "insert into inform values('";
    char *ErrMsg = 0;
    int result,i,j;
    int sign = 1;
    char *szErrMsg;
    char **dbResult=NULL;

    char *sql1 = "select * from inform where  punishNo ='00001'";
    char *ErrMsg1 = 0;
    int nRow=0,nCloumn;
    GtkEntry *entry = (GtkEntry*)shuzu[1];
    const gchar *punishNo = gtk_entry_get_text(entry);
    const gchar *punishNo1 = gtk_entry_get_text(entry);
    sql1 =str_str("select * from inform where punishNo ='",punishNo1);
    sql1 =str_str(sql1,"'");
    sqlite3_get_table(pdb,sql1,&dbResult,&nRow,&nCloumn,&ErrMsg1);
    if(nRow==1)
    {
        if(strlen(punishNo) == 0)
            sign = 0;
        else
        {
            sql =str_str(sql,punishNo);
            sql =str_str(sql,"','");
        }
        entry = (GtkEntry*)shuzu[2];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        {
            sql =str_str(sql,dbResult[nCloumn+1]);
            sql =str_str(sql,"','");
        }
        else
        {
            sql =str_str(sql,punishNo);
            sql =str_str(sql,"','");            
        }
        entry = (GtkEntry*)shuzu[3];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+2];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[4];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+3];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[5];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+4];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[6];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+5];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[7];
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+6];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"','");
        entry = (GtkEntry*)shuzu[8] ;
        punishNo = gtk_entry_get_text(entry);
        if(strlen(punishNo)==0)
        punishNo = dbResult[nCloumn+7];
        sql =str_str(sql,punishNo);
        sql =str_str(sql,"')");
        printf("%s\n",sql);
    }
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
        sql1="delete from inform where punishNo = '";
        sql1=str_str(sql1,punishNo1);
        sql1=str_str(sql1,"'");
        printf("%s\n",sql1);
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
//删除通知书信息
void callback_buttonb4(GtkWidget *button)
{
    GtkWidget *window;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *button1;
    GtkWidget *box;
    GtkWidget *fixed;
    GtkWidget *entry;
    GtkWidget *shuzu[3];
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title((GtkWindow*)window,"删除通知书信息");
    gtk_widget_set_usize(window,400,600);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    box = gtk_hbox_new(TRUE,5);
    entry = gtk_entry_new_with_max_length(20);
    button1 = gtk_button_new_with_label("确定");
    label1 = gtk_label_new("请输入你想删除的通知书的编号");
    label2 = gtk_label_new("编号");
    gtk_fixed_put(GTK_FIXED(fixed),label1,60,80);
    gtk_fixed_put(GTK_FIXED(fixed),label2,60,140);
    gtk_fixed_put(GTK_FIXED(fixed),button1,100,200);
    gtk_fixed_put(GTK_FIXED(fixed),entry,120,140);
    shuzu[0] = window;
    shuzu[1] = entry;
    shuzu[2] = button1;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(lookforb4),&shuzu);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();

}
//删除通知书的数据库操作
void lookforb4(GtkWidget *button,GtkWidget *shuzu[10])
{
     int k;
     char *temp=NULL;
     sqlite3 *pdb = NULL;
     sqlite3_open("db_car1.sql",&pdb);
     char *sql = "delete from inform where punishNo = '";
     char *ErrMsg = 0;
     int result,i,j;
     int sign = 1;
     char *szErrMsg;
     char **dbResult=NULL;
     GtkEntry *entry = (GtkEntry*)shuzu[1];
     const gchar *punishNo = gtk_entry_get_text(entry);
     if(strlen(punishNo) == 0)
     {
        sign = 0;
     }
     if(sign==0)
     {
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"错误提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("没有该通知书，无法删除！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                               
     }
     else
     {
         sql = str_str(sql,punishNo);
         sql = str_str(sql,"'");
         printf("%s\n",sql);
         sqlite3_exec(pdb,sql,0,0,&szErrMsg);
         GtkWidget *dialog;
         GtkWidget *label;
         dialog = gtk_dialog_new();
         gtk_window_set_title(GTK_WINDOW(dialog),"操作提示");
         gtk_widget_set_usize(dialog,200,200);
         label = gtk_label_new("删除成功！");
         gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,TRUE,TRUE,0);
         g_signal_connect(G_OBJECT(dialog),"delete_event",G_CALLBACK(release_resourse),NULL);
         gtk_widget_show_all(dialog);
         gtk_main();                                                   
     }
}

