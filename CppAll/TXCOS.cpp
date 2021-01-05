#include "TXCOS.h"
#include <QSettings>
//简易实现腾讯cos

TXCOS::TXCOS(const QString& region, const QString& appid, const QString& bucket, QString& SecretID, const QString& SecretKey, const QString& token/*=""*/)
	:_region(region), _appid(appid),_bucket(bucket), _sid(SecretID), _skey(SecretKey), _token(token)
{

}

TXCOS::TXCOS()
{
	QSettings server_config("server_config.ini", QSettings::IniFormat);
	//读取配置文件进行初始化
	_region = server_config.value("server/region").toString();
	_sid = server_config.value("server/secret_id").toString();
	_skey = server_config.value("server/secret_key").toString();
	_bucket = server_config.value("server/bucket").toString();
	_appid = server_config.value("server/appid").toString();
}

TXCOS::~TXCOS()
{

}

bool TXCOS::sendFile(const QString& filename,const QString& uri)
{
	QByteArray data = ch::qReadAll(filename);
	QString _uri = filename;
	if (uri!="")
	{
		_uri = uri;
	}
	return sendFile(data, _uri);
}

bool TXCOS::sendFile(QByteArray data, const QString uri)
{
	QString _uri = uri;
	if (_uri[0] != '/')
	{
		_uri = "/" + _uri;
	}
	if (!data.size())
	{
		return false;
	}
	httplib::Client client(gethost().toStdString());
	client.set_read_timeout(30, 100);
	auto host = gethost();
	httplib::Headers header{ { "host",gethost().toStdString() },{ "Authorization",getauth(_uri).toStdString() } };
	//数据的提供者 这个offset 和 length 都是自动控制的
	httplib::ContentProvider provider = [&](size_t offset, size_t length, httplib::DataSink &sink) {
		sink.write(&data.data()[offset], length);
	};

	auto res = client.Put(_uri.toUtf8(), header, data.size(), provider, "");
	qDebug() << "send file res:" << res->body.c_str();
	return true;
}

QString TXCOS::gethost()
{
	return QString("%1-%2.cos.ap-%3.myqcloud.com").arg(_bucket).arg(_appid).arg(_region);
}

QString TXCOS::geturl(const QString& filename, const QMap<QString, QString>& parameters = {})
{
	QString _filename = filename;
	if (filename[0]=='/')
	{
		_filename = filename.mid(1);
	}
	QString uri = QString("https://%1-%2.cos.ap-%3.myqcloud.com/%4").arg(_bucket).arg(_appid).arg(_region).arg(_filename);
	if (parameters.size())
	{
		QStringList ps;
		for (auto &p:parameters)
		{
			ps << (p + "=" + parameters[p]);
		}
		uri += "?" + ps.join("&");
	}
	return uri;
}

QString TXCOS::getauth(const QString& filename, const QString& method, const QMap<QString, QString>& parameters = {})
{
	QString parameter_keys = parameters.keys().join(';');
	QStringList key_values;
	for (auto& p : parameters.keys())
	{
		key_values<< (p + "=" +parameters[p]);
	}
	QString parameter_key_values = key_values.join("&");
	//根据当前时间获取时间
	QDateTime time_beg = QDateTime::currentDateTime();
	//十分钟过期
	QDateTime time_end = time_beg.addSecs(60 * 10);
	QString time_str = QString("%1;%2").arg(time_beg.toTime_t()).arg(time_end.toTime_t());
	//1. 计算 SignKey
	//HMAC-SHA1(SecretKey,"[q-key-time]")
	QString sign_key = ch::hmacsha1(_skey, time_str);
	//2. 生成 HttpString
	//[HttpMethod]\n[HttpURI]\n[HttpParameters]\n[HttpHeaders]\n
	QString http_str = QString("%1\n%2\n%3\n%4\n")
		.arg(method)
		.arg(filename)
		.arg(parameter_key_values)
		.arg(QString("host=%1").arg(gethost()));
	//put\n/1.png\n\ncontent-md5=34%2B%2B3lUUNnRVx6roO06kZw%3D%3D&host=data-1300298607.cos.ap-chengdu.myqcloud.com\n
	//3. 生成 StringToSign
	//[q-sign-algorithm]\n[q-sign-time]\nSHA1-HASH(HttpString)\n
	QString string_to_sign = QString("%1\n%2\n%3\n")
		.arg("sha1")
		.arg(time_str)
		.arg(QString(QCryptographicHash::hash(http_str.toUtf8(), QCryptographicHash::Sha1).toHex()));
	//sha1\n1609675069;1609682269\n89a43fc5c4634f4d047d6c8744c52f20ae926971\n
	//4. 生成 Signature
	QString signature = ch::hmacsha1(sign_key, string_to_sign);
	//HMAC-SHA1(SignKey,StringToSign)
	//5. 拼接 Authorization
	//q-sign-algorithm=[q-sign-algorithm]&q-ak=[SecretId]&q-sign-time=[q-sign-time]&q-key-time=[q-key-time]&q-header-list=[q-header-list]&q-url-param-list=[q-url-param-list]&q-signature=[q-signature]
	QString auth = QString("q-sign-algorithm=sha1&q-ak=%1&q-sign-time=%2&q-key-time=%2&q-header-list=%3&q-url-param-list=%4&q-signature=%5") \
		.arg(_sid).arg(time_str).arg("host").arg(parameter_keys).arg(signature);
	return auth;

}
