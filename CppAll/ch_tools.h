#pragma once
//��д�ݹ�ľ�д��cpp���棬�����ֱ��д��ͷ�ļ��������
#include "ch_switch.h"
#include <string>
#ifdef QT_ON
#include <QString>
#include <QImage>
#include <QDir>
#include <QFileInfoList>
#include <QTextCodec>
//ת��ΪQString
//from stringliteral to qstring
#define _Q(s) (QString::fromLocal8Bit(s))
//from std::string to qstring
#define _QS(s) (QString::fromLocal8Bit(s.c_str()))
//from qstring to std::string
#define _STR(qstr) (qstr.toLocal8Bit().data())
#endif
#ifdef OPENCV_ON
#include <opencv2/opencv.hpp>

#endif // OPENCV_ON

namespace ch {
	
#ifdef QT_ON
	//std::string <-> QString
	inline std::string toString(const QString& qstr) {
#if(defined _WIN32 || defined _WIN64)
		QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
		if (!pCodec) return "";
		QByteArray arr = pCodec->fromUnicode(qstr);
		std::string cstr = arr.data();
		return cstr;
#else
		QByteArray arr = qstr.toUtf8();
		std::string cstr = arr.data();
		return cstr;
#endif
	}
	inline static QString toQString(const std::string& cstr)
	{
#if(defined _WIN32 || defined _WIN64)
		QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
		if (!pCodec) return "";

		QString qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
		return qstr;
#else
		QString qstr = QString::fromUtf8(cstr.c_str(), cstr.length());
		return qstr;
#endif
	}

	inline std::string toString2(const QString& qstr) {
		return qstr.toLocal8Bit().data();
	}

	inline QString toQString2(const std::string str) {
		return QString::fromLocal8Bit(str.c_str());
	}
	//remove dir by loop rmove files
	inline bool removeDirForce(const QString& folder_name) {
		QDir dir(folder_name);
		QFileInfoList fileList;
		QFileInfo curFile;
		if (!dir.exists()) { return false; }//�ļ����棬�򷵻�false
		fileList = dir.entryInfoList(QDir::Dirs | QDir::Files
			| QDir::Readable | QDir::Writable
			| QDir::Hidden | QDir::NoDotAndDotDot
			, QDir::Name);
		while (fileList.size() > 0)
		{
			int infoNum = fileList.size();
			for (int i = infoNum - 1; i >= 0; i--)
			{
				curFile = fileList[i];
				if (curFile.isFile())//������ļ���ɾ���ļ�
				{
					QFile fileTemp(curFile.filePath());
					fileTemp.remove();
					fileList.removeAt(i);
				}
				if (curFile.isDir())//������ļ���
				{
					QDir dirTemp(curFile.filePath());
					QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
						| QDir::Readable | QDir::Writable
						| QDir::Hidden | QDir::NoDotAndDotDot
						, QDir::Name);
					if (fileList1.size() == 0)//�²�û���ļ����ļ���
					{
						dirTemp.rmdir(".");
						fileList.removeAt(i);
					}
					else//�²����ļ��л��ļ�
					{
						for (int j = 0; j < fileList1.size(); j++)
						{
							if (!(fileList.contains(fileList1[j])))
								fileList.append(fileList1[j]);
						}
					}
				}
			}
		}
		return true;
	}
#endif

#if(defined QT_ON && defined OPENCV_ON)

	//QImage covert to opencv mat,it depend on Qimage's format
	inline cv::Mat QImage2cvMat(const QImage& image) {
		cv::Mat out;
		switch (image.format()) {
		case QImage::Format_Invalid:
		{
			cv::Mat empty;
			empty.copyTo(out);
			break;
		}
		case QImage::Format_RGB32:
		{
			//���ֺ���͸��ͨ����ͼ
			cv::Mat view(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
			view.copyTo(out);
			break;
		}
		case QImage::Format_RGB888:
		{
			cv::Mat view(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine());
			cv::cvtColor(view, out, cv::COLOR_RGB2BGR);
			break;
		}
		default:
		{
			QImage conv = image.convertToFormat(QImage::Format_ARGB32);
			cv::Mat view(conv.height(), conv.width(), CV_8UC4, (void *)conv.constBits(), conv.bytesPerLine());
			view.copyTo(out);
			break;
		}
		}
		return out;
	}
	//opencv mat to QImage,depend on mat type
	inline QImage cvMat2QImage(const cv::Mat& mat) {
		switch (mat.type())
		{
			// 8λ4ͨ��
		case CV_8UC4:
		{
			QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
			return image;
		}

		// 8λ3ͨ��
		case CV_8UC3:
		{
			QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
			return image.rgbSwapped();
		}

		// 8λ��ͨ��
		case CV_8UC1:
		{
			static QVector<QRgb>  sColorTable;
			// only create our color table once
			if (sColorTable.isEmpty())
			{
				for (int i = 0; i < 256; ++i)
					sColorTable.push_back(qRgb(i, i, i));
			}
			QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
			image.setColorTable(sColorTable);
			return image;
		}

		default:
			qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
			break;
		}
		return QImage();
	}
#endif

#ifdef OPENCV_ON
	inline cv::Mat fusionImage(const std::vector<cv::Mat>& images) {
		//https://docs.opencv.org/master/d3/db7/tutorial_hdr_imaging.html
		//ͼƬ���ں�
		cv::Mat fusion;
		std::vector<cv::Mat> images;
		//��⺯��
		if (images.size()==0 || images[0].rows==0 || images[0].cols == 0)
		{
			return fusion;
		}
		for (auto i=1;i<images.size();i++)
		{
			if (images[i].size !=images[0].size)
			{
				return fusion;
			}
		}
		cv::Ptr<cv::MergeMertens> merge_mertens = cv::createMergeMertens();
		merge_mertens->process(images, fusion);
		return fusion;
	}
#endif // OPENCV_ON


}