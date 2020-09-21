#pragma once
/*
** Abstract class for the Pre Stream Encoder setup wizard.
** Allows services to create their own configuration classes that the wizard can 
** use to return encoder settinger per-service
*/

#include <QObject>
#include <QSharedPointer>
#include <QString>

#include "pre-stream-current-settings.hpp"

namespace StreamWizard {

class AbstractEncoderSettingsProvider : public QObject {
	Q_OBJECT

public:
	explicit AbstractEncoderSettingsProvider(QWidget *parent = nullptr);
	~AbstractEncoderSettingsProvider(){};

	// Pass in encoder request to use, returns FALSE is there is an error.
	virtual bool
	setEncoderRequest(QSharedPointer<EncoderSettingsRequest> request) = 0;

	// Uses the EncoderSettingsRequest to generate EncoderSettingsResponse
	// Does not return in sync becuase can be an async API call
	// Success: emits returnedEncoderSettings(...) with EncoderSettingsResponse
	// Failure: emits returnedError(QString title, QString description)
	virtual void run() = 0;

	// SIGNALS REQUIRED
	virtual void returnedEncoderSettings(
		QSharedPointer<EncoderSettingsResponse> response) = 0;
	virtual void returnedError(QString title, QString description) = 0;
};

} // namespace StreamWizard
