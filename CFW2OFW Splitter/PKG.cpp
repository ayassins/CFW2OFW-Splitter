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
	QString title_id = path.mid(1 + path.lastIndexOf(QChar('\\')));
	if (!title_id.startsWith("BL"))
		if (!title_id.startsWith("BC"))
			if (!title_id.startsWith("NP"))
				return false;
	if (!QFile::exists(path + "\\PARAM.SFO"))
		return false;
	if (!QFile::exists(path + "\\USRDIR\\EBOOT.BIN"))
		return false;
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;
	QString version = p.at(PARAM::VERSION);
	QString app_ver = p.at(PARAM::APP_VER);
	QString category = p.at(PARAM::CATEGORY);
	if (version.isEmpty())
		return false;
	if (app_ver.isEmpty())
		return false;
	if (category.isEmpty())
		return false;
	if(!p.insert(PARAM::TARGET_APP_VER, "00.01"))
		return false;
	if (category == "DG" || category == "HG" || category == "HD" || category == "AT")
		if (!p.insert(PARAM::APP_VER, "01.00"))
			return false;
	if (!p.close())
		return false;
	EBOOT e(path + "\\USRDIR\\EBOOT.BIN");
	if (!e.iseboot())
		return false;
	QString content_id = e.Content_ID();
	if (content_id.isEmpty())
		return false;
	if (!e.close())
		return false;
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QString part_number;
	if (title_id.contains(QChar('_'))) {
		part_number = ".part" + title_id.mid(1 + title_id.lastIndexOf(QChar('_')));
		title_id = title_id.left(title_id.lastIndexOf(QChar('_')));
	}
	QTextStream out(&f);
	out << "ContentID = " << content_id << endl
		<< "Klicensee = 0x00000000000000000000000000000000" << endl
		<< "DRMType = Free" << endl
		<< "InstallDirectory = " << title_id << endl
		<< "PackageVersion = " << version << endl;
	if (category == "GD") {
		out << "ContentType = GameData" << endl
			<< "PackageType = DiscGamePatch" << endl;
	}
	else if (category == "DG" || category == "HG" || category == "HD" || category == "AT") {
		out << "ContentType = GameExec" << endl
			<< "PackageType = HDDGamePatch" << endl;
	}
	else
		return false;
	f.close();
	QProcess proc;
	proc.setProcessChannelMode(QProcess::ForwardedChannels);
	proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << package_conf << path);
	if (!proc.waitForStarted())
		return false;
	if (!proc.waitForFinished(-1))
		return false;
	if (proc.exitCode() != QProcess::NormalExit && proc.exitStatus() != QProcess::NormalExit)
		return false;
	QString pkg_name = QDir::currentPath() + '\\' + content_id + "-A" + app_ver.remove(2, 1) + "-V" + version.remove(2, 1);
	if (!QDir().rename(pkg_name + ".pkg", pkg_name + part_number + ".pkg"))
		return false;
	return true;
}
