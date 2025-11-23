#pragma once

#include "StelModule.hpp"

class QSlider;
class QLabel;
class QWidget;

class ObliquityControlModule : public StelModule
{
    Q_OBJECT
public:
    ObliquityControlModule(StelCore* core);
    virtual bool configureGui(bool show = true) override;
    virtual void deinit() override;

private slots:
    void onSliderChanged(int value);

private:
    QWidget* m_widget;
    QSlider* m_slider;
    QLabel* m_label;
};
