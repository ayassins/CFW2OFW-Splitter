#include "PKG.h"



PKG::PKG(QString path)
{
	if (path.endsWith('\\'))
		path.remove(path.size() - 1, 1);
	gamedirpath = path;
}


PKG::~PKG()
{
}


bool PKG::Generate_Debug_Package()
{
	QString Title_ID = gamedirpath.mid(1 + gamedirpath.lastIndexOf(QChar('\\')));
	EBOOT e(gamedirpath + "\\USRDIR\\EBOOT.BIN");
	PARAM p(gamedirpath + "\\PARAM.SFO");
	if (!e.isValidEboot() && !p.isValidParam())
		return false;
	QString Content_ID = e.Content_ID();
	QString Category = p.Category();
	QString App_Ver = p.App_Ver();
	QString Version = p.Version();
	QString Pkg_Config_File = QDir::currentPath() + "\\bin\\package.conf";
	QString psn_package_npdrm = QDir::currentPath() + "\\bin\\psn_package_npdrm.exe";
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
	proc.setProcessChannelMode(QProcess::ForwardedChannels);
	proc.start(psn_package_npdrm, QStringList() << "-n" << "-f" << Pkg_Config_File << gamedirpath);
	//if (!proc.waitForStarted())
		//return false;
	if (!proc.waitForFinished(-1))
		qDebug() << "Make failed:";
	else
		qDebug() << "Make output:";
	//QDir().rename(Content_ID + ".pkg", Pkg_Name);
	return true;
}
