#pragma once
#include "screens/dashboard/widgets/QuoteTableWidget.h"
#include "ui/theme/Theme.h"

#include <QCoreApplication>

namespace fiorch::screens::widgets {

/// Cryptocurrency widget — fetches top 9 cryptos via yfinance.
inline QuoteTableWidget* create_crypto_widget(QWidget* parent = nullptr) {
    QMap<QString, QString> labels = {
        {"BTC-USD", "BTC"}, {"ETH-USD", "ETH"},   {"BNB-USD", "BNB"}, {"SOL-USD", "SOL"}, {"XRP-USD", "XRP"},
        {"ADA-USD", "ADA"}, {"DOGE-USD", "DOGE"}, {"DOT-USD", "DOT"}, {"LTC-USD", "LTC"},
    };
    const QString title = QCoreApplication::translate("fiorch::screens::widgets::QuoteTableWidget", "CRYPTOCURRENCY");
    return new QuoteTableWidget(title, services::MarketDataService::crypto_symbols(), labels, 2,
                                ui::colors::AMBER(), parent);
}

} // namespace fiorch::screens::widgets
