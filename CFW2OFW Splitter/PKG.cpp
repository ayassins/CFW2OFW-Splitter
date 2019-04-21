#include "PKG.h"


PKG::PKG(const QString &path) : path(path) {
}


PKG::~PKG() {
	//QDir().remove(package_conf);
}


bool PKG::generate_debug_package() {
	QByteArray title_id, part_number, version, app_ver, cat, contentid, klicensee, drmtype, contenttype, packagetype;
	if (path.isEmpty())
		return false;
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	title_id = path.mid(1 + path.lastIndexOf('\\')).toLocal8Bit();
	if (!title_id.startsWith("BL"))
		if (!title_id.startsWith("BC"))
			if (!title_id.startsWith("NP"))
				return false;
	if (title_id.contains('_')) {
		title_id = title_id.left(title_id.lastIndexOf('_'));
		part_number = ".part" + title_id.mid(1 + title_id.lastIndexOf('_'));
	}
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;
	version = p.at(PARAM::VERSION);
	if (version.isEmpty()) {
		version = "01.00";
		p.insert(PARAM::VERSION, version);
	}
	app_ver = p.at(PARAM::APP_VER);
	if (app_ver.isEmpty()) {
		app_ver = "01.00";
		p.insert(PARAM::VERSION, app_ver);
	}
	cat = p.at(PARAM::CATEGORY);
	if (cat.isEmpty())
		return false;
	if (cat == "DG" || cat == "HD" || cat == "HG" || cat == "AP" || cat == "AV" || cat == "AT") {
		p.insert(PARAM::TARGET_APP_VER, "00.01");
		p.insert(PARAM::APP_VER, "01.00");
		contentid = EBOOT(path + "\\USRDIR\\EBOOT.BIN").contentid();
		klicensee = "0x00000000000000000000000000000000";
		drmtype = "Free";
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (cat == "GD") {
		p.insert(PARAM::TARGET_APP_VER, "00.01");
		contentid = EBOOT(path + "\\USRDIR\\EBOOT.BIN").contentid();
		klicensee = "0x00000000000000000000000000000000";
		drmtype = "Free";
		contenttype = "GameExec";
		packagetype = "DiscGamePatch";
	}
	else if (cat == "2G" || cat == "2P" || cat == "2D" || cat == "1P" || cat == "MN" || cat == "PE" || cat == "PP") {
		contentid = EDAT(path + "\\USRDIR\\ISO.BIN.EDAT").contentid();
		klicensee = "0x72F990788F9CFF745725F08E4C128387";
		drmtype = "Local";
		contenttype = "GameData";
	}
	else
		return false;
	if (contentid.isEmpty())
		return false;
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << contentid << endl
		<< "Klicensee = " << klicensee << endl
		<< "DRMType = " << drmtype << endl
		<< "InstallDirectory = " << title_id << endl
		<< "ContentType = " << contenttype << endl
		<< "PackageType = " << packagetype << endl
		<< "PackageVersion = " << version << endl;
	if (!p.close())
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
	QString pkg_name = QDir::currentPath() + '\\' + contentid + "-A" + app_ver.remove(2, 1) + "-V" + version.remove(2, 1);
	if (!QDir().rename(pkg_name + ".pkg", pkg_name + part_number + ".pkg"))
		return false;
	return true;
}
