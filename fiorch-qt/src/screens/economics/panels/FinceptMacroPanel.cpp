// The script fincept_macro.py does not yet exist.
// This panel shows a Coming Soon state with description of planned data.
// When fincept_macro.py is ready, implement on_fetch() and on_result() here.

#include "screens/economics/panels/FinceptMacroPanel.h"

#include "core/logging/Logger.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace fiorch::screens {

FinceptMacroPanel::FinceptMacroPanel(QWidget* parent)
    : EconPanelBase("fincept_macro", "#8B5CF6", parent) {
    build_base_ui(this);
    // No service connection — Coming Soon panel
}

void FinceptMacroPanel::activate() {
    show_empty(tr("FINCEPT MACRO — COMING SOON\n\n"
                  "Planned data:\n"
                  "  · Central bank rates (40+ countries)\n"
                  "  · Sovereign debt metrics\n"
                  "  · Global inflation dashboard\n"
                  "  · Emerging market indicators\n\n"
                  "Check back in a future release"));
}

void FinceptMacroPanel::build_controls(QHBoxLayout* thl) {
    auto* lbl = new QLabel("FINCEPT MACRO — COMING SOON");
    lbl->setStyleSheet(ctrl_label_style() + "letter-spacing:1px;");
    thl->addWidget(lbl);
}

void FinceptMacroPanel::on_fetch() {
    // No-op until fincept_macro.py is implemented
}

void FinceptMacroPanel::on_result(const QString& request_id, const services::EconomicsResult& result) {
    Q_UNUSED(request_id);
    Q_UNUSED(result);
    show_empty(tr("Macro data source not yet available.\n"
                  "This panel will be enabled in a future release."));
}

} // namespace fiorch::screens
