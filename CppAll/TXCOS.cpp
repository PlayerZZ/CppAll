#include "TXCOS.h"
//简易实现腾讯cos
TXCOS::TXCOS(const QString& region, const QString& appid, const QString& bucket, QString& SecretID, const QString& SecretKey, const QString& token/*=""*/)
	:_region(region), _appid(appid),_bucket(bucket), _sid(SecretID), _skey(SecretKey), _token(token)
{

}

TXCOS::~TXCOS()
{

}

QString TXCOS::gethost()
{

	return QString("%1-%2.cos.ap-%3.myqcloud.com").arg(_bucket).arg(_appid).arg(_region);
}

QString TXCOS::geturl(const QString& filename)
{
	QString _filename = filename;
	if (filename[0]=='/')
	{
		_filename = filename.mid(1);
	}
	return QString("%1-%2.cos.ap-%3.myqcloud.com/%4").arg(_bucket).arg(_appid).arg(_region).arg(_filename);
}

QString TXCOS::getauth(const QString& filename)
{
	//根据当前时间获取时间
	QDateTime time_beg = QDateTime::currentDateTime();
	//十分钟过期
	QDateTime time_end = time_beg.addSecs(60 * 10);
	QString time_str = QString("%1;%2").arg(time_beg.toTime_t()).arg(time_end.toTime_t());
	//1. 计算 SignKey
	//HMAC-SHA1(SecretKey,"[q-key-time]")
	//2. 生成 HttpString
	//[HttpMethod]\n[HttpURI]\n[HttpParameters]\n[HttpHeaders]\n
	//put\n/1.png\n\ncontent-md5=34%2B%2B3lUUNnRVx6roO06kZw%3D%3D&host=data-1300298607.cos.ap-chengdu.myqcloud.com\n
	//3. 生成 StringToSign
	//[q-sign-algorithm]\n[q-sign-time]\nSHA1-HASH(HttpString)\n
	//sha1\n1609675069;1609682269\n89a43fc5c4634f4d047d6c8744c52f20ae926971\n
	//4. 生成 Signature
	//HMAC-SHA1(SignKey,StringToSign)
	//5. 拼接 Authorization
	//q-sign-algorithm=[q-sign-algorithm]&q-ak=[SecretId]&q-sign-time=[q-sign-time]&q-key-time=[q-key-time]&q-header-list=[q-header-list]&q-url-param-list=[q-url-param-list]&q-signature=[q-signature]


	return "";

}
