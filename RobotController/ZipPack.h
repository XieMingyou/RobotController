#pragma once
#include <iostream>

namespace ZipPack
{
	//* 遍历文件夹下的所有文件到zip
	//targetPath: 起始目录
	//currentDir: 当前遍历所处的目录
	//hZip: HZIP 句柄地址
	void BrowseFileToZip(std::wstring targetDir, std::wstring currentDir, void* hZip);

	//* 将目录打包为zip
	//targetPath: 要打包的目录
	//dstZip: 打包之后的zip文件位置
	bool PackDirToZip(std::wstring targetDir, std::wstring dstZip);

	//* 将zip文件解压到对应的目录
	//targetZip:需要解压的文件
	//dstPath:解压之后的文件所在目录(如果目录内已存在相同文件则会覆盖)
	bool UnPackZipToDir(std::wstring targetZip, std::wstring dstPath, std::string psw="");
};

