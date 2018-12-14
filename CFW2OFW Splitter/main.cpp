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
	QStringList gamedirectorys(a.arguments());
	if(gamedirectorys.at(0) == QDir::toNativeSeparators(a.applicationFilePath()))
		gamedirectorys.removeAt(0);
	if (gamedirectorys.isEmpty())
		gamedirectorys << QDir(QDir::currentPath()).entryList(QStringList() << "BL??????" << "BC??????" << "NP??????", QDir::Dirs | QDir::NoDotAndDotDot);
	for each (QString gamedirectory in gamedirectorys)
	{
		if (!gamedirectory.contains(QDir::toNativeSeparators(QDir::currentPath())))
			gamedirectory = QDir::currentPath() + QDir::separator() + gamedirectory;
		DIRSPLIT dirsplit(gamedirectory, 4294705152, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN");
		if (dirsplit.split()) {
			for each (const QString &entry in dirsplit.entryList()) {
				qDebug() << entry << endl;
				PKG(entry).Generate_Package();
			}
		}
		else {
			PKG(gamedirectory).Generate_Package();
		}
	}
	qDebug() << "Press any key to continue . . ."; getchar();
	return FALSE;
}
