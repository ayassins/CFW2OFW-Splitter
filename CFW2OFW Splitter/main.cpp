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
	qDebug() << " --- CFW2OFW Splitter v3 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	QStringList dirs(a.arguments());
	dirs.removeFirst();
	if (argc < 2)
		dirs << QDir(QDir::currentPath()).entryList(QStringList() << "BL??????" << "BC??????" << "NP??????", QDir::Dirs | QDir::NoDotAndDotDot);
	if (dirs.isEmpty())
	{
		qDebug() << "no valid directory BL?????? or BC?????? or NP?????? provided!" << endl << "Press any key to continue . . ."; getchar();
		return -1;
	}
	int i = 0;
	for each (QString dir in dirs)
	{
		if (dir.length() == 8)
			dir = QDir::currentPath() + QDir::separator() + dir;
		if (PKG(dir,PKG::Debug, 4294705152).generate_packages())
				i++;
	}
	qDebug() << "Finish generating (" << i << ") packages." << endl << "Press any key to continue . . ."; getchar();
	return false;
}
