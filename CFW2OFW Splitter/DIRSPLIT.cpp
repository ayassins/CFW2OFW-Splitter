#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(QString path, const QStringList &templatefiles, qint64 size) : path(path), templatefiles(templatefiles), size(size)
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
		leftSpace -= QFile(templatefile).size();
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
				leftSpace -= QFile(templatefile).size();
			}
			leftSpace -= f.fileInfo().size();
			part_number++;
		}
		QString DestPath = path + QString("_") + QString::number(part_number);
		QDir().mkpath(DestPath + f.fileInfo().absolutePath().mid(path.length()));
		for each (const QString &templatefile in templatefiles) {
			QDir().mkpath(DestPath + templatefile.mid(0, templatefile.lastIndexOf('\\')));
			QFile::copy(templatefile, DestPath + templatefile.mid(path.length()));
		}
		if (!QFile::rename(f.filePath(), DestPath + f.filePath().mid(path.length())))
			return false;
	}
	if (!QDir(path).removeRecursively())
		return false;
	return false;
}