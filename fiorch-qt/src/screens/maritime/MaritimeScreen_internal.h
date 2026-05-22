// src/screens/maritime/MaritimeScreen_internal.h
//
// Private header — included only by MaritimeScreen*.cpp TUs. Hosts the
// shared token-formatter helpers (C/F) and the styled-QSS factories used
// across the partial-class split files. Marked `inline` to be safely
// included from multiple TUs.

#pragma once

#include "ui/theme/Theme.h"

#include <QString>

namespace fiorch::screens::maritime_internal {

// Token → QString — works for both ColorToken and FontFamilyToken.
inline QString C(const fiorch::ui::ColorToken& t) {
    return QString::fromLatin1(t.get());
}
inline QString F(const fiorch::ui::fonts::FontFamilyToken& t) {
    return QString::fromLatin1(t.get());
}

inline QString table_ss() {
    return QString("QTableWidget { background:%1; color:%2; gridline-color:%3;"
                   "font-family:%4; font-size:%5px; border:none; }"
                   "QTableWidget::item { padding:4px 6px; }"
                   "QTableWidget::item:selected { background:%6; }"
                   "QTableWidget::item:alternate { background:%7; }"
                   "QHeaderView::section { background:%8; color:%9; font-weight:700;"
                   "padding:6px 8px; border:1px solid %3; font-family:%4; font-size:%5px; }")
        .arg(C(fiorch::ui::colors::BG_BASE), C(fiorch::ui::colors::TEXT_PRIMARY),
             C(fiorch::ui::colors::BORDER_DIM), F(fiorch::ui::fonts::DATA_FAMILY))
        .arg(fiorch::ui::fonts::SMALL)
        .arg(C(fiorch::ui::colors::BG_HOVER), C(fiorch::ui::colors::ROW_ALT),
             C(fiorch::ui::colors::BG_RAISED), C(fiorch::ui::colors::TEXT_SECONDARY));
}

inline QString input_ss() {
    return QString("QLineEdit, QDoubleSpinBox { background:%1; color:%2; border:1px solid %3;"
                   "font-family:%4; font-size:%5px; padding:6px 8px; border-radius:2px; }"
                   "QLineEdit:focus, QDoubleSpinBox:focus { border-color:%6; }")
        .arg(C(fiorch::ui::colors::BG_SURFACE), C(fiorch::ui::colors::TEXT_PRIMARY),
             C(fiorch::ui::colors::BORDER_MED), F(fiorch::ui::fonts::DATA_FAMILY))
        .arg(fiorch::ui::fonts::SMALL)
        .arg(C(fiorch::ui::colors::AMBER));
}

inline QString btn_primary_ss() {
    return QString("QPushButton { background:%1; color:%2; font-family:%3; font-size:%4px;"
                   "font-weight:700; border:none; padding:8px; border-radius:2px; letter-spacing:1px; }"
                   "QPushButton:hover { background:%5; }")
        .arg(C(fiorch::ui::colors::AMBER), C(fiorch::ui::colors::BG_BASE), F(fiorch::ui::fonts::DATA_FAMILY))
        .arg(fiorch::ui::fonts::SMALL)
        .arg(C(fiorch::ui::colors::AMBER_DIM));
}

inline QString btn_outline_ss() {
    return QString("QPushButton { background:transparent; color:%1; font-family:%2; font-size:%3px;"
                   "font-weight:700; border:1px solid %1; padding:6px; border-radius:2px; }"
                   "QPushButton:hover { background:%4; }")
        .arg(C(fiorch::ui::colors::WARNING), F(fiorch::ui::fonts::DATA_FAMILY))
        .arg(fiorch::ui::fonts::SMALL)
        .arg(C(fiorch::ui::colors::BG_HOVER));
}

inline QString section_label_ss() {
    return QString("color:%1; font-size:9px; font-weight:700; font-family:%2;"
                   "letter-spacing:1px; padding-bottom:4px; border-bottom:1px solid %3;")
        .arg(C(fiorch::ui::colors::AMBER), F(fiorch::ui::fonts::DATA_FAMILY),
             C(fiorch::ui::colors::BORDER_DIM));
}

inline QString tiny_label_ss() {
    return QString("color:%1; font-size:8px; font-weight:700; font-family:%2; letter-spacing:1px;")
        .arg(C(fiorch::ui::colors::TEXT_TERTIARY), F(fiorch::ui::fonts::DATA_FAMILY));
}

inline QString detail_text_ss() {
    return QString("color:%1; font-size:9px; font-family:%2;")
        .arg(C(fiorch::ui::colors::TEXT_SECONDARY), F(fiorch::ui::fonts::DATA_FAMILY));
}

} // namespace fiorch::screens::maritime_internal
