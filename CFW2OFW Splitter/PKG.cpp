#include "PKG.h"


PKG::PKG(const QByteArray &path) : path(path) {
}


PKG::~PKG() {
	QDir().remove(package_conf);
}


bool PKG::generate_debug_package() {
	if (path.isEmpty())
		return false;
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	QByteArray title_id = path.mid(1 + path.lastIndexOf('\\'));
	if (!title_id.startsWith("BL"))
		if (!title_id.startsWith("BC"))
			if (!title_id.startsWith("NP"))
				return false;
	QByteArray part_number;
	if (title_id.contains('_')) {
		title_id = title_id.left(title_id.lastIndexOf('_'));
		part_number = ".part" + title_id.mid(1 + title_id.lastIndexOf('_'));
	}
	PARAM p(path + "\\PARAM.SFO");
	if (!p.isparam())
		return false;
	QByteArray version = p.at(PARAM::VERSION);
	QByteArray app_ver = p.at(PARAM::APP_VER);
	QByteArray target_app_ver = p.at(PARAM::CATEGORY);
	QByteArray category = p.at(PARAM::CATEGORY);
	if (version.isEmpty()) {
		version = "01.00";
		p.insert(PARAM::VERSION, version);
	}
	if (app_ver.isEmpty()) {
		app_ver = "01.00";
		p.insert(PARAM::APP_VER, app_ver);
	}
	if (target_app_ver.isEmpty() || target_app_ver != "00.01") {
		target_app_ver = "00.01";
		p.insert(PARAM::TARGET_APP_VER, target_app_ver);
	}
	if (category.isEmpty())
		return false;
	EBOOT e(path + "\\USRDIR\\EBOOT.BIN");	//	"0x00000000000000000000000000000000"
	if (!e.iseboot())
		return false;
	QByteArray contentid, klicensee, drmtype, contenttype, packagetype;
	contentid = e.contentid();
	if (contentid.isEmpty())
		return false;
	if (category == "HD") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "HG") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "DG") {
		p.insert(PARAM::APP_VER, "01.00");
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "GD") {
		contenttype = "Game_Data";
		packagetype = "DiscGamePatch";
	}
	else if (category == "AP") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "AM") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "AV") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "AT") {
		contenttype = "GameExec";
		packagetype = "HDDGamePatch";
	}
	else if (category == "2G") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "Game_Data";
	}
	else if (category == "2P") {
		//set EDT = "ISO.BIN.EDAT";
		contenttype = "GameData";
	}
	else if (category == "2D") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "GameData";
	}
	else if (category == "1P") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "GameData";
	}
	else if (category == "MN") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "minis";
	}
	else if (category == "PE") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "GameData";
	}
	else if (category == "PP") {
		//set EDT = ISO.BIN.EDAT;
		contenttype = "GameData";
	}
	else
		return false;
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << contentid << endl
		<< "Klicensee = " << klicensee << endl
		<< "DRMType = " << drmtype << endl
		<< "InstallDirectory = " << title_id << endl
		<< "PackageVersion = " << version << endl
		<< "ContentType = " << contenttype << endl
		<< "PackageType = " << packagetype << endl;
	if (!p.close())
		return false;
	if (!e.close())
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
