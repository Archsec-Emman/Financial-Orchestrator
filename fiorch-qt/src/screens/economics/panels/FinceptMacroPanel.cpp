// The script fincept_macro.py does not yet exist.
// This panel shows a Coming Soon state with description of planned data.
// When fincept_macro.py is ready, implement on_fetch() and on_result() here.

#include "core/logging/Logger.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace fiorch::screens {
namespace {

} // namespace

    build_base_ui(this);
    // No service connection — Coming Soon panel
}

               "Planned data:\n"
               "  · Central bank rates (40+ countries)\n"
               "  · Sovereign debt metrics\n"
               "  · Global inflation dashboard\n"
               "  · Emerging market indicators\n\n"
               "Check back in a future release");
}

    auto* lbl = new QLabel("FINCEPT MACRO — COMING SOON");
    lbl->setStyleSheet(ctrl_label_style() + "letter-spacing:1px;");
    thl->addWidget(lbl);
}

               "This panel will be enabled in a future release.");
}

    // No-op until fincept_macro.py is implemented
}

} // namespace fiorch::screens
