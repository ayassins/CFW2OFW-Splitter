#include "PKG.h"


PKG::PKG(const QString &path) : path(path) {
}


PKG::~PKG() {
	//QDir().remove(package_conf);
}


bool PKG::generate_debug_package() {
	QByteArray titleid, partnum, cat, version, app_ver, contentid, klicensee, drmtype, contenttype, pkgtype, pkgver;
	QString pkgname, npkgname;
	if (path.isEmpty())
		return false;
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	titleid = path.mid(1 + path.lastIndexOf('\\')).toLocal8Bit();
	if (!titleid.startsWith("BL"))
		if (!titleid.startsWith("BC"))
			if (!titleid.startsWith("NP"))
				if (!titleid.startsWith("SL"))
					return false;
	if (titleid.contains('_')) {
		titleid = titleid.left(titleid.lastIndexOf('_'));
		partnum = ".part" + titleid.mid(1 + titleid.lastIndexOf('_'));
	}
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;
	cat = p.at(PARAM::CATEGORY);
	if (cat == "DG" || cat == "HD" || cat == "HG" ||
		cat == "AP" || cat == "AM" || cat == "AV" ||
		cat == "AT" || cat == "CB" || cat == "AS" ||
		cat == "HM" || cat == "SF") {
		contenttype = "GameExec";
		pkgtype = "HDDGamePatch";
		drmtype = "Free";
		app_ver = "01.00";
		p.insert(PARAM::APP_VER, app_ver);
		p.insert(PARAM::TARGET_APP_VER, "00.01");
	}
	else if (cat == "GD") {
		contenttype = "GameData";
		pkgtype = "DiscGamePatch";
		drmtype = "Free";
		app_ver = p.at(PARAM::APP_VER);
		p.insert(PARAM::TARGET_APP_VER, "00.01");
	}
	else if (cat == "1P")
		contenttype = "PS1Game";
	else if (cat == "2G" || cat == "2P" || cat == "2D")
		contenttype = "PS2Game";
	else if (cat == "MN")
		contenttype = "minis";
	else if (cat == "PE")
		contenttype = "PSPemu";
	else if (cat == "PP")
		contenttype = "PSPData";
	else if (cat == "WT")
		contenttype = "XMBLink";
	else
		return false;
	version = p.at(PARAM::VERSION);
	if (version.isEmpty()) {
		version = "01.00";
		p.insert(PARAM::VERSION, version);
	}
	if (app_ver.isEmpty())
		app_ver = "01.00";
	if (drmtype.isEmpty())
		drmtype = "Local";
	klicensee = "0x00000000000000000000000000000000";			//"0x72F990788F9CFF745725F08E4C128387";
	pkgver = version;
	if (QFile::exists(path + "\\USRDIR\\EBOOT.BIN")) {
		contentid = EBOOT(path + "\\USRDIR\\EBOOT.BIN").contentid();
		pkgname = contentid + "-A" + app_ver + "-V" + version;
		npkgname = pkgname;
	}
	else {
		contentid = EDAT(path + "\\USRDIR\\ISO.BIN.EDAT").contentid();
		pkgname = contentid;
		npkgname = pkgname + "-A" + app_ver + "-V" + version;
	}
	if (contentid.isEmpty())
		return false;
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << contentid << endl
		<< "Klicensee = " << klicensee << endl
		<< "DRMType = " << drmtype << endl
		<< "InstallDirectory = " << titleid << endl
		<< "PackageVersion = " << pkgver << endl
		<< "ContentType = " << contenttype << endl;
	if (!pkgtype.isEmpty())
		out << "PackageType = " << pkgtype << endl;
	if (!p.close())
		return false;
	f.close();
	QProcess proc;
	proc.setProcessChannelMode(QProcess::ForwardedChannels);
	qDebug() << endl << "Generate Package : \"" << npkgname.replace('.', "") + partnum + ".pkg" << "\"" << endl;
	proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << package_conf << path);
	if (!proc.waitForStarted())
		return false;
	if (!proc.waitForFinished(-1))
		return false;
	if (proc.exitCode() != QProcess::NormalExit && proc.exitStatus() != QProcess::NormalExit)
		return false;
	QString pkgpath = QDir::currentPath() + '\\';
	if (!QDir().rename(pkgpath + pkgname.replace('.', "") + ".pkg", pkgpath + npkgname.replace('.', "") + partnum + ".pkg"))
		return false;
	return true;
}
