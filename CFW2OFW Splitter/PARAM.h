#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qpair.h>
#include <QtCore/qmap.h>

class PARAM
{
public:
	PARAM(const QString & path);
	~PARAM();
	bool isValidParam();
	QString Account_ID();
	bool Account_ID(QString value);
	QString Analog_Mode();
	bool Analog_Mode(QString value);
	QString App_Ver();
	bool App_Ver(QString value);
	QString Category();
	bool Category(QString value);
	QString Content_ID();
	bool Content_ID(QString value);
	QString Detail();
	bool Detail(QString value);
	QString Gamedata_ID();
	bool Gamedata_ID(QString value);
	QString License();
	bool License(QString value);
	QString NP_Communication_ID();
	bool NP_Communication_ID(QString value);
	QString NPcommid();
	bool NPcommid(QString value);
	QString PADDING();
	bool PADDING(QString value);
	QString Params();
	bool Params(QString value);
	QString Params2();
	bool Params2(QString value);
	QString Patch_File();
	bool Patch_File(QString value);
	QString Ps3_System_Ver();
	bool Ps3_System_Ver(QString value);
	QString Savedata_detail();
	bool Savedata_detail(QString value);
	QString Savedata_Directory();
	bool Savedata_Directory(QString value);
	QString Savedata_File_List();
	bool Savedata_File_List(QString value);
	QString Savedata_List_Param();
	bool Savedata_List_Param(QString value);
	QString Savedata_Params();
	bool Savedata_Params(QString value);
	QString Savedata_Title();
	bool Savedata_Title(QString value);
	QString Sub_Title();
	bool Sub_Title(QString value);
	QString Target_App_Ver();
	bool Target_App_Ver(QString value);
	QString Title();
	bool Title(QString value);
	QString Title_ID();
	bool Title_ID(QString value);
	QString Title_xx();
	bool Title_xx(QString value);
	QString TitleID0xx();
	bool TitleID0xx(QString value);
	QString Version();
	bool Version(QString value);
	QString Xmb_Apps();
	bool Xmb_Apps(QString value);
private:
	QFile f;
	quint32 magic, version;
	QMap<int, QPair<int, QPair<int, int>>> paramDict;
	bool isValidSignature();
	bool isValidVersion();
	bool setKeyValue(QString key, QString value);
	QString getKeyValue(QString key);
};

