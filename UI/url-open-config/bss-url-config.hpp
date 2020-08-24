/*
Send this class potentially valid bss:// protocol configuration URLS sent via
either QApplication UrlOpen event or commandline args and then will emit 
with a signal or slot with the configuration changes requested if valid.


For Streaming info setup example (returns in url for example only)
___________
bss://settings?service=facebook
      &stream_type=rmtp
      &service_url=cnRtcHM6Ly9saXZlLWFwaS1zLmZhY2Vib29rLmNvbTo0NDMvcnRtcC8=
      &stream_key=NjQzNzgzMT9zX2JsPTEmc19zbWw9Mw==

 - URL is a String sent via protocol hook or -bss argument 
 - "service" can be a known service name to compare to 
 - "stream_type" will be the protocol to use also in the url
 - All other key/value pairs in are to be base 64 encoded 
 - "service_url" base64 UTF-8 encoded URL for streaming destination 
 - "stream_key" base64 UTF-8 encoded stream key
*/

#pragma once

#include <QObject>
#include <QString>

#include "bss-stream-setting-model.hpp"

class BssUrlConfig : public QObject {
	Q_OBJECT

public:
	explicit BssUrlConfig(QObject *parent = nullptr);
  void newUrl(const QString &submittedUrl);

signals:
	void newStreamSetting(StreamSettingModel settingModel);

private:
	void parseBssSettingsUrl(const QUrl &settingsUrl);
};
