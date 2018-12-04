#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(QString path, qint64 size, QStringList templatefiles) :path(path), size(size),templatefiles(templatefiles)
{
}


DIRSPLIT::~DIRSPLIT()
{
}


bool DIRSPLIT::split()
{
	int part_number = 1;
	qint64 leftSpace = size;
	for each (const QString &templatefile in templatefiles) {
		leftSpace -= QFile(path + "\\" + templatefile).size();
	}
	QDirIterator chk_f(path, QDir::Files, QDirIterator::Subdirectories);
	if (!chk_f.hasNext())
		return false;
	while (chk_f.hasNext()) {
		chk_f.next();
		if (chk_f.fileInfo().size() > size)
			return false;
	}
	QDirIterator f(path, QDir::Files, QDirIterator::Subdirectories);
	while (f.hasNext()) {
		f.next();
		if (f.fileInfo().size() <= leftSpace)
			leftSpace -= f.fileInfo().size();
		else
		{
			for each (const QString &templatefile in templatefiles) {
				leftSpace -= QFile(path + "\\" + templatefile).size();
			}
			leftSpace -= f.fileInfo().size();
			part_number++;
		}
		QString DestPath = path + QString("_") + QString::number(part_number);
		QDir().mkpath(DestPath + f.fileInfo().absolutePath().remove(0, path.length()));
		for each (const QString &templatefile in templatefiles) {
			QFile::copy(path + "\\" + templatefile, DestPath + "\\" + templatefile);
		}
		if (!QFile::rename(f.filePath(), DestPath + f.filePath().remove(0, path.length())))
			return false;
	}
	if (!QDir(path).removeRecursively())
		return false;
	return false;
}