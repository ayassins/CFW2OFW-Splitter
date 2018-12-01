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
	PKG(QString path);
	~PKG();
	bool Generate_Debug_Package();
private:
	QString gamedirpath;
	QProcess proc;
	QString package_conf = QDir::currentPath() + "\\bin\\package.conf";
	QString psn_package_npdrm = QDir::currentPath() + "\\bin\\psn_package_npdrm.exe";
};

