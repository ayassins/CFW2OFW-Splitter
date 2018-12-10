#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDirIterator>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include "pkg.h"
#include "dirsplit.h"

bool splitandcreatepkg(QString path)
{
	DIRSPLIT ds(path, 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN");
	if (ds.split()) {
		for each (const QString &d in ds.entryList()) {
			qDebug() << d << endl;
			PKG(d).Generate_Package();
		}
	}
	else {
		PKG(path).Generate_Package();
	}
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	if (argc > 0)
		splitandcreatepkg(argv[1]);
	else
	{
		QDirIterator dir(QCoreApplication::applicationDirPath(), QStringList() << "???????", QDir::Dirs);
		while (dir.hasNext()) {
			dir.next();
			splitandcreatepkg(dir.path());
		}
	}

	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
