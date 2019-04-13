#include "EBOOT.h"


EBOOT::EBOOT(const QString &path) {
	f.setFileName(path);
	f.open(QFile::ReadOnly);
	QDataStream in(&f);
	in.setByteOrder(QDataStream::BigEndian);
	in >> magic >> version;
}


EBOOT::~EBOOT() {
}


bool EBOOT::iseboot() {
	if ((magic != 0x53434500) && (version != 0x00000002))
		return false;
	return true;
}


bool EBOOT::close() {
	if (!f.isOpen())
		return false;
	f.close();
	return true;
}


QString EBOOT::Content_ID() {
	if (!f.isOpen())
		return QString();
	if (!iseboot())
		return QString();
	QDataStream in(&f);
	in.device()->seek(0x450);
	QByteArray ContentID(0x24, '\0');
	if (in.readRawData(ContentID.data(), 0x24) != 0x24)
		return QString();
	ContentID.replace("PATCH", "GAME0");
	ContentID.replace("SHIP0", "GAME0");
	return ContentID;
}
