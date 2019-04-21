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
	qDebug() << " --- CFW2OFW Toolbox v3 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	if (argc < 2)
		qDebug() << "drag and drop directory BL?????? or BC?????? or NP??????.";
	else {
		QStringList gamespaths;
		gamespaths << DIRSPLIT(argv[1], QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN", 4294705152).split();
		if (!gamespaths.isEmpty())
			for each (QString path in gamespaths)
				if(!PKG(path.toLocal8Bit()).generate_debug_package())
					qDebug() << "couldn't generate game package!.";
		else
			qDebug() << "couldn't split game directory!.";
	}
	qDebug() << " Press any key to continue . . ."; getchar();
	return false;
}

