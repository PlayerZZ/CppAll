#pragma once

#include <QObject>
#include "httplib.h"
#include "json.hpp"
#include <tinyxml2.h>
#include <QDateTime>
#include "ch_tools.h"
#include <QMap>
class TXCOS : public QObject
{
	Q_OBJECT

public:
	TXCOS(const QString& region,const QString& appid,const QString& bucket,QString& SecretID,const QString& SecretKey,const QString& token="");
	TXCOS();
	~TXCOS();
	bool sendFile(QByteArray data, const QString uri);
	bool sendFile(const QString& filename,const QString& uri="");
	bool setBlockSize(const int& block_size) { _block_size = block_size; };
private:
	QString _region;
	QString _appid;
	QString _sid;
	QString _skey;
	QString _bucket;
	QString _token;
	QString _host;
	int _block_size = 5;//Mb
	QString gethost();
	QString geturl(const QString& filename, const QMap<QString, QString>& parameters = {});
	QString getauth(const QString& filename, const QString& method = "put", const QMap<QString,QString>& parameters = {});
	QString initMultipartUpload(const QString& uri);
};
