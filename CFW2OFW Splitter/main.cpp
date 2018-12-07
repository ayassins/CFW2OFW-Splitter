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
	//qDebug() << PKG("C:\\1\\ExtractedPKG\\NPEB0225_9\\",PKG::Han).Generate_Package();
	DIRSPLIT(QCoreApplication::applicationDirPath() + "\\NPEB0225", QStringList() << "\\PARAM.SFO" << "\\ICON0.PNG"<<"\\USRDIR\\EBOOT.BIN").split();
	//qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	//if (DIRSPLIT(argv[1], QStringList() << "param.sfo" << "pic.jbeg").split())
		//qDebug() << "        Sucess!" << endl;
	//else
		//qDebug() << "        Fail!" << endl;
	qDebug() << "Press any key to continue . . .";
	getchar();
	return FALSE;
}
