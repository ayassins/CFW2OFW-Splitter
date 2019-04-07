#pragma once
#include <QtCore/qvector.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>


class PARAM
{
public:
	PARAM(const QString &path);
	~PARAM();
	bool isparam();
	bool insert(const QByteArray &key, const QByteArray &data, quint32 data_max_len);
	bool remove(const QByteArray &key);
	QByteArray at(const QByteArray &key);
	int length();
	struct SFO {
		friend QDataStream &operator>>(QDataStream &in, SFO &s);
		friend QDataStream &operator<<(QDataStream &out, SFO &s);
		struct header {
			quint32 magic;
			quint32 version;
			quint32 key_table_start;
			quint32 data_table_start;
			quint32 tables_entries;
		} header;
		struct index {
			quint16 key_offset;
			quint16 data_fmt;
			quint32 data_len;
			quint32 data_max_len;
			quint32 data_offset;
		};
		QVector <index> index_table;
		QVector <QByteArray> key_table;
		QVector <QByteArray> data_table;
	};
private:
	SFO s;
	QFile f;
	bool commit;
	enum data_max_len {
		ACCOUNT_ID = 0x010,
		ACCOUNTID = 0x010,
		ANALOG_MODE = 0x004,
		APP_VER = 0x008,
		ATTRIBUTE = 0x004,
		BOOTABLE = 0x004,
		CATEGORY = 0x004,
		CONTENT_ID = 0x030,
		DETAIL = 0x400,
		GAMEDATA_ID = 0x020,
		ITEM_PRIORITY = 0x004,
		LANG = 0x004,
		LICENSE = 0x200,
		NP_COMMUNICATION_ID = 0x010,
		NPCOMMID = 0x010,
		PADDING = 0x008,
		PARAMS = 0x400,
		PARAMS2 = 0x00C,
		PARENTAL_LEVEL_x = 0x004,
		PARENTAL_LEVEL = 0x004,
		PARENTALLEVEL = 0x004,
		PATCH_FILE = 0x020,
		PS3_SYSTEM_VER = 0x008,
		REGION_DENY = 0x004,
		RESOLUTION = 0x004,
		SAVEDATA_DETAIL = 0x400,
		SAVEDATA_DIRECTORY = 0x040,
		SAVEDATA_FILE_LIST = 0xC60,
		SAVEDATA_LIST_PARAM = 0x008,
		SAVEDATA_PARAMS = 0x080,
		SAVEDATA_TITLE = 0x080,
		SOUND_FORMAT = 0x004,
		SOURCE = 0x004,
		SUB_TITLE = 0x080,
		TARGET_APP_VER = 0x008,
		TITLE = 0x080,
		TITLE_ID = 0x010,
		TITLE_xx = 0x080,
		TITLEID0xx = 0x010,
		VERSION = 0x008,
		XMB_APPS = 0x004
	};
};

