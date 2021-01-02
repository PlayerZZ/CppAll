#pragma once

#include <QObject>

class TXCOS : public QObject
{
	Q_OBJECT

public:
	TXCOS(QObject *parent);
	~TXCOS();
};
