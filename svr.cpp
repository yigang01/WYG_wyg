/*************************************************************************
    > File Name: svr.cpp
    > Author:  WYG
    > Mail:  1769703801@qq.com 
    > Created Time: 2020年06月23日 星期二 12时25分14秒

    服务端
    1、创建套接字
    2、绑定地址信息
    3、监听
    4、获取链接
    5、接收数据
    6、发送数据
    7、关闭套接字
 ************************************************************************/
#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<gtk/gtk.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
GtkWidget *text_view; 
GtkTextBuffer *buffer; 
GtkTextIter *Iter; 
int b[1];
char *table[7]={"","","","","","",""};
char *str_str(char *A,char *B);
static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data);
void callback_button(GtkWidget *button,GtkWidget *entry[3]);

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


void button_connection(GtkWidget *button,GtkWidget *shuzu[3])//创建套接字
{
    //创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return;
    }
    //允许地址端口重复使用
    const int a = 1;
    int ret1 = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&a,sizeof(a));
    if(ret1 < 0)
    {
        perror("setsockopt");
        return;
    }
    //绑定地址信息
    struct sockaddr_in svr_addr;
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(19996);
    svr_addr.sin_addr.s_addr = inet_addr("192.168.23.128");
    int ret = bind(sockfd,(struct sockaddr*)&svr_addr,sizeof(svr_addr));
    if(ret < 0)
    {
        perror("bind");
        return;
    }
    //监听
    ret = listen(sockfd,5);
    if(ret < 0)
    {
        perror("listen");
        return;
    }
    //连接
    struct sockaddr_in cli_addr;
    socklen_t addrlen = sizeof(cli_addr);
    int newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&addrlen);
    b[0] = newsockfd;
    if(newsockfd < 0)
    {
        perror("accept");
        return;
    }
    printf("服务端连接成功\n");
    table[0] = "当前登录ip：192.168.23.128";
    table[1] = "端口号：50345";
    gtk_label_set_text(GTK_LABEL(shuzu[1]),table[0]);
    //gtk_widget_show_all(shuzu[3]);
    gtk_label_set_text(GTK_LABEL(shuzu[2]),table[1]);
    gtk_widget_show_all(shuzu[2]);


    char str2[1024] = {0};
    char name3[10] = "对方：";
    //5、接收数据
    recv(newsockfd,str2,sizeof(str2)-1,0);
    printf("接收成功\n");
    printf("我已成功接受客户端数据：%s\n",str2);
    printf("lalal\n");
    GtkTextIter start,end; 
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,name3,strlen(name3));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,str2,strlen(str2));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,"\n",1);
}
void communication(GtkWidget *button,GtkWidget *shuzu[3]) 
{

    GtkTextIter start,end; 
    GtkEntry *entry1 = (GtkEntry*)shuzu[0];
    const gchar *buf = gtk_entry_get_text(entry1);
    char name2[10] = "自己：";
    //6、发送数据
    send(b[0],buf,sizeof(buf),0);
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,name2,strlen(name2));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,buf,strlen(buf));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,"\n",1);
    printf("发送成功\n");
    char str3[1024] = {0};
    char name1[10] = "对方：";
    //5、接收数据
    recv(b[0],str3,sizeof(str3)-1,0);
    printf("接收成功\n");
    printf("我已成功接受客户端数据：%s\n",str3);
    printf("lalal\n");
    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer),&start,&end);
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,name1,strlen(name1));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,str3,strlen(str3));
    gtk_text_buffer_insert(GTK_TEXT_BUFFER(buffer),&end,"\n",1);
}
int main(int argc,char *argv[])
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
    gtk_window_set_title((GtkWindow*)window,"QQ1");//标题
    gtk_widget_set_usize(window,400,280);
    gtk_container_set_border_width(GTK_CONTAINER(window),15);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    chang_background(window, 400, 280, "2.jpg");
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);
    label = gtk_label_new("QQ号");
    label1 = gtk_label_new("密码");
    button1 = gtk_button_new_with_label("登录");
    entry1 = gtk_entry_new_with_max_length(20);
    entry2 = gtk_entry_new_with_max_length(20);
    gtk_fixed_put(GTK_FIXED(fixed),label,113,145);
    gtk_fixed_put(GTK_FIXED(fixed),label1,113,185);
    gtk_fixed_put(GTK_FIXED(fixed),button1,210,222);
    gtk_fixed_put(GTK_FIXED(fixed),entry1,150,140);
    gtk_fixed_put(GTK_FIXED(fixed),entry2,150,180);
    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);//设置密码不可见，entry2是一个编辑密码行，所以肯定不可见
    entry[0] = entry1;
    entry[1] = entry2;
    entry[2] = window;
    g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(callback_button),&entry);
    g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
void callback_button(GtkWidget *button,GtkWidget *entry[3])
{
    const gchar *name = NULL;
    const gchar *password = NULL;
    gboolean btn_state;
    name = gtk_entry_get_text((GtkEntry *)entry[0]);
    password = gtk_entry_get_text((GtkEntry *)entry[1]);
    if(strcmp(name,"1769703801") == 0 && strcmp(password,"123456wyg") == 0)
    {
        GtkWidget *window;
        GtkWidget *fixed1;
        GtkWidget *label1;
        GtkWidget *label2;
        GtkWidget *button1;
        GtkWidget *button2;
        GtkWidget *label3;
        GtkWidget *label4;
        GtkWidget *entry1;
        GtkWidget *shuzu[4];
        //GtkWidget *dialog;

        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title((GtkWindow*)window,"客户端1");
        gtk_widget_set_usize(window,500,400);
        gtk_container_set_border_width(GTK_CONTAINER(window),15);
        chang_background(window, 500, 400, "0.jpg");
        entry1 = gtk_entry_new_with_max_length(140);
        fixed1 = gtk_fixed_new();
        label1 = gtk_label_new("输入信息：");
        label2 = gtk_label_new("点击登录按钮连接服务器：");
        label3 = gtk_label_new("当前登录ip：");
        label4 = gtk_label_new("端口号：");
        button1 = gtk_button_new_with_label("登录");
        button2 = gtk_button_new_with_label("发送");
        gtk_container_add(GTK_CONTAINER(window),fixed1);
        gtk_fixed_put(GTK_FIXED(fixed1),entry1,150,240);
        gtk_fixed_put(GTK_FIXED(fixed1),label1,50,250);
        gtk_fixed_put(GTK_FIXED(fixed1),label2,20,20);
        gtk_fixed_put(GTK_FIXED(fixed1),button1,200,12);

        gtk_fixed_put(GTK_FIXED(fixed1),button2,350,240);
        gtk_fixed_put(GTK_FIXED(fixed1),label3,20,60);
        gtk_fixed_put(GTK_FIXED(fixed1),label4,300,60);

        text_view = gtk_text_view_new();
        gtk_widget_set_size_request(text_view,400,130); 
        gtk_fixed_put(GTK_FIXED(fixed1),text_view,20,100);
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

        shuzu[0] = entry1;
        shuzu[1] = label3;
        shuzu[2] = label4;
        g_signal_connect(G_OBJECT(button1),"pressed",G_CALLBACK(button_connection),&shuzu);
        //button_connection();
        //int newsockfd = button_connection();
        //gtk_signal_connect(GTK_OBJECT(button2),"clicked",GTK_SIGNAL_FUNC(button_event),&shuzu);
        g_signal_connect(G_OBJECT(button2),"pressed",G_CALLBACK(communication),&shuzu);
        g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(release_resourse),NULL);
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
static gboolean release_resourse(GtkWidget *widget,GdkEvent *event,gpointer data)
{
    gtk_main_quit();
    return FALSE;
}
