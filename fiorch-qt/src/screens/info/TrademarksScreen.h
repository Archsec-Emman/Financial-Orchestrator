#pragma once
#include <QWidget>

namespace fiorch::screens {

class TrademarksScreen : public QWidget {
    Q_OBJECT
  public:
    explicit TrademarksScreen(QWidget* parent = nullptr);

  signals:
    void navigate_back();
};

} // namespace fiorch::screens
