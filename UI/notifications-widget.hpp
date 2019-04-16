#pragma once

#include "obs.h"
#include <QMdiArea>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "clickable-label.hpp"

class OBSNotifications : public QMdiArea {
	Q_OBJECT

private:
	QHBoxLayout *layout;
	QPushButton *button;
	QLabel *notificationText;
	QLabel *icon;
	ClickableLabel *closeButton;
	obs_source_t *source = nullptr;

	QString buttonURL;

	enum obs_notify_type type;
	enum obs_notify_action action;

private slots:
	void ButtonClicked();

public:
	OBSNotifications(enum obs_notify_type type, QString text,
			 enum obs_notify_action action_ = OBS_NOTIFY_ACTION_DO_NOTHING,
			 QWidget *parent = 0);

	~OBSNotifications();

	void SetURL(QString url);
	void SetMessage(QString text);
	void SetButtonText(QString newText);
	void SetSource(obs_source_t *newSource);
};
