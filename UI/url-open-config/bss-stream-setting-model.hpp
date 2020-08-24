// Struct to be populated by bss-url-config and to be handed off. 

#pragma once 

#include <QString>
#include <QUrl>

struct StreamSettingModel {
  QString serviceName;
  QString streamType;
  QUrl serviceUrl;
  QString streamKey;
};
