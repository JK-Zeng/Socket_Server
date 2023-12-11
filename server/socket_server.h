/*
 * @Author: jk_zeng@qq.com
 * @Date: 2023-12-07 17:00:51
 * @LastEditors: jk_zeng@qq.com
 * @LastEditTime: 2023-12-08 15:50:54
 * @FilePath: /socket-server/server/socket_server.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${jk_zeng@qq.com}, All Rights Reserved. 
 */
#include <iostream>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


namespace cloud{

class SocketServer{
public:
    struct SocketsPama {
        int fd;
        struct sockaddr_in socket_addr;
        int linking_num = 0;
    };

    SocketServer();
    ~SocketServer();

    void SeverListen();

private:
    fd_set selectfds;
    std::map<std::string, SocketsPama> sockets;

};

}

