// Script fincept_macro.py does not yet exist — shows a Coming Soon panel.
// When the script is ready, this panel will be updated.
#pragma once

#include "screens/economics/panels/EconPanelBase.h"

namespace fiorch::screens {

    Q_OBJECT
  public:
    void activate() override;

  protected:
    void build_controls(QHBoxLayout* thl) override;
    void on_fetch() override;
    void on_result(const QString& request_id, const services::EconomicsResult& result) override;
};

} // namespace fiorch::screens
