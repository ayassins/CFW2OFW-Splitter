#include "EBOOT.h"


EBOOT::EBOOT(const QString &path) :path(path) {
	f.setFileName(path);
}


EBOOT::~EBOOT() {
	f.close();
}


bool EBOOT::open() {
	if (!f.open(QFile::ReadOnly))
		return false;
	QDataStream in(&f);
	in.setByteOrder(QDataStream::BigEndian);
	quint32 magic, version;
	in >> magic >> version;
	if (magic != 0x53434500)
		return false;
	if (version != 0x02000000)
		return false;
}


bool EBOOT::close() {
	f.close();
}


QString EBOOT::Content_ID() {
	if (!f.isOpen())
		return false;
	QDataStream in(&f);
	in.device()->seek(0x450);
	QByteArray ContentID(0x24, '\0');
	if (in.readRawData(ContentID.data(), 0x24) != 0x24)
		return false;
	ContentID.replace("PATCH", "GAME0");
	ContentID.replace("SHIP0", "GAME0");
	return ContentID;
}
