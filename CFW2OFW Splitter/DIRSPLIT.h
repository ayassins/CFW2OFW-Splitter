#pragma once
#include <Qtcore/QString>
#include <QtCore/qstringlist.h>
#include <Qtcore/QDirIterator>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>
#include <Qtcore/qDebug>

class DIRSPLIT
{
public:
	DIRSPLIT(const QString &path);
	~DIRSPLIT();
	QStringList entryList(const QStringList &templatefiles = QStringList(), qint64 size = 4294705152);
private:
	QString path;
	QStringList splitteddirectorylist;
	bool split(const QStringList &templatefiles, qint64 size);
};

