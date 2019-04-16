#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>

class EBOOT
{
public:
	EBOOT(const QString & path);
	~EBOOT();
	bool iseboot();
	bool close();
	QByteArray contentid();
private:
	QFile f;
	quint32 magic, version;
};