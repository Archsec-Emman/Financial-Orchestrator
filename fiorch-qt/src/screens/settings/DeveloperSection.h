#pragma once
// DeveloperSection.h — DataHub Inspector and other devtools surfaces.

#include <QWidget>

namespace fiorch::screens {

class DeveloperSection : public QWidget {
    Q_OBJECT
  public:
    explicit DeveloperSection(QWidget* parent = nullptr);
};

} // namespace fiorch::screens
