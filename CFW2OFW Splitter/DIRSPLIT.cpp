#include "DIRSPLIT.h"



DIRSPLIT::DIRSPLIT(QString path, qint64 size) :path(path), size(size)
{
}


DIRSPLIT::~DIRSPLIT()
{
}


bool DIRSPLIT::split()
{
	int i = 1;
	qint64 leftSpace = size - QFile(path + "\\" + "PARAM.SFO").size() - QFile(path + "\\" + "ICON0.PNG").size();
	QDirIterator f1(path, QDir::Files, QDirIterator::Subdirectories);
	if (!f1.hasNext())
		return false;
	while (f1.hasNext()) {
		f1.next();
		if (f1.fileInfo().size() > size)
			return false;
	}
	QDirIterator f2(path, QDir::Files, QDirIterator::Subdirectories);
	while (f2.hasNext()) {
		f2.next();
		if (f2.fileInfo().size() <= leftSpace)
			leftSpace -= f2.fileInfo().size();
		else
		{
			leftSpace = size - QFile(path + "\\" + "PARAM.SFO").size() - QFile(path + "\\" + "ICON0.PNG").size();
			leftSpace -= f2.fileInfo().size();
			i++;
		}
		QString DestPath = path + QString("_") + QString::number(i);
		QDir().mkpath(DestPath + f2.fileInfo().absolutePath().remove(0, path.length()));
		QFile::copy(path + "\\" + "PARAM.SFO", DestPath + "\\" + "PARAM.SFO");
		QFile::copy(path + "\\" + "ICON0.PNG", DestPath + "\\" + "ICON0.PNG");
		QFile::rename(f2.filePath(), DestPath + f2.filePath().remove(0, path.length()));
		if (!QFile::exists(DestPath + f2.filePath().remove(0, path.length())))
			return false;
	}
	if (!QDir(path).removeRecursively())
		return false;
	return false;
}


const qstringlist list{ "a", "b", "c" };

for (const auto& i : list)
{
	qdebug() << i;
}


foreach(const qstring &str, list) {
		qdebug() << qstring(" [%1] ").arg(str);
}

for (qstringlist::iterator it = list.begin();
	it != list.end(); ++it) {
		qstring current = *it;
		qdebug() << "[[" << current << "]]";
}

qlistiterator<qstring> itr(list2);
while (itr.hasnext()) {
		qstring current = itr.next();
	qdebug() << "{" << current << "}";
}