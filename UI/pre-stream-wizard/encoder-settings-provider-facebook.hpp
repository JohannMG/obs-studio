#pragma once

#include "encoder-settings-provider-abstract.hpp"

#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "pre-stream-current-settings.hpp"

namespace StreamWizard {

class FacebookEncoderSettingsProvider : public AbstractEncoderSettingsProvider {
	Q_OBJECT

public:
	FacebookEncoderSettingsProvider(QWidget *parent = nullptr);
	~FacebookEncoderSettingsProvider();

	bool setEncoderRequest(
		QSharedPointer<EncoderSettingsRequest> request) override;
	void run() override;

	// signals from abstract class
	Q_SIGNAL void returnedEncoderSettings(
		QSharedPointer<EncoderSettingsResponse> response) override;
	Q_SIGNAL void returnedError(QString title,
				    QString description) override;
};

} // namespace StreamWizard
