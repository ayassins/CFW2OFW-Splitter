#include "PARAM.h"



PARAM::PARAM(QString path)
{
	quint32 magic, version, key_table_start, data_table_start, tables_entries, data_len, data_max_len, data_offset;
	quint16 key_offset, data_fmt;
	f.setFileName(path);
	f.open(QFile::ReadWrite);
	QDataStream in(&f);
	in.setByteOrder(QDataStream::LittleEndian);
	in >> magic >> version >> key_table_start >> data_table_start >> tables_entries;
	for (int i = 0; i < tables_entries; i++)
	{
		in >> key_offset >> data_fmt >> data_len >> data_max_len >> data_offset;
		paramDict.insert(i, qMakePair(key_offset + key_table_start, qMakePair(data_offset + data_table_start, data_max_len)));
	}
}

bool PARAM::setKeyValue(QByteArray key, QByteArray value)
{
	for (int i = 0; i < paramDict.count(); i++)
	{
		f.seek(paramDict[i].first);
		if (key != f.read(key.size())) continue;
		f.seek(paramDict[i].second.first);
		if (value.size() <= paramDict[i].second.second)
		{
			QByteArray key_value;
			key_value.fill(0, paramDict[i].second.second);
			key_value.insert(0, value);
			key_value.resize(paramDict[i].second.second);
			return (f.write(key_value));
		}
	}
	return false;
}

QString PARAM::getKeyValue(QByteArray key)
{
	for (int i = 0; i < paramDict.count(); i++)
	{
		f.seek(paramDict[i].first);
		if (key != f.read(key.size())) continue;
		f.seek(paramDict[i].second.first);
		return f.read(paramDict[i].second.second);
	}
	return QString();
}

PARAM::~PARAM()
{
	f.close();
}


QString PARAM::Account_ID()
{
	return getKeyValue("ACCOUNT_ID");
}


bool PARAM::Account_ID(QByteArray value)
{
	return setKeyValue("ACCOUNT_ID", value);
}

QString PARAM::Analog_Mode()
{
	return getKeyValue("ANALOG_MODE");
}

bool PARAM::Analog_Mode(QByteArray value)
{
	return setKeyValue("ANALOG_MODE", value);
}

QString PARAM::App_Ver()
{
	return getKeyValue("APP_VER");
}

bool PARAM::App_Ver(QByteArray value)
{
	return setKeyValue("APP_VER", value);
}

QString PARAM::Category()
{
	return getKeyValue("CATEGORY");
}
bool PARAM::Category(QByteArray value)
{
	return setKeyValue("CATEGORY", value);
}


QString PARAM::Content_ID()
{
	return getKeyValue("CONTENT_ID");
}

bool PARAM::Content_ID(QByteArray value)
{
	return setKeyValue("CONTENT_ID", value);
}

QString PARAM::Detail()
{
	return getKeyValue("DETAIL");
}
bool PARAM::Detail(QByteArray value)
{
	return setKeyValue("DETAIL", value);
}


QString PARAM::Gamedata_ID()
{
	return getKeyValue("GAMEDATA_ID");
}

bool PARAM::Gamedata_ID(QByteArray value)
{
	return setKeyValue("GAMEDATA_ID", value);
}

QString PARAM::License()
{
	return getKeyValue("LICENSE");
}

bool PARAM::License(QByteArray value)
{
	return setKeyValue("LICENSE", value);
}

QString PARAM::NP_Communication_ID()
{
	return getKeyValue("NP_COMMUNICATION_ID");
}

bool PARAM::NP_Communication_ID(QByteArray value)
{
	return setKeyValue("NP_COMMUNICATION_ID", value);
}

QString PARAM::NPcommid()
{
	return getKeyValue("NPCOMMID");
}

bool PARAM::NPcommid(QByteArray value)
{
	return setKeyValue("NPCOMMID", value);
}

QString PARAM::PADDING()
{
	return getKeyValue("PADDING");
}

bool PARAM::PADDING(QByteArray value)
{
	return setKeyValue("PADDING", value);
}

QString PARAM::Params()
{
	return getKeyValue("PARAMS");
}

bool PARAM::Params(QByteArray value)
{
	return setKeyValue("PARAMS", value);
}

QString PARAM::Params2()
{
	return getKeyValue("PARAMS2");
}

bool PARAM::Params2(QByteArray value)
{
	return setKeyValue("PARAMS2", value);
}

QString PARAM::Patch_File()
{
	return getKeyValue("PATCH_FILE");
}

bool PARAM::Patch_File(QByteArray value)
{
	return setKeyValue("PATCH_FILE", value);
}

QString PARAM::Ps3_System_Ver()
{
	return getKeyValue("PS3_SYSTEM_VER");
}

bool PARAM::Ps3_System_Ver(QByteArray value)
{
	return setKeyValue("PS3_SYSTEM_VER", value);
}

QString PARAM::Savedata_detail()
{
	return getKeyValue("SAVEDATA_DETAIL");
}
bool PARAM::Savedata_detail(QByteArray value)
{
	return setKeyValue("SAVEDATA_DETAIL", value);
}


QString PARAM::Savedata_Directory()
{
	return getKeyValue("SAVEDATA_DIRECTORY");
}

bool PARAM::Savedata_Directory(QByteArray value)
{
	return setKeyValue("SAVEDATA_DIRECTORY", value);
}

QString PARAM::Savedata_File_List()
{
	return getKeyValue("SAVEDATA_FILE_LIST");
}

bool PARAM::Savedata_File_List(QByteArray value)
{
	return setKeyValue("SAVEDATA_FILE_LIST", value);
}

QString PARAM::Savedata_List_Param()
{
	return getKeyValue("SAVEDATA_LIST_PARAM");
}

bool PARAM::Savedata_List_Param(QByteArray value)
{
	return setKeyValue("SAVEDATA_LIST_PARAM", value);
}

QString PARAM::Savedata_Params()
{
	return getKeyValue("SAVEDATA_PARAMS");
}
bool PARAM::Savedata_Params(QByteArray value)
{
	return setKeyValue("SAVEDATA_PARAMS", value);
}

QString PARAM::Savedata_Title()
{
	return getKeyValue("SAVEDATA_TITLE");
}

bool PARAM::Savedata_Title(QByteArray value)
{
	return setKeyValue("SAVEDATA_TITLE", value);
}


QString PARAM::Sub_Title()
{
	return getKeyValue("SUB_TITLE");
}

bool PARAM::Sub_Title(QByteArray value)
{
	return setKeyValue("SUB_TITLE", value);
}

QString PARAM::Target_App_Ver()
{
	return getKeyValue("TARGET_APP_VER");
}


bool PARAM::Target_App_Ver(QByteArray value)
{
	return setKeyValue("TARGET_APP_VER", value);
}


QString PARAM::Title()
{
	return getKeyValue("TITLE");
}


bool PARAM::Title(QByteArray value)
{
	return setKeyValue("TITLE", value);
}


QString PARAM::Title_ID()
{
	return getKeyValue("TITLE_ID");
}


bool PARAM::Title_ID(QByteArray value)
{
	return setKeyValue("TITLE_ID", value);
}


QString PARAM::Title_xx()
{
	return getKeyValue("TITLE_xx");
}


bool PARAM::Title_xx(QByteArray value)
{
	return setKeyValue("TITLE_xx", value);
}


QString PARAM::TitleID0xx()
{
	return getKeyValue("TITLEID0xx");
}


bool PARAM::TitleID0xx(QByteArray value)
{
	return setKeyValue("TITLEID0xx", value);
}


QString PARAM::Version()
{
	return getKeyValue("VERSION");
}


bool PARAM::Version(QByteArray value)
{
	return setKeyValue("VERSION", value);
}


QString PARAM::Xmb_Apps()
{
	return getKeyValue("XMB_APPS");
}


bool PARAM::Xmb_Apps(QByteArray value)
{
	return setKeyValue("XMB_APPS", value);
}


//ACCOUNT_ID 				utf8 - S
//ACCOUNTID 				utf8
//ANALOG_MODE				int32
//APP_VER 				utf8
//ATTRIBUTE 				int32
//BOOTABLE 				int32
//CATEGORY 				utf8
//CONTENT_ID				utf8
//DETAIL 					utf8
//GAMEDATA_ID				utf8
//ITEM_PRIORITY			int32
//LANG 					int32
//LICENSE 				utf8
//NP_COMMUNICATION_ID 	utf8
//NPCOMMID 				utf8
//PADDING 				utf8 - S
//PARAMS 					utf8 - S
//PARAMS2 				utf8 - S
//PATCH_FILE 				utf8
//PS3_SYSTEM_VER 			utf8
//REGION_DENY 			int32
//RESOLUTION 				int32
//SAVEDATA_DETAIL 		utf8
//SAVEDATA_DIRECTORY 		utf8
//SAVEDATA_FILE_LIST 		utf8 - S
//SAVEDATA_LIST_PARAM 	utf8
//SAVEDATA_PARAMS 		utf8 - S
//SAVEDATA_TITLE 			utf8
//SOUND_FORMAT		 	int32
//SOURCE					int32
//SUB_TITLE				utf8
//TARGET_APP_VER			utf8
//TITLE 					utf8
//TITLE_ID				utf8
//PARENTAL_LEVEL 			int32
//PARENTALLEVEL 			int32
//VERSION 				utf8
//XMB_APPS 				int32

//PARENTAL_LEVEL_x 		int32
//TITLE_xx 				utf8
//TITLEID0xx				utf8
