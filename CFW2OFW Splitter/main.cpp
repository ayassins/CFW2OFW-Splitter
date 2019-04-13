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
				if(!PKG(path).generate_debug_package())
					qDebug() << "couldn't generate game package!.";
		else
			qDebug() << "couldn't split game directory!.";
	}
	qDebug() << " Press any key to continue . . ."; getchar();
	return false;
}

//if (type == Han) {
	//proc.start(ps3xploit_rifgen_edatresign, QStringList() << pkg_name);
	//if (!proc.waitForStarted())
		//return false;
	//if (!proc.waitForFinished(-1))
		//return false;
	//if (proc.exitCode() != QProcess::NormalExit && proc.exitStatus() != QProcess::NormalExit)
		//return false;
	///if (!QDir().remove(pkg_name))
		//return false;
//}

//
//QStringList dirs(a.arguments());
//dirs.removeFirst();
//if (argc < 2)
//	dirs << QDir(QDir::currentPath()).entryList(QStringList() << "BL??????" << "BC??????" << "NP??????", QDir::Dirs | QDir::NoDotAndDotDot);
//if (dirs.isEmpty())
//{
//	qDebug() << "no valid directory BL?????? or BC?????? or NP?????? provided!" << endl << "Press any key to continue . . ."; getchar();
//	return -1;
//}
//int i = 0;
//for each (QString dir in dirs)
//{
//	if (dir.length() == 8)
//		dir = QDir::currentPath() + QDir::separator() + dir;
//	if (PKG(dir, PKG::Debug, 4294705152).generate_packages())
//		i++;
//}
