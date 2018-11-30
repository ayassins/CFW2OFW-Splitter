#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qpair.h>
#include <QtCore/qmap.h>
#include <QtCore/qdebug.h>

class PARAM
{
public:
	PARAM(QString path);
	~PARAM();
	QString Account_ID();
	bool Account_ID(QByteArray value);
	QString Analog_Mode();
	bool Analog_Mode(QByteArray value);
	QString App_Ver();
	bool App_Ver(QByteArray value);
	QString Category();
	bool Category(QByteArray value);
	QString Content_ID();
	bool Content_ID(QByteArray value);
	QString Detail();
	bool Detail(QByteArray value);
	QString Gamedata_ID();
	bool Gamedata_ID(QByteArray value);
	QString License();
	bool License(QByteArray value);
	QString NP_Communication_ID();
	bool NP_Communication_ID(QByteArray value);
	QString NPcommid();
	bool NPcommid(QByteArray value);
	QString PADDING();
	bool PADDING(QByteArray value);
	QString Params();
	bool Params(QByteArray value);
	QString Params2();
	bool Params2(QByteArray value);
	QString Patch_File();
	bool Patch_File(QByteArray value);
	QString Ps3_System_Ver();
	bool Ps3_System_Ver(QByteArray value);
	QString Savedata_detail();
	bool Savedata_detail(QByteArray value);
	QString Savedata_Directory();
	bool Savedata_Directory(QByteArray value);
	QString Savedata_File_List();
	bool Savedata_File_List(QByteArray value);
	QString Savedata_List_Param();
	bool Savedata_List_Param(QByteArray value);
	QString Savedata_Params();
	bool Savedata_Params(QByteArray value);
	QString Savedata_Title();
	bool Savedata_Title(QByteArray value);
	QString Sub_Title();
	bool Sub_Title(QByteArray value);
	QString Target_App_Ver();
	bool Target_App_Ver(QByteArray value);
	QString Title();
	bool Title(QByteArray value);
	QString Title_ID();
	bool Title_ID(QByteArray value);
	QString Title_xx();
	bool Title_xx(QByteArray value);
	QString TitleID0xx();
	bool TitleID0xx(QByteArray value);
	QString Version();
	bool Version(QByteArray value);
	QString Xmb_Apps();
	bool Xmb_Apps(QByteArray value);
private:
	QFile f;
	QMap<int, QPair<int, QPair<int, int>>> paramDict;
	bool setKeyValue(QByteArray key, QByteArray value);
	QString getKeyValue(QByteArray key);
};

