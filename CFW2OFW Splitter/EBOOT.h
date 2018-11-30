#pragma once
#include <QtCore/qfile.h>

class EBOOT
{
public:
	EBOOT(QString path);
	~EBOOT();
	QString ContentID();
private:
	QFile f;
};