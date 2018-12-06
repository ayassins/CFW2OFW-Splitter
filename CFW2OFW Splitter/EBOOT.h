#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>

class EBOOT
{
public:
	EBOOT(const QString & path);
	~EBOOT();
	bool isValidEboot();
	QString Content_ID();
private:
	QFile f;
	quint32 magic, header_version;
	bool isValidSignature();
	bool isValidVersion();
};