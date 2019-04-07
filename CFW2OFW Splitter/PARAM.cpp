#include "PARAM.h"


PARAM::PARAM(const QString &path) {
	f.setFileName(path);
	f.open(QIODevice::ReadWrite);
	QDataStream in(&f);
	in >> s;
}


PARAM::~PARAM() {
	if (commit) {
		f.resize(0);
		QDataStream out(&f);
		out << s;
	}
	f.close();
}


bool PARAM::isparam() {
	return ((s.header.magic == 0x00505346) && (s.header.version == 0x01010000));
}


bool PARAM::insert(const QByteArray &key, const QByteArray &data, quint32 data_max_len) {
	int i = s.key_table.indexOf(key.toUpper());
	if (i < 0) {
		s.header.tables_entries += 1;
		SFO::index index;
		index.data_fmt = 0x0402;
		index.data_len = data.length();
		index.data_max_len = data_max_len;
		s.index_table << index;
		s.key_table << key;
		s.data_table << data;
	}
	else {
		s.index_table[i].data_len = data.length();
		s.data_table[i] = data;
	}
	commit = true;
	return true;
}


bool PARAM::remove(const QByteArray &key) {
	int i = s.key_table.indexOf(key.toUpper());
	if (i < 0)
		return false;
	s.header.tables_entries -= 1;
	s.index_table.remove(i);
	s.key_table.remove(i);
	s.data_table.remove(i);
	commit = true;
	return true;
}


QByteArray PARAM::at(const QByteArray &key) {
	int i = s.key_table.indexOf(key.toUpper());
	if (i < 0)
		return QByteArray();
	return s.data_table[i];
}


int PARAM::length() {
	return s.header.tables_entries;
}


QDataStream &operator>>(QDataStream &in, PARAM::SFO &s) {
	in.device()->reset();
	in.setByteOrder(QDataStream::BigEndian);
	in >> s.header.magic >> s.header.version;
	in.setByteOrder(QDataStream::LittleEndian);
	in >> s.header.key_table_start >> s.header.data_table_start >> s.header.tables_entries;
	s.index_table.resize(s.header.tables_entries);
	for (int i = 0; i < s.header.tables_entries; ++i)
		in >> s.index_table[i].key_offset >> s.index_table[i].data_fmt >> s.index_table[i].data_len
		>> s.index_table[i].data_max_len >> s.index_table[i].data_offset;
	for (int i = 0; i < s.header.tables_entries; ++i) {
		quint8 byte;
		QByteArray key;
		do {
			in >> byte;
			if (byte)
				key.append(byte);
		} while (byte);
		s.key_table << key;
	}
	in.device()->seek(s.header.data_table_start);
	for (int i = 0; i < s.header.tables_entries; ++i) {
		QByteArray data(s.index_table[i].data_max_len, '\0');
		in.readRawData(data.data(), s.index_table[i].data_max_len);
		s.data_table << data;
	}
	return in;
}


QDataStream &operator<<(QDataStream &out, PARAM::SFO  &s) {
	out.device()->reset();
	out.setByteOrder(QDataStream::BigEndian);
	s.header.magic = 0x00505346;
	s.header.version = 0x01010000;
	out << s.header.magic << s.header.version;
	out.setByteOrder(QDataStream::LittleEndian);
	s.header.key_table_start = 0x14 + s.index_table.count() * 0x10;
	s.header.data_table_start = s.header.key_table_start;
	s.header.tables_entries = s.index_table.count();
	for (auto key : s.key_table)
		s.header.data_table_start += key.length() + 1;
	if (s.header.data_table_start % 4 != 0)
		s.header.data_table_start = (s.header.data_table_start / 4 + 1) * 4;
	out << s.header.key_table_start << s.header.data_table_start << s.header.tables_entries;
	s.index_table[0].key_offset = s.index_table[0].data_offset = 0;
	for (int i = 0; i < s.header.tables_entries; ++i) {
		s.index_table[i + 1].key_offset = s.index_table[i].key_offset + s.key_table[i].length() + 1;
		s.index_table[i + 1].data_offset = s.index_table[i].data_offset + s.index_table[i].data_max_len;
		out << s.index_table[i].key_offset << s.index_table[i].data_fmt << s.index_table[i].data_len
			<< s.index_table[i].data_max_len << s.index_table[i].data_offset;
	}
	for (int i = 0; i < s.header.tables_entries; ++i)
		out.writeRawData(s.key_table[i].append('\0').toUpper().data(), s.key_table[i].length());
	out.device()->seek(s.header.data_table_start);
	for (int i = 0; i < s.header.tables_entries; ++i)
		out.writeRawData(s.data_table[i].data(), s.index_table[i].data_max_len);
	return out;
}


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

enum key {
	ACCOUNT_ID,
	ACCOUNTID  ,
	ANALOG_MODE,
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
