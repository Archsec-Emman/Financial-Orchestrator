// src/screens/alt_investments/AltInvestmentsScreen.cpp
//
// Core: kStyle, static field-builder helpers, ctor, show/hide events,
// format_value, display_error, set_loading, save_state/restore_state.
// Other concerns:
//   - AltInvestmentsScreen_Layout.cpp   — setup_ui + create_* panels
//   - AltInvestmentsScreen_Analysis.cpp — form/analysis/verdict rendering
#include "screens/alt_investments/AltInvestmentsScreen.h"

#include "core/logging/Logger.h"
#include "core/session/ScreenStateManager.h"
#include "services/python_cli/PythonCliService.h"
#include "storage/cache/CacheManager.h"
#include "ui/theme/Theme.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QPointer>
#include <QRegularExpression>
#include <QScrollArea>
#include <QShowEvent>
#include <QSplitter>

// ── Stylesheet ───────────────────────────────────────────────────────────────

namespace {
using namespace fiorch::ui;

static const QString kStyle =
    QStringLiteral("#altScreen { background: %1; }"

                   "#altHeader { background: %2; border-bottom: 2px solid %3; padding: 0 16px; }"
                   "#altHeaderTitle { color: %4; font-size: 13px; font-weight: 700; background: transparent; }"
                   "#altHeaderSub   { color: %5; font-size: 9px; letter-spacing: 0.8px; background: transparent; }"
                   "#altHeaderBadge { color: %6; font-size: 8px; font-weight: 700; letter-spacing: 0.5px;"
                   "  background: rgba(22,163,74,0.18); border: 1px solid rgba(22,163,74,0.4); padding: 2px 8px; }"

                   "#altLeftPanel { background: %7; border-right: 1px solid %8; }"
                   "#altLeftTitle  { color: %5; font-size: 9px; font-weight: 700; letter-spacing: 0.8px;"
                   "  background: %2; padding: 8px 12px; border-bottom: 1px solid %8; }"
                   "#altCatBtn { background: transparent; color: %5; border: none; border-bottom: 1px solid %8;"
                   "  text-align: left; font-size: 11px; padding: 9px 14px; }"
                   "#altCatBtn:hover { color: %4; background: %12; }"
                   "#altCatBtn[active=\"true\"] { color: %3; font-weight: 700;"
                   "  background: rgba(217,119,6,0.08); border-left: 3px solid %3; padding-left: 11px; }"

                   "#altCenterPanel { background: %1; }"
                   "#altCenterTitleBar { background: %2; border-bottom: 1px solid %8; }"
                   "#altCenterTitle { color: %4; font-size: 12px; font-weight: 700; background: transparent; }"
                   "#altCenterDesc  { color: %5; font-size: 10px; background: transparent; }"
                   "#altComboLabel  { color: %5; font-size: 9px; font-weight: 700;"
                   "  letter-spacing: 0.5px; background: transparent; }"

                   "#altFormPanel  { background: %7; border: 1px solid %8; }"
                   "#altFormHeader { background: %2; border-bottom: 1px solid %8; padding: 0 12px; }"
                   "#altFormTitle  { color: %4; font-size: 10px; font-weight: 700; background: transparent; }"
                   "#altFieldLabel { color: %5; font-size: 9px; font-weight: 700;"
                   "  letter-spacing: 0.5px; background: transparent; }"

                   "QLineEdit { background: %1; color: %4; border: 1px solid %8;"
                   "  padding: 5px 8px; font-size: 11px; }"
                   "QLineEdit:focus { border-color: %9; }"
                   "QDoubleSpinBox { background: %1; color: %4; border: 1px solid %8;"
                   "  padding: 5px 8px; font-size: 11px; }"
                   "QDoubleSpinBox:focus { border-color: %9; }"
                   "QDoubleSpinBox::up-button, QDoubleSpinBox::down-button { width: 0; }"
                   "QComboBox { background: %1; color: %4; border: 1px solid %8;"
                   "  padding: 5px 8px; font-size: 11px; }"
                   "QComboBox::drop-down { border: none; width: 18px; }"
                   "QComboBox QAbstractItemView { background: %2; color: %4; border: 1px solid %8;"
                   "  selection-background-color: %3; selection-color: %1; outline: none; }"

                   "#altAnalyzeBtn { background: %3; color: %1; border: none; padding: 7px 20px;"
                   "  font-size: 10px; font-weight: 700; letter-spacing: 0.5px; }"
                   "#altAnalyzeBtn:hover    { background: #FF8800; }"
                   "#altAnalyzeBtn:disabled { background: %10; color: %11; }"

                   "#altRightPanel { background: %7; border-left: 1px solid %8; }"
                   "#altRightTitle { color: %5; font-size: 9px; font-weight: 700; letter-spacing: 0.8px;"
                   "  background: %2; padding: 8px 12px; border-bottom: 1px solid %8; }"
                   "#altVerdictBadge  { font-size: 11px; font-weight: 700; padding: 4px 14px;"
                   "  letter-spacing: 0.5px; }"
                   "#altVerdictRating { color: %13; font-size: 14px; font-weight: 700; background: transparent; }"
                   "#altVerdictRec    { color: %4; font-size: 10px; background: transparent; }"

                   "#altMetricRow     { background: transparent; border-bottom: 1px solid %8; }"
                   "#altMetricKey     { color: %5; font-size: 10px; background: transparent; }"
                   "#altMetricVal     { color: %13; font-size: 10px; font-weight: 700; background: transparent; }"
                   "#altMetricSection { color: %3; font-size: 9px; font-weight: 700; letter-spacing: 0.8px;"
                   "  background: %2; padding: 4px 10px; border-top: 1px solid %8; }"
                   "#altMetricBullet    { color: %5;  font-size: 10px; background: transparent; }"
                   "#altMetricBulletVal { color: %4;  font-size: 10px; background: transparent; }"
                   "#altMetricWarn      { color: #FFD700; font-size: 10px; background: transparent; }"
                   "#altMetricGood      { color: %6;  font-size: 10px; background: transparent; }"
                   "#altMetricBad       { color: %14; font-size: 10px; background: transparent; }"

                   "#altStatusBar  { background: %2; border-top: 1px solid %8; }"
                   "#altStatusText { color: %5; font-size: 9px; background: transparent; }"
                   "#altStatusHigh { color: %13; font-size: 9px; background: transparent; }"

                   "QSplitter::handle { background: %8; }"
                   "QScrollBar:vertical { background: %1; width: 5px; border: none; }"
                   "QScrollBar::handle:vertical { background: %8; min-height: 20px; }"
                   "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }"
                   "QScrollBar:horizontal { height: 0; }")
        .arg(colors::BG_BASE())        // %1
        .arg(colors::BG_RAISED())      // %2
        .arg(colors::AMBER())          // %3
        .arg(colors::TEXT_PRIMARY())   // %4
        .arg(colors::TEXT_SECONDARY()) // %5
        .arg(colors::POSITIVE())       // %6
        .arg(colors::BG_SURFACE())     // %7
        .arg(colors::BORDER_DIM())     // %8
        .arg(colors::BORDER_BRIGHT())  // %9
        .arg(colors::AMBER_DIM())      // %10
        .arg(colors::TEXT_DIM())       // %11
        .arg(colors::BG_HOVER())       // %12
        .arg(colors::CYAN())           // %13
        .arg(colors::NEGATIVE())       // %14
    ;
} // namespace

namespace fiorch::screens {

using namespace fiorch::ui;

// ── Field factory helpers ────────────────────────────────────────────────────


static AltField text_field(const QString& key, const QString& label, const QString& def = "") {
    AltField f;
    f.key = key;
    f.label = label;
    f.type = AltField::Text;
    f.combo_items = def;
    return f;
}

static AltField spin_field(const QString& key, const QString& label, double def, double min_v, double max_v,
                           int dec = 2, const QString& pfx = "", const QString& sfx = "", bool div100 = false) {
    AltField f;
    f.key = key;
    f.label = label;
    f.type = AltField::Spin;
    f.default_val = def;
    f.min_val = min_v;
    f.max_val = max_v;
    f.decimals = dec;
    f.prefix = pfx;
    f.suffix = sfx;
    f.divide_100 = div100;
    return f;
}

static AltField combo_field(const QString& key, const QString& label, const QString& items) {
    AltField f;
    f.key = key;
    f.label = label;
    f.type = AltField::Combo;
    f.combo_items = items;
    return f;
}

// ── Category definitions ─────────────────────────────────────────────────────

static QList<AltCategory> build_categories() {
    return {
        {"bonds",
         "Bonds & Fixed Income",
         "#3B82F6",
         "B",
         {
             {"high-yield", "High-Yield Bonds", "Spread analysis, default probability, equity-like behavior"},
             {"em-bonds", "Emerging Market Bonds", "Yield spread, sovereign default risk, currency risk"},
             {"convertible-bonds", "Convertible Bonds", "Conversion premium, bond floor, upside participation"},
             {"preferred-stocks", "Preferred Stocks", "Current yield, call risk, dividend safety analysis"},
         }},
        {"real_estate",
         "Real Estate",
         "#8B5CF6",
         "RE",
         {
             {"real-estate", "Direct Property / REIT", "NOI, cap rate, DCF valuation, financing analysis"},
         }},
        {"hedge_funds",
         "Hedge Funds",
         "#EAB308",
         "HF",
         {
             {"hedge-funds", "Long/Short Equity", "Strategy metrics, fee impact, liquidity risk"},
             {"managed-futures", "Managed Futures / CTA", "Fee drag, trend following, crisis alpha analysis"},
             {"market-neutral", "Market Neutral", "Beta neutrality, factor exposure, leverage risk"},
         }},
        {"commodities",
         "Commodities",
         "#F97316",
         "C",
         {
             {"natural-resources", "Natural Resources", "Futures basis, contango/backwardation, roll yield"},
             {"pme", "Precious Metals Equities", "Correlation to metals, inflation hedge, drawdowns"},
         }},
        {"private_capital",
         "Private Capital",
         "#EC4899",
         "PE",
         {
             {"private-capital", "Private Equity / Venture Capital", "IRR, MOIC, DPI, RVPI, J-curve, fee drag"},
         }},
        {"annuities",
         "Annuities",
         "#22C55E",
         "AN",
         {
             {"annuities", "Fixed Annuity", "Payout analysis, breakeven years, inflation erosion"},
             {"variable-annuities", "Variable Annuity", "Total fee drag, tax deferral myth, vs. alternatives"},
             {"eia", "Equity-Indexed Annuity", "Crediting rate, upside cap limitations, surrender charges"},
             {"inflation-annuity", "Inflation-Indexed Annuity",
              "vs. fixed annuity, vs. TIPS ladder, longevity break-even"},
         }},
        {"structured",
         "Structured Products",
         "#06B6D4",
         "SP",
         {
             {"structured-products", "Structured Notes", "Complexity score, hidden costs, issuer credit risk"},
             {"leveraged-funds", "Leveraged ETFs (2x/3x)", "Volatility decay, path-dependency, holding cost"},
         }},
        {"inflation",
         "Inflation Protected",
         "#FB923C",
         "IP",
         {
             {"tips", "TIPS — Inflation-Linked Treasuries", "Real yield, inflation scenarios, tax efficiency"},
             {"ibonds", "I-Bonds — Series I Savings Bonds", "Composite rate, early redemption penalty, vs. TIPS"},
             {"stable-value", "Stable Value Funds", "Market-to-book ratio, crediting rate, wrap contract risk"},
         }},
        {"strategies",
         "Strategies & Analysis",
         "#67E8F9",
         "ST",
         {
             {"covered-calls", "Covered Call Strategy", "Tax consequences, opportunity cost, premium income"},
             {"sri", "SRI / ESG Funds", "Performance vs. benchmark, screening costs, approaches"},
             {"asset-location", "Tax-Efficient Asset Location",
              "Optimal account placement, muni bonds, annual tax drag"},
         }},
        {"crypto",
         "Digital Assets",
         "#F87171",
         "DA",
         {
             {"digital-assets", "Cryptocurrency", "Fundamental metrics, NVT ratio, market cap analysis"},
         }},
    };
}


// ── Constructor ──────────────────────────────────────────────────────────────

AltInvestmentsScreen::AltInvestmentsScreen(QWidget* parent) : QWidget(parent) {
    setObjectName("altScreen");
    setStyleSheet(kStyle);
    categories_ = build_categories();
    setup_ui();
    LOG_INFO("AltInvestments", "Screen constructed");
}

void AltInvestmentsScreen::showEvent(QShowEvent* e) {
    QWidget::showEvent(e);
}
void AltInvestmentsScreen::hideEvent(QHideEvent* e) {
    QWidget::hideEvent(e);
}

// ── UI Setup ─────────────────────────────────────────────────────────────────


QString AltInvestmentsScreen::format_value(const QJsonValue& v) const {
    if (v.isBool())
        return v.toBool() ? "Yes" : "No";
    if (v.isNull())
        return "\u2014";
    if (v.isString())
        return v.toString();
    if (v.isDouble()) {
        const double d = v.toDouble();
        // Looks like a 0–1 rate/fraction (not an integer)
        if (d > 0.0001 && d < 1.0 && d != static_cast<double>(static_cast<long long>(d)))
            return QString::number(d * 100.0, 'f', 2) + "%";
        if (qAbs(d) >= 1e12)
            return QString::number(d / 1e12, 'f', 2) + "T";
        if (qAbs(d) >= 1e9)
            return QString::number(d / 1e9, 'f', 2) + "B";
        if (qAbs(d) >= 1e6)
            return QString::number(d / 1e6, 'f', 2) + "M";
        if (d == static_cast<double>(static_cast<long long>(d)) && qAbs(d) < 1e15)
            return QString::number(static_cast<long long>(d));
        return QString::number(d, 'f', 4);
    }
    if (v.isArray())
        return QString("[%1 items]").arg(v.toArray().size());
    return "[object]";
}

void AltInvestmentsScreen::display_error(const QString& error) {
    verdict_badge_->setText("ERROR");
    verdict_badge_->setStyleSheet(QString("color:%1; background:rgba(220,38,38,0.15);"
                                          " font-size:11px; font-weight:700; padding:4px 14px;")
                                      .arg(colors::NEGATIVE()));
    verdict_rating_->clear();
    verdict_rec_->setText(error);
    while (metrics_layout_->count() > 0) {
        auto* item = metrics_layout_->takeAt(0);
        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }
    metrics_layout_->addStretch(1);
    LOG_ERROR("AltInvestments", error);
}

void AltInvestmentsScreen::set_loading(bool loading) {
    loading_ = loading;
    analyze_btn_->setEnabled(!loading);
    analyze_btn_->setText(loading ? "ANALYZING..." : "ANALYZE");
}

// ── IStatefulScreen ──────────────────────────────────────────────────────────

QVariantMap AltInvestmentsScreen::save_state() const {
    return {
        {"category", active_category_},
        {"analyzer", active_analyzer_},
    };
}

void AltInvestmentsScreen::restore_state(const QVariantMap& state) {
    const int cat = state.value("category", -1).toInt();
    const int ana = state.value("analyzer", -1).toInt();
    if (cat < 0 || cat >= categories_.size())
        return;
    on_category_changed(cat);
    if (ana >= 0 && ana < categories_[cat].analyzers.size())
        on_analyzer_changed(ana);
}

} // namespace fiorch::screens
