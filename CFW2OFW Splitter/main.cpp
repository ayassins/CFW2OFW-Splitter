#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDir>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include "pkg.h"
#include "dirsplit.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	if (type == QtDebugMsg)
		fprintf(stdout, "%s", msg.toLocal8Bit().constData());
}
  int main(int argc, char *argv[]) {
	  qInstallMessageHandler(myMessageOutput);
	  QCoreApplication a(argc, argv);
	  qDebug() << " --- CFW2OFW Splitter v1.1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	  if (argc < 2)
		  qDebug() << "drag and drop directory BL?????? or BC?????? or NP?????? or SL??????";
	  else {
		  QStringList gamespaths;
		  gamespaths << DIRSPLIT(argv[1], QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN", 4294705152).split();
		  if (!gamespaths.isEmpty())
			  for each (QString path in gamespaths)
				  if (!PKG(path).generate_debug_package())
					  qDebug() << "couldn't generate Package for [ " << path << " ]" << endl;
				  else
					  qDebug() << "couldn't split game directory!.";
	  }
	  qDebug() << " Press any key to continue . . ."; getchar();
	  return false;
  }

