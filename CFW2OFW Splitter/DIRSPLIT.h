#pragma once
#include <Qtcore/QString>
#include <Qtcore/QDirIterator>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>
#include <Qtcore/qDebug>

class DIRSPLIT
{
public:
	DIRSPLIT(QString path, qint64 size);
	~DIRSPLIT();
	bool split();
private:
	QString path;
	qint64 size;
};

