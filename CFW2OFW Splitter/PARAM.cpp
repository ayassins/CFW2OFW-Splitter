#include "PARAM.h"


PARAM::PARAM(const QString &path) {
	try {
		f.setFileName(path);
		f.open(QFile::ReadWrite);
		QDataStream in(&f);
		in >> s;
	}
	catch (...) {
	}
}


PARAM::~PARAM() {
	if (f.isOpen())
		f.close();
}


bool PARAM::isparam() {
	if (f.isOpen())
		if ((s.header.magic == 0x00505346) && (s.header.version == 0x01010000))
			return true;
	return false;
}


bool PARAM::close() {
	if (!isparam())
		return false;
	if (!f.resize(0))
		return false;
	QDataStream out(&f);
	out << s;
	if (!f.flush())
		return false;
	f.close();
	return true;
}


bool PARAM::insert(key key, const QByteArray &data) {
	if (!isparam())
		return false;
	int i = s.key_table.indexOf(key_name[key]);
	if (i < 0) {
		s.header.tables_entries += 1;
		SFO::index index;
		index.data_fmt = 0x0204;
		index.data_len = data.length() + 1;
		index.data_max_len = data_max_len[key];
		s.index_table << index;
		s.key_table << key_name[key];
		s.data_table << data;
	}
	else {
		s.index_table[i].data_len = data.length() + 1;
		s.data_table[i] = data;
	}
	return true;
}


bool PARAM::remove(key key) {
	if (!isparam())
		return false;
	int i = s.key_table.indexOf(key_name[key]);
	if (i < 0)
		return false;
	s.header.tables_entries -= 1;
	s.index_table.remove(i);
	s.key_table.remove(i);
	s.data_table.remove(i);
	return true;
}


QByteArray PARAM::at(key key) {
	if (!isparam())
		return QByteArray();
	int i = s.key_table.indexOf(key_name[key]);
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
