#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDirIterator>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include "EBOOT.h"
#include "param.h"


BOOL splitdir(QString path, qint64 size)
{
	int i = 1;
	qint64 leftSpace = size - QFile(path + "\\" + "PARAM.SFO").size() - QFile(path + "\\" + "ICON0.PNG").size();
	QDirIterator f1(path, QDir::Files, QDirIterator::Subdirectories);
	if (!f1.hasNext())
		return FALSE;
	while (f1.hasNext()) {
		f1.next();
		if (f1.fileInfo().size() > size)
			return FALSE;
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
			return FALSE;
	}
	if(!QDir(path).removeRecursively())
		return FALSE;
	return TRUE;
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << PARAM("c:\\param.sfo").Title("wwwwgjgjgjgjgjgggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggffgg*hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
	//qDebug() << EBOOT("c:\\eboot.bin").ContentID() << endl;
	//qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	//if (splitdir(argv[1], 4294705152))
	//	qDebug() << "        Sucess!" << endl;
	//else
	//	qDebug() << "        Fail!" << endl;
	qDebug() << "Press any key to continue . . .";
	getchar();
	return FALSE;
}
