#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(const QString &path, const QStringList &templatefiles, qint64 size) : path(path), templatefiles(templatefiles), size(size)
{
}


DIRSPLIT::~DIRSPLIT()
{
}


bool DIRSPLIT::split()
{
	int part_number = 1;
	for each (const QString &templatefile in templatefiles) {
		qDebug() <<"0"<< templatefile;
		size -= QFile(templatefile).size();
	}
	qint64 leftSpace = size;
	qDebug() << "1" <<leftSpace;
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
			leftSpace = size;
			leftSpace -= f.fileInfo().size();
			part_number++;
		}
		QString DestPath = path + QString("_") + QString::number(part_number);
		qDebug() <<"2" <<DestPath + f.fileInfo().absolutePath().mid(path.length());
		QDir().mkpath(DestPath + f.fileInfo().absolutePath().mid(path.length()));
		for each (const QString &templatefile in templatefiles) {
			qDebug() <<"3"<< DestPath + templatefile.mid(path.length(), templatefile.size() - templatefile.lastIndexOf(QChar('\\')));
			QDir().mkpath(DestPath + templatefile.mid(path.length(), templatefile.size() - templatefile.lastIndexOf(QChar('\\'))));
			qDebug() <<"4" <<DestPath + templatefile.mid(path.length());
			QFile::copy(templatefile, DestPath + templatefile.mid(path.length()));
		}
		qDebug() <<"5" <<DestPath + f.filePath().mid(path.length());
		if (!QFile::rename(f.filePath(), DestPath + f.filePath().mid(path.length())))
			return false;
	}
	if (!QDir(path).removeRecursively())
		return false;
	return false;
}