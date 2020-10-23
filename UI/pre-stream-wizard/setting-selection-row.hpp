#pragma once

#include <QWidget>
#include <QWizardPage>
#include <QString>
#include <QLabel>
#include <QCheckBox>

#include "pre-stream-current-settings.hpp"

namespace StreamWizard {

/*
* Shows user encoder configuration options and allows them to select and apply 
* each. For exmaple can apply a resolution limit but opt-out of using b-frames 
* even if recommended. 
*/

class SelectionRow : public QWidget {
	Q_OBJECT

public:
	SelectionRow(QWidget *parent = nullptr);

	// User facing name to be shown to the user. ("Resolution")
	void setName(QString newName);
	QString getName();

	// Value in a user-presentable manner. ("1920x180p")
	void setValueLabel(QString newValue);
	QString getValueLabel();

	// Key to mapping property to Settings Map
	void setPropertyKey(QString newKey);
	QString getPropertyKey();

signals:
	// User changed if they want to apply an option
	void didChangeSelectedStatus(QString propertyKey, bool selected);

private:
	void createLayout();
	void checkboxUpdated();
	void updateLabel();

	// Visual from upper class
	QString name_;
	QString valueLabel_;
	QString propertyKey_;

	// Layout and subwidgets
	QString separator_ = ": ";
	QString checkboxValueString_;
	QCheckBox *checkbox_;

}; // class SelectionRow

} // namespace StreamWizard
