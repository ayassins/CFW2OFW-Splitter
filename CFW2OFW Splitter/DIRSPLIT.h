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
	DIRSPLIT(const QString &path, qint64 size = 4294705152, const QStringList &templatefiles = QStringList());
	~DIRSPLIT();
	bool split();
	QStringList &entryList();
	bool isSplittable();
private:
	QString path;
	qint64 size;
	QStringList templatefiles;
	QStringList splitteddirectorylist;
};

