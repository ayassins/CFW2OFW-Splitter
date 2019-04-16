#pragma once
#include <QtCore/qfile.h>
#include <QtCore/qdatastream.h>


class EDAT
{
public:
	EDAT(const QString & path);
	~EDAT();
	bool isedat();
	bool close();
	QByteArray contentid();
private:
	QFile f;
	quint32 magic, version;
};

