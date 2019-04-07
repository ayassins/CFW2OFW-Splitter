#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(const QString &path, const QStringList &templatefiles, qint64 size) : path(path), templatefiles(templatefiles), size(size)
{
}


DIRSPLIT::~DIRSPLIT()
{
}


QStringList DIRSPLIT::split()
{
	{
		QDirIterator f(path, QDir::Files, QDirIterator::Subdirectories);
		qint64 totalsize = 0;
		while (f.hasNext()) {
			f.next();
			if (f.fileInfo().size() > size)
				return QStringList();
			totalsize += f.fileInfo().size();
		}
		if (totalsize < size)
			return QStringList();
	}
	for each (const QString &templatefile in templatefiles)
		size -= QFile(path + QDir::separator() + templatefile).size();
	QStringList splitteddirectorylist;
	qint64 leftSpace = size;
	int part_number = 1;
	QDirIterator f(path, QDir::Files, QDirIterator::Subdirectories);
	while (f.hasNext()) {
		f.next();
		if (f.fileInfo().size() <= leftSpace)
			leftSpace -= f.fileInfo().size();
		else
		{
			leftSpace = size;
			leftSpace -= f.fileInfo().size();
			part_number++;
		}
		QString DestPath = path + QString('_') + QString::number(part_number);
		if (!splitteddirectorylist.contains(DestPath))
			splitteddirectorylist << DestPath;
		QDir().mkpath(DestPath + f.fileInfo().absolutePath().mid(path.length()));
		for each (const QString &templatefile in templatefiles) {
			if(templatefile.contains(QDir::separator()))
				QDir().mkpath(DestPath + QDir::separator() + templatefile.left(templatefile.lastIndexOf(QDir::separator())));
			QFile::copy(path + QDir::separator() + templatefile, DestPath + QDir::separator() + templatefile);
		}
		QFile::rename(f.filePath(), DestPath + f.filePath().mid(path.length()));
		if (!QFile(DestPath + f.filePath().mid(path.length())).exists())
			return QStringList();
	}
	if (!QDir(path).removeRecursively())
		return QStringList();
	return splitteddirectorylist;
}
