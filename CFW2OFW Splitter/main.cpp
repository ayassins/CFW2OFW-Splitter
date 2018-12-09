#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDirIterator>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include "pkg.h"
#include "dirsplit.h"




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	DIRSPLIT ds(argv[1], 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN");
	if(ds.split()) {
		for each (const QString &d in ds.entryList()) {
			qDebug() << d << endl;
			PKG(d).Generate_Package();
		}
	}
	else {
		PKG(argv[1]).Generate_Package();
	}
	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
