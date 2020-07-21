#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>
#include <stdlib.h>
#include <windows.h>
#include "dataProto.pb.h"
#include "dataDeclaration.h"
#include "ZipPack.h"

#define BUF_SIZE 1024
#pragma comment(lib,"ws2_32.lib")

void dataTransfer()
{
	WSADATA wsd; //WSADATA变量，用于初始化Windows Socket 
	SOCKET sServer; //服务器socket，用于监听客户端请求
	SOCKET sClient; //客户端socket，用于实现与客户端的通信
	int retVal; //调用各种socket函数的返回值

	//初始化Socket环境
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WASStartup failed !" << endl;
		WSACleanup();
		return;
	}

	//创建用于监听的Socket
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sServer == INVALID_SOCKET)
	{
		cout << "socket failed !" << endl;
		closesocket(sServer);
		WSACleanup();
		return;
	}

	//设置服务器Socket地址
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = htons(9990);
	addrServ.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定Sockets Server到某个IP和端口（IP标识主机，端口标识通信进程）
	retVal = ::bind(sServer, (const struct sockaddr *)&addrServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		cout << "bind failed !" << endl;
		closesocket(sServer);
		WSACleanup();
		return;
	}

	//在Socket Server上进行监听
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		cout << "listen failed !" << endl;
		closesocket(sServer);
		WSACleanup();
		return;
	}

	//接受来自客户端的请求
	cout << "TCP Server Start..." << endl;
	SOCKADDR_IN addrClient; //客户端地址
	int addrClientLen = sizeof(addrClient);
	//如果客户端没有启动，那么程序一直停留在该函数处
	sClient = accept(sServer, (sockaddr FAR *)&addrClient, &addrClientLen);
	if (INVALID_SOCKET == sClient)
	{
		cout << "accept failed !" << endl;
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return;
	}
	int n = 0;
	while (true)
	{
		Client2Server client2Server;

		char buf_recv[BUF_SIZE];
		retVal = recv(sClient, buf_recv, BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "recv failed !" << endl;
			closesocket(sServer);
			closesocket(sClient);
			WSACleanup();
			return;
		}
		std::string str_recv;
		str_recv.assign(buf_recv, BUF_SIZE);
		client2Server.ParseFromString(str_recv);
		emergeStop = client2Server.emergestop();
		enableState = client2Server.enablestate();
		operateMode = client2Server.operatemode();
		activeState = client2Server.activestate();
		runState = client2Server.runstate();
		step = client2Server.step();
		jog = client2Server.jog();
		coordinate = client2Server.coordinate();
		upOrDown = client2Server.upordown();
		ovr = client2Server.ovr();
		progLine = client2Server.progline();
		transferZip = client2Server.transferzip();
		zipSize = client2Server.zipsize();
		projName = client2Server.projname();
		varProgName = client2Server.varprogname();

		//当transferZip为1是，表示示教器将要传文件压缩包过来
		if (transferZip == 1)
		{
			int size, netSize;
			if ((size = send(sClient, "OK", 2, 0)) < 0) 
			{
				cout << "send failed !" << endl;
				closesocket(sServer);
				closesocket(sClient);
				WSACleanup();
				exit(1);
			}

			FILE *fp = fopen("prog_var_xml.zip", "wb");
			if (fp == NULL) 
			{
				closesocket(sServer);
				closesocket(sClient);
				WSACleanup();
				return;
			}

			int fileSize2 = 0;
			char fileBuf[BUF_SIZE];
			while (memset(fileBuf, 0, sizeof(fileBuf)), (size = recv(sClient, fileBuf, sizeof(fileBuf), 0)) > 0) 
			{
				int size2 = 0;
				while (size2 < size) 
				{
					if ((netSize = fwrite(fileBuf + size2, 1, size - size2, fp)) < 0) 
					{
						closesocket(sServer);
						closesocket(sClient);
						WSACleanup();
						exit(1);
					}
					size2 += netSize;
				}
				fileSize2 += size;
				if (fileSize2 >= zipSize) 
				{
					break;
				}
			}
			if ((size = send(sClient, "OK", 2, 0)) < 0)
			{
				cout << "send failed !" << endl;
				closesocket(sServer);
				closesocket(sClient);
				WSACleanup();
				exit(1);
			}
			fclose(fp);
			//解压
			ZipPack::UnPackZipToDir(L"prog_var_xml.zip", L"prog_var_xml");
		}

		//Server2Client server2Client;
		////注意一下几个变量要通过指针访问，否则会出错
		//AxisPos *axisPos = new AxisPos;
		//CartPos *cartPos = new CartPos;
		//DrivePos *drivePos = new DrivePos;
		//axisPos->set_a1(::axisPos.a1);
		//axisPos->set_a2(::axisPos.a2);
		//axisPos->set_a3(::axisPos.a3);
		//axisPos->set_a4(::axisPos.a4);
		//axisPos->set_a5(::axisPos.a5);
		//axisPos->set_a6(::axisPos.a6);
		//cartPos->set_x(::cartPos.x);
		//cartPos->set_y(::cartPos.y);
		//cartPos->set_z(::cartPos.z);
		//cartPos->set_a(::cartPos.a);
		//cartPos->set_b(::cartPos.b);
		//cartPos->set_c(::cartPos.c);
		//drivePos->set_drive1(::drivePos.drive1);
		//drivePos->set_drive2(::drivePos.drive2);
		//drivePos->set_drive3(::drivePos.drive3);
		//drivePos->set_drive4(::drivePos.drive4);
		//drivePos->set_drive5(::drivePos.drive5);
		//drivePos->set_drive6(::drivePos.drive6);
		//server2Client.set_allocated_axispos(axisPos);
		//server2Client.set_allocated_cartpos(cartPos);
		//server2Client.set_allocated_driverpos(driverPos);
		//server2Client.set_stopprog(stopProg);
		//server2Client.set_endprog(endProg);
		//server2Client.set_hasreachsingularity(::hasReachSingularity);
		//InfoReport *infoReport = server2Client.add_inforeport();
		//infoReport->set_level(0);
		//infoReport->set_content("notice");

		Server2Client server2Client;
		//注意一下几个变量要通过指针访问，否则会出错
		AxisPos *axisPos = server2Client.mutable_axispos();
		CartPos *cartPos = server2Client.mutable_cartpos();
		DrivePos *drivePos = server2Client.mutable_drivepos();
		axisPos->set_a1(::axisPos.a1);
		axisPos->set_a2(::axisPos.a2);
		axisPos->set_a3(::axisPos.a3);
		axisPos->set_a4(::axisPos.a4);
		axisPos->set_a5(::axisPos.a5);
		axisPos->set_a6(::axisPos.a6);
		cartPos->set_x(::cartPos.x);
		cartPos->set_y(::cartPos.y);
		cartPos->set_z(::cartPos.z);
		cartPos->set_a(::cartPos.a);
		cartPos->set_b(::cartPos.b);
		cartPos->set_c(::cartPos.c);
		drivePos->set_d1(::drivePos.d1);
		drivePos->set_d2(::drivePos.d2);
		drivePos->set_d3(::drivePos.d3);
		drivePos->set_d4(::drivePos.d4);
		drivePos->set_d5(::drivePos.d5);
		drivePos->set_d6(::drivePos.d6);
		server2Client.set_activeprog(activeProg);
		server2Client.set_runprog(runProg);
		server2Client.set_hasreachsingularity(::hasReachSingularity);
		InfoReport *infoReport = server2Client.add_inforeport();
		infoReport->set_level(0);
		infoReport->set_content("notice");

		std::string str_send;
		server2Client.SerializeToString(&str_send);

		Sleep(200); //等待一段时间，避免数据的发送和接收响应不过来

		char buf_send[BUF_SIZE];
		for (int i = 0; i < str_send.length(); i++)
		{
			buf_send[i] = str_send[i];
		}
		retVal = send(sClient, str_send.data(), BUF_SIZE, 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed !" << endl;
			closesocket(sServer);
			closesocket(sClient);
			WSACleanup();
			return;
		}
		n++;
	}
	
	//释放资源
	closesocket(sServer);
	closesocket(sClient);
	WSACleanup();
}

