#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qprocess.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>
#include "PARAM.h"
#include "EBOOT.h"
#include <QtCore/qdebug>

class PKG
{
public:
	enum PkgType {
		Debug ,
		Han ,
	};
	PKG(const QString &path, PkgType type = Debug);
	~PKG();
	bool Generate_Package();
private:
	QString path;
	QProcess proc;
	PkgType pkgtype;
	QString package_conf = QDir::currentPath() + "\\bin\\package.conf";
	QString psn_package_npdrm = QDir::currentPath() + "\\bin\\psn_package_npdrm.exe";
	QString ps3xploit_rifgen_edatresign = QDir::currentPath() + "\\bin\\ps3xploit_rifgen_edatresign.exe";
};

