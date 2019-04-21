#include "EDAT.h"


EDAT::EDAT(const QString & path) {
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


EDAT::~EDAT() {
	close();
}


bool EDAT::isedat() {
	try {
		if (f.isOpen())
			//if ((magic == 0x53434500) && (version == 0x00000002))
				return true;
	}
	catch (...) {
		return false;
	}
	return false;
}


bool EDAT::close() {
	if (!isedat())
		return false;
	f.close();
	return true;
}


QByteArray EDAT::contentid() {
	//if (!isedat())
		//return QByteArray();
	try {
		QDataStream in(&f);
		in.device()->seek(0x10);
		QByteArray ContentID(0x24, '\0');
		if (in.readRawData(ContentID.data(), 0x24) == 0x24)
			return ContentID;
	}
	catch (...) {
		return QByteArray();
	}
	return QByteArray();
}
