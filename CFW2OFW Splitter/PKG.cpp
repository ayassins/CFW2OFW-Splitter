#include "PKG.h"



PKG::PKG(QString path)
{
	gamedirpath = path;
}


PKG::~PKG()
{
}


bool PKG::Generate_Debug_Package()
{
	QString Category, App_Ver, Version, Content_ID, Title_ID, Pkg_Name, Pkg_Config;
	Title_ID = gamedirpath.mid(gamedirpath.lastIndexOf("/"));
	EBOOT e(gamedirpath + "\\USRDIR\\EBOOT.BIN");
	PARAM p(gamedirpath + "\\PARAM.SFO");
	if (!e.isValidEboot() && !p.isValidParam())
		return false;
	Content_ID = e.Content_ID();
	Category = p.Category();
	App_Ver = p.App_Ver();
	Version = p.Version();
	Pkg_Config = QDir::currentPath() + "bin\\package.conf";
	Pkg_Name = Content_ID + "-A" + App_Ver.remove(2, 1) + "-V" + Version.remove(2, 1) + ".pkg";
	f.setFileName(Pkg_Config);
	if (!f.open(QIODevice::WriteOnly,QIODevice::Truncate))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << Content_ID << endl
		<< "Klicensee = 0x00000000000000000000000000000000" << endl
		<< "DRMType = Free" << endl
		<< "InstallDirectory = " << Title_ID << endl
		<< "PackageVersion = " << Version  << endl;
	if (Category == "GD")
	{
		out << "ContentType = GameData" << endl
			<< "PackageType = DiscGamePatch" << endl;
	}
	else if (Category == "DG" || Category == "HG" || Category == "HD" || Category == "AT")
	{
		p.Title_ID("");
		if (Category == "DG")
			p.Category("HG");
		out << "ContentType = GameExec" << endl
			<< "PackageType = HDDGamePatch" << endl;
	}
	else
		return false;
	f.close();
	proc.start("%s", QStringList() << "- n" << "- f");
	proc.waitForFinished();
}
