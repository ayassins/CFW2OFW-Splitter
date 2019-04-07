#include "EBOOT.h"


EBOOT::EBOOT(const QString &path) {
	f.setFileName(path);
	f.open(QIODevice::ReadOnly);
	QDataStream in(&f);
	in >> magic >> version;
}


EBOOT::~EBOOT() {
	f.close();
}


bool EBOOT::iseboot() {
	return ((magic == 0x53434500) && (version == 0x02000000));
}


QString EBOOT::Content_ID() {
	if (!iseboot())
		return QString();
	QDataStream in(&f);
	in.device()->seek(448);
	QByteArray ContentID(0x24, '\0');
	in.readRawData(ContentID.data(), 0x24);
	ContentID.replace("PATCH", "GAME0");
	ContentID.replace("SHIP0", "GAME0");
	return ContentID;
}


//if (ContentID.contains("PATCH"))
	//ContentID.replace(ContentID.indexOf("PATCH"), 0x5, "GAME0");
//if (ContentID.contains("SHIP0"))
	//ContentID.replace(ContentID.indexOf("SHIP0"), 0x5, "GAME0");