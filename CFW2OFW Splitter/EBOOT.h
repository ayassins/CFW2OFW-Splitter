#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>

class EBOOT
{
public:
	EBOOT(const QString & path);
	~EBOOT();
	bool open(QFile::OpenMode flags);
	QString Content_ID();
private:
	QFile f;
	QString path;
	quint32 magic, version;
	bool ismagic();
	bool isversion();
};