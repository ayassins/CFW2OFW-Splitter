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
	DIRSPLIT ds(argv[1], 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN");
	if(ds.split())
	{
		for each (const QString &dir in ds.entryList()) {
			qDebug() << dir << endl;
			PKG(dir).Generate_Package();
		}
	}
	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
