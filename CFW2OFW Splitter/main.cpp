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
	QStringList argvdirs = a.arguments();
	if ((argvdirs[0].mid(1 + argvdirs[0].lastIndexOf(QDir::separator())) != "CFW2OFW_Splitter_v1.1.exe"))
		return false;
	qDebug() << " --- CFW2OFW Splitter v1.1 ---" << endl << "  -- a.yassin@msn.com --" << endl;
	if (argvdirs.length() < 2)
		qDebug() << "drag and drop directory BL?????? or BC?????? or NP?????? or SL??????" << endl;
	else {
		argvdirs.removeFirst();
		for each (QString argvdir in argvdirs) {
			QStringList gamespaths = DIRSPLIT(argvdir, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN", 4294705152).split();
			if (!gamespaths.isEmpty()) {
				for each (QString path in gamespaths)
					if (!PKG(path).generate_debug_package())
						qDebug() << "couldn't generate Package for [ " << path << " ]" << endl;
			}
			else
				if (!PKG(argvdir).generate_debug_package())
					qDebug() << "couldn't generate Package for [ " << argvdir << " ]" << endl;
		}
	}
	qDebug() << " Press any key to continue . . ."; getchar();
	return false;
}

