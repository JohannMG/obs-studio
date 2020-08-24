#include "bss-url-config.hpp"

#include <QUrl>
#include <QUrlQuery>
#include <QPair>

BssUrlConfig::BssUrlConfig(QObject *parent) : QObject(parent)
{
	//nop
}

void BssUrlConfig::newUrl(const QString &submittedUrl)
{
	QUrl settingsUrl(submittedUrl, QUrl::TolerantMode);
	if (!settingsUrl.isValid)
		return;

	int schemeCompare = QString::compare(settingsUrl.scheme(), "bss",
					     Qt::CaseInsensitive);
	if (schemeCompare != 0)
		return;

	int settingsCompare = QString::compare(settingsUrl.host(), "settings",
					       Qt::CaseInsensitive);
	if (settingsCompare == 0) {
		parseBssSettingsUrl(settingsUrl);
	}
}

void BssUrlConfig::parseBssSettingsUrl(const QUrl &settingsUrl)
{
  if (settingsUrl.isEmpty)
    return;

	QUrlQuery settingsQuery(settingsUrl.query(QUrl::PrettyDecoded));
	if (settingsQuery.isEmpty())
		return;

	struct StreamSettingModel newModel = {
		StringForKey(settingsQuery, "service"),
		StringForKey(settingsQuery, "stream_type"),
		UrlForKey(settingsQuery, "service_url"),
		StringForKey(settingsQuery, "stream_key"),
	};

	emit BssUrlConfig::newStreamSetting(newModel);
}

QString StringForKey(const QUrlQuery &settingsQuery, const QString &key)
{
	return settingsQuery.queryItemValue(key, QUrl::FullyDecoded);
}

QUrl UrlForKey(const QUrlQuery &settingsQuery, const QString &key)
{
	QString urlString = StringForKey(settingsQuery, key);
	return QUrl(urlString, QUrl::StrictMode);
}
