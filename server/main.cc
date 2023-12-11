/*
 * @Author: jk_zeng@qq.com
 * @Date: 2023-11-28 16:09:59
 * @LastEditors: jk_zeng@qq.com
 * @LastEditTime: 2023-12-08 17:15:48
 * @FilePath: /socket-server/server/main.cc
 * @Description: 
 * 
 * Copyright (c) 2023 by ${jk_zeng@qq.com}, All Rights Reserved. 
 */
#include "socket_server.h"
using namespace cloud;
int main(){
    SocketServer ss;

    ss.SeverListen();
    
    return 0;
}
