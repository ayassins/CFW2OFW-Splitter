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
		qDebug() << "no valid directory BL?????? or BC?????? or NP?????? provided!" << endl << "Press any key to continue . . ."; getchar();
		return -1;
	}
	int i = 0;
	for each (QString gamedirectory in gamedirectorys)
	{
		if (gamedirectory.length() == 8)
			gamedirectory = QDir::currentPath() + QDir::separator() + gamedirectory;
		if (PKG(gamedirectory,PKG::Debug, 4294705152).generate_package())
				i++;
	}
	qDebug() << "Finish generating (" << i << ") packages." << endl << "Press any key to continue . . ."; getchar();
	return false;
}
