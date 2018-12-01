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
	QFile f;
	QProcess proc;
};

