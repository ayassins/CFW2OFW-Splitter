#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDirIterator>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include "PKG.h"
#include "DIRSPLIT.h"




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	QStringList splitdirs;
	if (DIRSPLIT(argv[1], 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN").split(splitdirs)) {
		for each (const QString &dir in splitdirs) {
			qDebug() << dir << endl;
			PKG(dir).Generate_Package();
		}
	}
	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
