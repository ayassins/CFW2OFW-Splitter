#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDir>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include "pkg.h"
#include "dirsplit.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << " --- CFW2OFW Splitter v2 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	QStringList gamedirectorys(a.arguments()); gamedirectorys.removeFirst();
	if (argc < 2)
		gamedirectorys << QDir(QDir::currentPath()).entryList(QStringList() << "BL??????" << "BC??????" << "NP??????", QDir::Dirs | QDir::NoDotAndDotDot);
	if (gamedirectorys.isEmpty())
	{
		qDebug() << "no valid directorys BL?????? or BC?????? or NP?????? provided!\n";
		return -1;
	}
	int pkgcount = 0;
	for each (QString gamedirectory in gamedirectorys)
	{
		if (gamedirectory.length() == 8)
			gamedirectory = QDir::currentPath() + QDir::separator() + gamedirectory;
		DIRSPLIT dirsplit(gamedirectory, 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN");
		if (dirsplit.split())
			for each (const QString &entry in dirsplit.entryList())
				if (PKG(entry).Generate_Package())
					pkgcount++;
	}
	qDebug() << "finish generate " << pkgcount << "packages\n";
	qDebug() << "Press any key to continue . . ."; getchar();
	return false;
}
