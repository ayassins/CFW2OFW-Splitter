#include <Windows.h>
#include <QtCore/QCoreApplication>
#include <Qtcore/QDir>
#include <Qtcore/QString>
#include <Qtcore/qDebug>
#include <QtCore/qstringlist.h>
#include <QtCore/qcryptographichash.h>
#include <QtCore/qstandardpaths.h>
#include "pkg.h"
#include "dirsplit.h"


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
	if (type == QtDebugMsg)
		fprintf(stdout, "%s", msg.toLocal8Bit().constData());
}


QByteArray fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm) {
	QFile f(fileName);
	if (f.open(QFile::ReadOnly)) {
		QCryptographicHash hash(hashAlgorithm);
		if (hash.addData(&f)) {
			return hash.result();
		}
	}
	return QByteArray();
}


DWORD GetModuleSize(LPCSTR ModuleName) {
	HMODULE hModule = GetModuleHandleA(ModuleName);
	PIMAGE_DOS_HEADER IMAGE_DOS_HEADER = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS IMAGE_NT_HEADERS = (PIMAGE_NT_HEADERS)((PBYTE)hModule + IMAGE_DOS_HEADER->e_lfanew);
	PIMAGE_SECTION_HEADER IMAGE_SECTION_HEADER = (PIMAGE_SECTION_HEADER)((PBYTE)IMAGE_NT_HEADERS + sizeof(IMAGE_NT_HEADERS32));
	DWORD maxpointer = 0, size = 0;
	for (int i = 0; i < IMAGE_NT_HEADERS->FileHeader.NumberOfSections; ++i)
	{
		if (IMAGE_SECTION_HEADER->PointerToRawData > maxpointer)
		{
			maxpointer = IMAGE_SECTION_HEADER->PointerToRawData;
			size = IMAGE_SECTION_HEADER->PointerToRawData + IMAGE_SECTION_HEADER->SizeOfRawData;
		}
		IMAGE_SECTION_HEADER++;
	}
	return size;
}


bool FileInstall(const QString &source, const QString &dest, bool overwrite = 0) {
	QByteArray binary;
	try {
		QFile f(source);
		if (!f.open(QFile::ReadOnly))
			return false;
		if (f.seek(GetModuleSize(source.toLocal8Bit().constData())))
			return false;
		binary = f.readAll();
		f.close();
	}
	catch (...) {
		return false;
	}
	try {
		if ((QFile::exists(dest)) && (overwrite == false))
			return true;
		QFile f(dest);
		if (!f.open(QFile::Truncate))
			return false;
		if (f.write(binary) != binary.length())
			return false;
		f.close();
	}
	catch (...) {
		return false;
	}
	return true;
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

