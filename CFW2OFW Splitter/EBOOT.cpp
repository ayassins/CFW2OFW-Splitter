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


bool EBOOT::isValidEboot()
{
	return (isValidSignature() && isValidVersion());
}


bool EBOOT::isValidSignature()
{
	return magic == 0x53434500;
}


bool EBOOT::isValidVersion()
{
	return header_version == 0x02000000;
}


QString EBOOT::Content_ID()
{
	QDataStream in(&f);
	in >> magic >> header_version;
	in.skipRawData(0x448);
	QByteArray ContentID;
	in.readRawData(ContentID.data(),0x24);
	if (ContentID.contains("PATCH"))
		ContentID.replace(ContentID.indexOf("PATCH"), 0x5, "GAME0");
	if (ContentID.contains("SHIP0"))
		ContentID.replace(ContentID.indexOf("SHIP0"), 0x5, "GAME0");
	return ContentID;
}