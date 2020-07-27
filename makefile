all:cli svr
cli:cli.cpp
	g++ $^ -o $@ `pkg-config --cflags --libs gtk+-2.0` -lsqlite3 -L/usr/local/sqlite3/lib -g
svr:svr.cpp
	g++ $^ -o $@ `pkg-config --cflags --libs gtk+-2.0` -lsqlite3 -L/usr/local/sqlite3/lib -g
