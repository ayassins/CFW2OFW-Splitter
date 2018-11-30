#include "EBOOT.h"

EBOOT::EBOOT(QString path)
{
	f.setFileName(path);
	f.open(QIODevice::ReadOnly);
}

EBOOT::~EBOOT()
{
	f.close();
}

QString EBOOT::ContentID()
{
	f.seek(0x450);
	QByteArray ContentID = f.read(0x24);
	if (ContentID.contains("PATCH"))
		ContentID.replace(ContentID.indexOf("PATCH"), 0x5, "GAME0");
	if (ContentID.contains("SHIP0"))
		ContentID.replace(ContentID.indexOf("SHIP0"), 0x5, "GAME0");
	return ContentID;
}
