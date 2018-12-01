#include "PKG.h"



PKG::PKG(QString path)
{
	gamedirpath = path;
}


PKG::~PKG()
{
}
String removeLastSlash(String url) {
	if (url.endsWith("/")) {
		return url.substring(0, url.lastIndexOf("/"));
	}
	else {
		return url;
	}
}

bool PKG::Generate_Debug_Package()
{
	int pos = gamedirpath.lastIndexOf(QChar('\\')) + 1;
	if (pos == -1)
		return false;
	QString Title_ID = gamedirpath.mid(pos);
	EBOOT e(gamedirpath + "\\USRDIR\\EBOOT.BIN");
	PARAM p(gamedirpath + "\\PARAM.SFO");
	if (!e.isValidEboot() && !p.isValidParam())
		return false;
	QString Content_ID = e.Content_ID();
	QString Category = p.Category();
	QString App_Ver = p.App_Ver();
	QString Version = p.Version();
	QString Pkg_Config_File = QDir::currentPath() + "\\bin\\package.conf";
	QString Pkg_Name = Content_ID + "-A" + App_Ver.remove(2, 1) + "-V" + Version.remove(2, 1) + ".pkg";
	f.setFileName(Pkg_Config_File);
	if (!f.open(QIODevice::WriteOnly))
		return false;
	QTextStream out(&f);
	out << "ContentID = " << Content_ID << endl
		<< "Klicensee = 0x00000000000000000000000000000000" << endl
		<< "DRMType = Free" << endl
		<< "InstallDirectory = " << Title_ID << endl
		<< "PackageVersion = " << Version.insert(2,".")  << endl;
	if (Category == "GD")
	{
		out << "ContentType = GameData" << endl
			<< "PackageType = DiscGamePatch" << endl;
	}
	else if (Category == "DG" || Category == "HG" || Category == "HD" || Category == "AT")
	{
		p.Title_ID(Title_ID);
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
	QDir().rename(Content_ID + ".pkg", Pkg_Name);
}
