#include "notifications-widget.hpp"
#include "window-basic-main.hpp"
#include <QDesktopServices>
#include <QSpacerItem>

OBSNotifications::OBSNotifications(enum obs_notify_type type, QString text,
				   enum obs_notify_action action_, QWidget *parent)
	: QMdiArea(parent), action(action_)
{
	layout = new QHBoxLayout();
	layout->setContentsMargins(10, 0, 10, 0);
	layout->setSpacing(10);
	notificationText = new QLabel(text);
	notificationText->setStyleSheet("background: transparent;");
	notificationText->setProperty("themeID", "notifyText");

	closeButton = new ClickableLabel();
	closeButton->setStyleSheet("background: transparent;");
	closeButton->setFixedSize(16, 16);
	closeButton->setProperty("themeID", "notifyCloseButton");

	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	if (action != OBS_NOTIFY_ACTION_DO_NOTHING) {
		button = new QPushButton();
		button->setStyleSheet("background: transparent;");
		button->setProperty("themeID", "notifyButton");
		connect(button, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
	}

	icon = new QLabel();

	QColor color;

	if (type == OBS_NOTIFY_TYPE_INFO) {
		icon->setProperty("themeID", "notifyIconInfo");
		color.setRgb(90, 163, 89);
	} else if (type == OBS_NOTIFY_TYPE_WARNING) {
		icon->setProperty("themeID", "notifyIconWarning");
		color.setRgb(192, 128, 0);
	} else if (type == OBS_NOTIFY_TYPE_ERROR) {
		icon->setProperty("themeID", "notifyIconError");
		color.setRgb(192, 0, 0);
	}

	QBrush brush(color);
	setBackground(brush);

	icon->setFixedSize(32, 32);
	icon->setStyleSheet("background: transparent;");

	layout->addWidget(icon);
	layout->addWidget(notificationText);
	layout->addItem(new QSpacerItem(25, 0));

	if (button) {
		layout->addWidget(button);
	}

	layout->addStretch();
	layout->addWidget(closeButton);

	setLayout(layout);
}

OBSNotifications::~OBSNotifications()
{
	deleteLater();
}

void OBSNotifications::ButtonClicked()
{
	OBSBasic *main = reinterpret_cast<OBSBasic *>(App()->GetMainWindow());

	switch (action) {
	case OBS_NOTIFY_ACTION_OPEN_URL:
		QDesktopServices::openUrl(QUrl(buttonURL));
		break;
	case OBS_NOTIFY_ACTION_OPEN_SETTINGS:
		main->on_action_Settings_triggered();
		break;
	case OBS_NOTIFY_ACTION_OPEN_PROPERTIES:
		if (source)
			main->CreatePropertiesWindow(source);
		break;
	default:
		break;
	}
}

void OBSNotifications::SetMessage(QString text)
{
	notificationText->setText(text);
}

void OBSNotifications::SetURL(QString url)
{
	buttonURL = url;
}

void OBSNotifications::SetButtonText(QString newText)
{
	if (button)
		button->setText(newText);
}

void OBSNotifications::SetSource(obs_source_t *newSource)
{
	source = newSource;
}
