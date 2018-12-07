#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDirIterator>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include <qtcore/QListIterator>
#include "EBOOT.h"
#include "param.h"
#include "PKG.h"
#include "DIRSPLIT.h"




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	QStringList splitteddirectorys;
	DIRSPLIT(argv[1], QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN").split(splitteddirectorys);
	for each (const QString &splitteddirectory in splitteddirectorys) {
		qDebug() << splitteddirectory << "jhjhjhj";
		PKG(splitteddirectory).Generate_Package();
	}
	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
