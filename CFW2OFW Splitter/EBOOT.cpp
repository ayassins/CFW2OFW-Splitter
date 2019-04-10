#include "EBOOT.h"


EBOOT::EBOOT(const QString &path) :path(path) {
	f.setFileName(path);
}


EBOOT::~EBOOT() {
	f.close();
}


bool EBOOT::ismagic() {
	return ((magic == 0x53434500));
}


bool EBOOT::isversion() {
	return ((version == 0x02000000));
}


bool EBOOT::open(QFile::OpenMode flags) {
	if (!f.open(flags))
		return false;
	QDataStream in(&f);
	in.setByteOrder(QDataStream::BigEndian);
	in >> magic >> version;
	if (!ismagic())
		return false;
	if (!isversion())
		return false;
}


QString EBOOT::Content_ID() {
	//if (!iseboot())
		//return QString();
	QDataStream in(&f);
	in.device()->seek(0x450);
	QByteArray ContentID(0x24, '\0');
	in.readRawData(ContentID.data(), 0x24);
	ContentID.replace("PATCH", "GAME0");
	ContentID.replace("SHIP0", "GAME0");
	return ContentID;
}