#pragma once

#include <QObject>
#include "httplib.h"
#include "json.hpp"
#include <tinyxml2.h>
#include <QDateTime>
class TXCOS : public QObject
{
	Q_OBJECT

public:
	TXCOS(const QString& region,const QString& appid,const QString& bucket,QString& SecretID,const QString& SecretKey,const QString& token="");
	~TXCOS();
private:
	QString _region;
	QString _appid;
	QString _sid;
	QString _skey;
	QString _bucket;
	QString _token;
	QString _host;
	QString gethost();
	QString geturl(const QString& filename);
	QString getauth(const QString& filename);
};