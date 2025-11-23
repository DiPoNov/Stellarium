#include "ObliquityControlModule.hpp"
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include "Planet.hpp"  // твой класс Planet с `setForcedObliquityRadians` и `enableForcedObliquity`

#define _USE_MATH_DEFINES
#include <cmath>

ObliquityControlModule::ObliquityControlModule(StelCore* core)
    : StelModule(core)
    , m_widget(nullptr)
    , m_slider(nullptr)
    , m_label(nullptr)
{
}

bool ObliquityControlModule::configureGui(bool show)
{
    if (!m_widget) {
        m_widget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(m_widget);

        m_label = new QLabel(m_widget);
        m_label->setText("Obliquity: 0°");
        layout->addWidget(m_label);

        m_slider = new QSlider(Qt::Horizontal, m_widget);
        // Диапазон: 0° — 180° (пример)
        m_slider->setRange(0, 180);
        // Начальное значение — текущее obliquity (в градусах)
        double currentRad = Planet::getRotObliquity(2451545.0); // J2000 или любой JDE
        int currentDeg = static_cast<int>(currentRad * 180.0 / M_PI);
        m_slider->setValue(currentDeg);
        m_label->setText(QString("Obliquity: %1°").arg(currentDeg));

        QObject::connect(m_slider, &QSlider::valueChanged, this, &ObliquityControlModule::onSliderChanged);

        layout->addWidget(m_slider);
        m_widget->setLayout(layout);
    }

    if (show) {
        m_widget->show();
    } else {
        m_widget->hide();
    }

    return true;
}

void ObliquityControlModule::onSliderChanged(int value)
{
    m_label->setText(QString("Obliquity: %1°").arg(value));
    double radians = value * M_PI / 180.0;
    Planet::setForcedObliquityRadians(radians);
    Planet::enableForcedObliquity(true);
}

void ObliquityControlModule::deinit()
{
    if (m_widget) {
        m_widget->close();
        delete m_widget;
        m_widget = nullptr;
    }
}
