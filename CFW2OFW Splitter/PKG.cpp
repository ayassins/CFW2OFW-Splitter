#include "PKG.h"


PKG::PKG(const QString &path) : path(path) {
}


PKG::~PKG() {
	//QDir().remove(package_conf);
}


bool PKG::generate_debug_package() {
	if (path.isEmpty())
		return false;
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	//if (!QFile::exists(path + "\\PARAM.SFO"))
		//return false;
	//if (!QFile::exists(path + "\\USRDIR\\EBOOT.BIN"))
		//return false;
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;

	EBOOT e(path + "\\USRDIR\\EBOOT.BIN");
	//if (!e.iseboot())
		//return false;
	qDebug() << "ok";
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QString Content_ID = e.Content_ID();
	QString package_part_number;
	QString Title_ID = path.mid(1 + path.lastIndexOf(QChar('\\')));
	if (Title_ID.contains(QChar('_'))) {
		package_part_number = ".part" + Title_ID.right(1);
		Title_ID.remove(Title_ID.indexOf(QChar('_')), 2);
	}
	QString Version = p.at(PARAM::VERSION);
	QTextStream out(&f);
	out << "ContentID = " << Content_ID << endl
		<< "Klicensee = 0x00000000000000000000000000000000" << endl
		<< "DRMType = Free" << endl
		<< "InstallDirectory = " << Title_ID << endl
		<< "PackageVersion = " << Version << endl;
	QString Category = p.at(PARAM::CATEGORY);
	PARAM(path + "\\PARAM.SFO").insert(PARAM::TARGET_APP_VER, "00.01");
	if (Category == "GD") {
		out << "ContentType = GameData" << endl
			<< "PackageType = DiscGamePatch" << endl;
	}
	else if (Category == "DG" || Category == "HG" || Category == "HD" || Category == "AT") {
		PARAM(path + "\\PARAM.SFO").insert(PARAM::APP_VER, "01.00");
		out << "ContentType = GameExec" << endl
			<< "PackageType = HDDGamePatch" << endl;
	}
	else
		return false;
	f.close();
	QProcess proc;
	QString App_Ver = p.at(PARAM::APP_VER);
	proc.setProcessChannelMode(QProcess::ForwardedChannels);
	proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << package_conf << path);
	if (!proc.waitForStarted())
		return false;
	if (!proc.waitForFinished(-1))
		return false;
	if (proc.exitCode() != QProcess::NormalExit && proc.exitStatus() != QProcess::NormalExit)
		return false;
	QString pkg_name = QDir::currentPath() + '\\' + Content_ID + "-A" + App_Ver.remove(2, 1) + "-V" + Version.remove(2, 1) + package_part_number + ".pkg";
	if (!QDir().rename(QDir::currentPath() + '\\' + Content_ID + ".pkg", pkg_name))
		return false;
	return true;
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


	//QStringList gamespaths;
	//if (size > 0)
		//gamespaths << DIRSPLIT(path, QStringList() << "PARAM.SFO" << "ICON0.PNG" << "USRDIR\\EBOOT.BIN", 4294705152).split();
	//if (gamespaths.isEmpty())
		//gamespaths << path;
	//for each (QString path in gamespaths)
	//{
		//if (path.endsWith('\\'))
			//path.remove(path.size() - 1, 1);
