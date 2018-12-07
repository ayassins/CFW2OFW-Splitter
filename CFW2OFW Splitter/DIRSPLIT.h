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
	DIRSPLIT(const QString &path, const QStringList &templatefiles, qint64 size = 4294705152);
	~DIRSPLIT();
	bool split(QStringList &splitteddirectorys);
private:
	QString path;
	qint64 size;
	QStringList templatefiles;
};

