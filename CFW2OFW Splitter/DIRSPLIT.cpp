#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(const QString &path, qint64 size, const QStringList &templatefiles) : path(path), templatefiles(templatefiles), size(size)
{
}


DIRSPLIT::~DIRSPLIT()
{
}


bool DIRSPLIT::canSplit()
{
	QDirIterator f(path, QDir::Files, QDirIterator::Subdirectories);
	qint64 totalsize;
	while (f.hasNext()) {
		f.next();
		if (f.fileInfo().size() > size)
			return false;
		totalsize += f.fileInfo().size();
		if (totalsize > size)
			return true;
	}
	return false;
}


bool DIRSPLIT::split()
{
	if (!canSplit())
		return false;
	for each (const QString &templatefile in templatefiles) {
		size -= QFile(path + '\\' + templatefile).size();
	}
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
			if(templatefile.contains('\\'))
				QDir().mkpath(DestPath + '\\' + templatefile.left(templatefile.lastIndexOf('\\')));
			QFile::copy(path + '\\' + templatefile, DestPath + '\\' + templatefile);
		}
		QFile::rename(f.filePath(), DestPath + f.filePath().mid(path.length()));
		if (!QFile(DestPath + f.filePath().mid(path.length())).exists())
			return false;
	}
	if (!QDir(path).removeRecursively())
		return false;
	return true;
}


QStringList &DIRSPLIT::entryList()
{
	return splitteddirectorylist;
}