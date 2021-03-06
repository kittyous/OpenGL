#include "stdafx.h"

#include "QSFMLWidget.h"
#include "qnamespace.h"                  // for FocusPolicy::StrongFocus, WidgetAttribute::WA_NoSystemBackground, WidgetAttribute::WA_OpaquePaintEvent, WidgetAttribute::WA_PaintOnScreen
#include "SFML/Window/WindowHandle.hpp"  // for WindowHandle
#include "SFML/System.hpp" 
#include "windef.h"                      // for HWND__
#include <stddef.h>                      // for NULL

QSFMLWidget::QSFMLWidget(QWidget *parent) : QWidget(parent), m_initialized(false)
{
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	setFocusPolicy(Qt::ClickFocus);
}

QPaintEngine *QSFMLWidget::paintEngine() const {
	return NULL;
}

void QSFMLWidget::showEvent(QShowEvent *event) {
	if (m_initialized == false) {
#ifdef Q_WS_X11
		XFlush(QX11info::display())
#endif
			sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 0;
		settings.majorVersion = 4;
		settings.minorVersion = 4;
		sf::RenderWindow::create(reinterpret_cast<sf::WindowHandle>(winId()), settings);
		onInit();
		connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
		m_timer.start(16);
		m_initialized = true;
	}
}

void QSFMLWidget::paintEvent(QPaintEvent *event) {
	RenderWindow::clear();
	onUpdate();
	RenderWindow::display();
}

void QSFMLWidget::onInit() {
	//To be overidden
}

void QSFMLWidget::onUpdate() {
	//To be overidden
}