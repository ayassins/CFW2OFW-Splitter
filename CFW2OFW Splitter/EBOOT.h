#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>

class EBOOT
{
public:
	EBOOT(const QString & path);
	~EBOOT();
	bool iseboot();
	QString Content_ID();
private:
	QFile f;
	quint32 magic, version;
};