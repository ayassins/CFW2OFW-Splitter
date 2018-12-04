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




int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	//qDebug() << PARAM("c:\\param.sfo").Title("123");
	//qDebug() << PKG("C:\\1\\ExtractedPKG\\NPEB0225_9\\",PKG::Han).Generate_Package();
	q();
	//qDebug() << EBOOT("c:\\eboot.bin").ContentID() << endl;
	//qDebug() << " --- CFW2OFW Splitter v1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	//if (splitdir(argv[1], 4294705152))
	//	qDebug() << "        Sucess!" << endl;
	//else
	//	qDebug() << "        Fail!" << endl;
	qDebug() << "Press any key to continue . . .";
	getchar();
	return FALSE;
}
