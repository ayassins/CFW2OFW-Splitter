#include "DIRSPLIT.h"


DIRSPLIT::DIRSPLIT(const QString &path, const QStringList &primaryfiles, qint64 size) : path(path), primaryfiles(primaryfiles), size(size) {
}


DIRSPLIT::~DIRSPLIT() {
}


bool DIRSPLIT::cansplit() {
	QDirIterator f(path, QDir::Files, QDirIterator::Subdirectories);
	qint64 totalsize = 0;
	while (f.hasNext()) {
		f.next();
		if (f.fileInfo().size() > size)
			return false;
		totalsize += f.fileInfo().size();
	}
	if (totalsize < size)
		return false;
	return true;
}


QStringList DIRSPLIT::split() {
	if (!cansplit())
		return QStringList();
	for each (const QString &primaryfile in primaryfiles)
		size -= QFile(path + QDir::separator() + primaryfile).size();
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
		for each (const QString &primaryfile in primaryfiles) {
			if (primaryfile.contains(QDir::separator()))
				QDir().mkpath(DestPath + QDir::separator() + primaryfile.left(primaryfile.lastIndexOf(QDir::separator())));
			QFile::copy(path + QDir::separator() + primaryfile, DestPath + QDir::separator() + primaryfile);
		}
		QFile::rename(f.filePath(), DestPath + f.filePath().mid(path.length()));
		if (!QFile(DestPath + f.filePath().mid(path.length())).exists())
			return QStringList();
	}
	//if (!QDir(path).removeRecursively())
		//return QStringList();
	return splitteddirectorylist;
}
