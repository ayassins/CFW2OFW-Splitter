#pragma once
#include <Qtcore/QString>
#include <QtCore/qstringlist.h>
#include <Qtcore/QDirIterator>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>

class DIRSPLIT
{
public:
	DIRSPLIT(const QString & path, const QStringList &primaryfiles = QStringList(), qint64 size = 4294705152);
	~DIRSPLIT();
	
	QStringList split();
private:
	QString path;
	QStringList primaryfiles;
	qint64 size;
	bool cansplit();
};

