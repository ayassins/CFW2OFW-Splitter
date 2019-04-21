#include "EBOOT.h"


EBOOT::EBOOT(const QString &path) {
	try {
		f.setFileName(path);
		f.open(QFile::ReadOnly);
		QDataStream in(&f);
		in.setByteOrder(QDataStream::BigEndian);
		in >> magic >> version;
	}
	catch (...) {
	}
}


EBOOT::~EBOOT() {
	close();
}


bool EBOOT::iseboot() {
	try{
		if (f.isOpen())
			if ((magic == 0x53434500) && (version == 0x00000002))
				return true;
	}
	catch (...){
		return false;
	}
	return false;
}


bool EBOOT::close() {
	if (!iseboot())
		return false;
	f.close();
	return true;
}


QByteArray EBOOT::contentid() {
	if (!iseboot())
		return QByteArray();
	try {
		QDataStream in(&f);
		in.device()->seek(0x450);
		QByteArray ContentID(0x24, '\0');
		if (in.readRawData(ContentID.data(), 0x24) == 0x24)
			return ContentID.replace("PATCH", "GAME0").replace("SHIP0", "GAME0");
	}
	catch (...) {
		return QByteArray();
	}
	return QByteArray();
}
