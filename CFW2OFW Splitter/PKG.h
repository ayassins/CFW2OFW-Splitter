#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qprocess.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qfile.h>
#include <QtCore/qdir.h>
#include "PARAM.h"
#include "EBOOT.h"
#include "DIRSPLIT.h"
#include <QtCore/qdebug>

class PKG
{
public:
	PKG(const QString &path);
	~PKG();
	bool generate_debug_package();
private:
	QString path;
	QString package_conf = QDir::currentPath() + "\\bin\\package.conf";
	QString psn_package_npdrm = QDir::currentPath() + "\\bin\\psn_package_npdrm.exe";
	//QString ps3xploit_rifgen_edatresign = QDir::currentPath() + "\\bin\\ps3xploit_rifgen_edatresign.exe";
};