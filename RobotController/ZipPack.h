#pragma once
#include <iostream>

namespace ZipPack
{
	//* �����ļ����µ������ļ���zip
	//targetPath: ��ʼĿ¼
	//currentDir: ��ǰ����������Ŀ¼
	//hZip: HZIP �����ַ
	void BrowseFileToZip(std::wstring targetDir, std::wstring currentDir, void* hZip);

	//* ��Ŀ¼���Ϊzip
	//targetPath: Ҫ�����Ŀ¼
	//dstZip: ���֮���zip�ļ�λ��
	bool PackDirToZip(std::wstring targetDir, std::wstring dstZip);

	//* ��zip�ļ���ѹ����Ӧ��Ŀ¼
	//targetZip:��Ҫ��ѹ���ļ�
	//dstPath:��ѹ֮����ļ�����Ŀ¼(���Ŀ¼���Ѵ�����ͬ�ļ���Ḳ��)
	bool UnPackZipToDir(std::wstring targetZip, std::wstring dstPath, std::string psw="");
};

