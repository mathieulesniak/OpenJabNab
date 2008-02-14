#include <QSettings>
#include <QCoreApplication>
#include <QDir>

#include "settings.h"
#include "log.h"

#include <iostream>

GlobalSettings::GlobalSettings()
{
	QString fileName = QDir(QCoreApplication::applicationDirPath()).absoluteFilePath("openjabnab.ini");
	if (QFile::exists(fileName))
		settings = new QSettings(fileName, QSettings::IniFormat);
	else
	{
		std::cerr << "Error, openjabnab.ini not found !" << std::endl;
		exit(-1);
	}
}

QVariant GlobalSettings::Get(QString const& key, QVariant const& defaultValue)
{
	if (!instance)
		instance = new GlobalSettings();

	if (instance->settings->contains(key))
		return instance->settings->value(key);
	else
	{
		Log::Warning(QString("Unknown setting : %1\n").arg(key));
		return defaultValue;
	}
}

bool GlobalSettings::HasKey(QString const& key)
{
	if (!instance)
		instance = new GlobalSettings();
	return instance->settings->contains(key);
}

GlobalSettings * GlobalSettings::instance = 0;