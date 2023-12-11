/*
 * @Author: jk_zeng@qq.com
 * @Date: 2023-12-07 17:00:37
 * @LastEditors: jk_zeng@qq.com
 * @LastEditTime: 2023-12-08 17:17:58
 * @FilePath: /socket-server/server/socket_server.cc
 * @Description: 
 * 
 * Copyright (c) 2023 by ${jk_zeng@qq.com}, All Rights Reserved. 
 */
#include "socket_server.h"

namespace cloud{

SocketServer::SocketServer(){
    FD_ZERO(&selectfds);
    for (int i = 0; i < 2; i++)
    {
        SocketsPama socket_pama;
        socket_pama.fd = socket(AF_INET, SOCK_STREAM, 0);
        socket_pama.socket_addr.sin_family = AF_INET;
        socket_pama.socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        socket_pama.socket_addr.sin_port = htons(8880+i);
        if(bind(socket_pama.fd, (struct sockaddr *)&socket_pama.socket_addr,sizeof(struct sockaddr)) != 0){
            std::cout << "bind error!" << std::endl;
            return ;
        }
        if(listen(socket_pama.fd, 5) != 0){
            std::cout << "call listen fail!" << std::endl;
            return ;
        }
        FD_SET(socket_pama.fd,&selectfds);
        std::string key = "serverfd-" + std::to_string(8880+i);
        sockets.insert(std::pair<std::string, SocketsPama>(key, socket_pama));
    }
    
}

SocketServer::~SocketServer(){}

void SocketServer::SeverListen(){
    while (1)
    {
        fd_set tempfds = selectfds;
        int result = select(FD_SETSIZE, &tempfds, NULL, NULL, NULL);
        for (std::map<std::string, SocketsPama>::iterator it = sockets.begin(); it != sockets.end(); it++)
        {
            if (FD_ISSET(it->second.fd, &tempfds)){
                if (it->first.substr(0, 6) == "server")
                {
                    SocketsPama socket_pama;
                    int sockaddr_in_size = sizeof(struct sockaddr_in);
                    socket_pama.fd = accept(it->second.fd, 
                                            (struct sockaddr *)(&socket_pama.socket_addr), 
                                            (socklen_t *)(&sockaddr_in_size));
                    if(socket_pama.fd == -1){
                        std::cout << "connect fail!" << std::endl;
                    }else{
                        std::cout << "Client " << inet_ntoa(socket_pama.socket_addr.sin_addr) 
                                << " has connected to port " << it->first.substr(9, 4) << std::endl;
                    }
                    FD_SET(socket_pama.fd, &selectfds);
                    std::string key = "clientfd-" + it->first.substr(9, 4) + "-" + std::to_string(it->second.linking_num);
                    sockets.insert(std::pair<std::string, SocketsPama>(key, socket_pama));
                    it->second.linking_num++;
                }else if(it->first.substr(0, 6) == "client"){
                    char buffer[BUFSIZ];
                    memset(buffer, '\0', BUFSIZ);
                    int iret = recv(it->second.fd, buffer, BUFSIZ, 0);
                    if (iret == 0){
                        std::cout << it->first <<" connect break!" << std::endl;
                        close(it->second.fd);
                        FD_CLR(it->second.fd,&selectfds);
                        sockets.erase(it->first);
                        std::map<std::string, SocketsPama>::iterator itserver = sockets.find(
                                    "serverfd-" + it->first.substr(9, 4));
                        itserver->second.linking_num--;
                        break;
                    }else{
                        std::cout <<" recv " << it->first <<" message:" << buffer << std::endl;
                        send(it->second.fd, buffer, strlen(buffer), 0);
                    }
                }
            }
        }
    }
}
}    //namespace cloud