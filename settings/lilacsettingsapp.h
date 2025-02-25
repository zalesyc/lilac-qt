#pragma once

#include "lilacsettings.h"

#include <QWidget>

namespace Ui {
class lilacsettingsapp;
}
namespace Lilac {
class SettingsApp : public QWidget {
    Q_OBJECT

   public:
    explicit SettingsApp(QWidget* parent = nullptr);
    ~SettingsApp();

   public slots:
    void defaults();
    void save();

   signals:
    void changed(bool changed);

   private:
    void initFromSettings();

   private:
    Ui::lilacsettingsapp* ui;
    LilacSettings* settings;
};
}  // namespace Lilac
