#include "PKG.h"



PKG::PKG(QString path, PkgType type) : pkgtype(type), gamedirpath(path)
{	
}


PKG::~PKG()
{
	QDir().remove(package_conf);
}


bool PKG::Generate_Package()
{
	if (gamedirpath.endsWith('\\'))
		gamedirpath.remove(gamedirpath.size() - 1, 1);
	EBOOT e(gamedirpath + "\\USRDIR\\EBOOT.BIN");
	PARAM p(gamedirpath + "\\PARAM.SFO");
	if (!e.isValidEboot() && !p.isValidParam())
		return false;
	QString Title_ID = gamedirpath.mid(1 + gamedirpath.lastIndexOf(QChar('\\')));
	QString Content_ID = e.Content_ID();
	QString Category = p.Category();
	QString App_Ver = p.App_Ver();
	QString Version = p.Version();
	QString package_part_number;
	if (Title_ID.contains(QChar('_'))) {
		package_part_number = ".part" + Title_ID.mid(Title_ID.size() - 1);
		Title_ID.remove(Title_ID.indexOf(QChar('_')), 2);
	}
	QFile f(package_conf);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << Content_ID << endl
		<< "Klicensee = 0x00000000000000000000000000000000" << endl
		<< "DRMType = Free" << endl
		<< "InstallDirectory = " << Title_ID << endl
		<< "PackageVersion = " << Version << endl;
	if (Category == "GD") {
		out << "ContentType = GameData" << endl
			<< "PackageType = DiscGamePatch" << endl;
	}
	else if (Category == "DG" || Category == "HG" || Category == "HD" || Category == "AT") {
		p.Title_ID(Title_ID);
		if (Category == "DG")
			p.Category("HG");
		out << "ContentType = GameExec" << endl
			<< "PackageType = HDDGamePatch" << endl;
	}
	else
		return false;
	f.close();
	proc.setProcessChannelMode(QProcess::ForwardedChannels);
	proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << package_conf << gamedirpath);
	if (!proc.waitForStarted())
		return false;
	if (!proc.waitForFinished(-1))
		return false;
	if (proc.exitCode() != 0 && proc.exitStatus() != QProcess::NormalExit)
		return false;
	QString pkg_name = QDir::currentPath() + "\\"+ Content_ID + "-A" + App_Ver.remove(2, 1) + "-V" + Version.remove(2, 1) + package_part_number + ".pkg";
	if (!QDir().rename(QDir::currentPath() + "\\" + Content_ID + ".pkg", pkg_name))
		return false;
	if (pkgtype == Han)
	{
		proc.start(ps3xploit_rifgen_edatresign, QStringList() << pkg_name);
		if (!proc.waitForStarted())
			return false;
		if (!proc.waitForFinished(-1))
			return false;
		if (proc.exitCode() != 0 && proc.exitStatus() != QProcess::NormalExit)
			return false;
	}
	return true;
}
