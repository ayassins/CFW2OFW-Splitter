#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>

class EBOOT
{
public:
	EBOOT(const QString & path);
	~EBOOT();
	bool open();
	bool close();
	QString Content_ID();
private:
	QFile f;
	QString path;
};