#include "datahub/DataHubMetaTypes.h"

#include "core/logging/Logger.h"

namespace fiorch::datahub {

void register_metatypes() {
    qRegisterMetaType<fiorch::services::QuoteData>("fiorch::services::QuoteData");
    qRegisterMetaType<fiorch::services::HistoryPoint>("fiorch::services::HistoryPoint");
    qRegisterMetaType<fiorch::services::InfoData>("fiorch::services::InfoData");
    qRegisterMetaType<fiorch::services::NewsArticle>("fiorch::services::NewsArticle");
    qRegisterMetaType<fiorch::services::EconomicsResult>("fiorch::services::EconomicsResult");
    qRegisterMetaType<QVector<fiorch::services::HistoryPoint>>("QVector<fiorch::services::HistoryPoint>");
    qRegisterMetaType<QVector<fiorch::services::NewsArticle>>("QVector<fiorch::services::NewsArticle>");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<fiorch::trading::TickerData>("fiorch::trading::TickerData");
    qRegisterMetaType<fiorch::trading::OrderBookData>("fiorch::trading::OrderBookData");
    qRegisterMetaType<fiorch::trading::Candle>("fiorch::trading::Candle");
    qRegisterMetaType<fiorch::trading::TradeData>("fiorch::trading::TradeData");
    qRegisterMetaType<fiorch::services::polymarket::OrderBook>("fiorch::services::polymarket::OrderBook");

    // Prediction Markets (Polymarket, Kalshi, …)
    qRegisterMetaType<fiorch::services::prediction::MarketKey>("fiorch::services::prediction::MarketKey");
    qRegisterMetaType<fiorch::services::prediction::PredictionMarket>("fiorch::services::prediction::PredictionMarket");
    qRegisterMetaType<fiorch::services::prediction::PredictionEvent>("fiorch::services::prediction::PredictionEvent");
    qRegisterMetaType<fiorch::services::prediction::PredictionOrderBook>("fiorch::services::prediction::PredictionOrderBook");
    qRegisterMetaType<fiorch::services::prediction::PriceHistory>("fiorch::services::prediction::PriceHistory");
    qRegisterMetaType<fiorch::services::prediction::PredictionTrade>("fiorch::services::prediction::PredictionTrade");
    qRegisterMetaType<fiorch::services::prediction::PredictionPosition>("fiorch::services::prediction::PredictionPosition");
    qRegisterMetaType<fiorch::services::prediction::OpenOrder>("fiorch::services::prediction::OpenOrder");
    qRegisterMetaType<fiorch::services::prediction::OrderResult>("fiorch::services::prediction::OrderResult");
    qRegisterMetaType<fiorch::services::prediction::AccountBalance>("fiorch::services::prediction::AccountBalance");
    qRegisterMetaType<QVector<fiorch::services::prediction::PredictionMarket>>("QVector<fiorch::services::prediction::PredictionMarket>");
    qRegisterMetaType<QVector<fiorch::services::prediction::PredictionEvent>>("QVector<fiorch::services::prediction::PredictionEvent>");
    qRegisterMetaType<QVector<fiorch::services::prediction::PredictionTrade>>("QVector<fiorch::services::prediction::PredictionTrade>");
    qRegisterMetaType<QVector<fiorch::services::prediction::PredictionPosition>>("QVector<fiorch::services::prediction::PredictionPosition>");
    qRegisterMetaType<QVector<fiorch::services::prediction::OpenOrder>>("QVector<fiorch::services::prediction::OpenOrder>");
    qRegisterMetaType<fiorch::services::DbnDataPoint>("fiorch::services::DbnDataPoint");
    qRegisterMetaType<fiorch::services::GovDataResult>("fiorch::services::GovDataResult");
    qRegisterMetaType<fiorch::trading::BrokerPosition>("fiorch::trading::BrokerPosition");
    qRegisterMetaType<fiorch::trading::BrokerHolding>("fiorch::trading::BrokerHolding");
    qRegisterMetaType<fiorch::trading::BrokerOrderInfo>("fiorch::trading::BrokerOrderInfo");
    qRegisterMetaType<fiorch::trading::BrokerQuote>("fiorch::trading::BrokerQuote");
    qRegisterMetaType<fiorch::trading::BrokerFunds>("fiorch::trading::BrokerFunds");
    qRegisterMetaType<QVector<fiorch::trading::BrokerPosition>>("QVector<fiorch::trading::BrokerPosition>");
    qRegisterMetaType<QVector<fiorch::trading::BrokerHolding>>("QVector<fiorch::trading::BrokerHolding>");
    qRegisterMetaType<QVector<fiorch::trading::BrokerOrderInfo>>("QVector<fiorch::trading::BrokerOrderInfo>");
    qRegisterMetaType<QVector<fiorch::trading::BrokerQuote>>("QVector<fiorch::trading::BrokerQuote>");

    // F&O / Options chain (Phase 11 — Sensibull-style tab)
    qRegisterMetaType<fiorch::services::options::OptionGreeks>("fiorch::services::options::OptionGreeks");
    qRegisterMetaType<fiorch::services::options::OptionChainRow>("fiorch::services::options::OptionChainRow");
    qRegisterMetaType<fiorch::services::options::OptionChain>("fiorch::services::options::OptionChain");
    qRegisterMetaType<fiorch::services::options::StrategyLeg>("fiorch::services::options::StrategyLeg");
    qRegisterMetaType<fiorch::services::options::Strategy>("fiorch::services::options::Strategy");
    qRegisterMetaType<fiorch::services::options::PayoffPoint>("fiorch::services::options::PayoffPoint");
    qRegisterMetaType<fiorch::services::options::StrategyAnalytics>(
        "fiorch::services::options::StrategyAnalytics");
    qRegisterMetaType<QVector<fiorch::services::options::OptionChainRow>>(
        "QVector<fiorch::services::options::OptionChainRow>");
    qRegisterMetaType<QVector<fiorch::services::options::PayoffPoint>>(
        "QVector<fiorch::services::options::PayoffPoint>");
    qRegisterMetaType<QVector<fiorch::services::options::StrategyLeg>>(
        "QVector<fiorch::services::options::StrategyLeg>");
    qRegisterMetaType<fiorch::services::options::OISample>("fiorch::services::options::OISample");
    qRegisterMetaType<QVector<fiorch::services::options::OISample>>(
        "QVector<fiorch::services::options::OISample>");
    qRegisterMetaType<fiorch::services::options::FiiDiiDay>("fiorch::services::options::FiiDiiDay");
    qRegisterMetaType<QVector<fiorch::services::options::FiiDiiDay>>(
        "QVector<fiorch::services::options::FiiDiiDay>");

    // Phase 8 — Geopolitics / Maritime / RelationshipMap
    qRegisterMetaType<fiorch::services::geo::NewsEvent>("fiorch::services::geo::NewsEvent");
    qRegisterMetaType<fiorch::services::geo::HDXDataset>("fiorch::services::geo::HDXDataset");
    qRegisterMetaType<fiorch::services::geo::UniqueCountry>("fiorch::services::geo::UniqueCountry");
    qRegisterMetaType<fiorch::services::geo::UniqueCategory>("fiorch::services::geo::UniqueCategory");
    qRegisterMetaType<QVector<fiorch::services::geo::NewsEvent>>("QVector<fiorch::services::geo::NewsEvent>");
    qRegisterMetaType<QVector<fiorch::services::geo::HDXDataset>>("QVector<fiorch::services::geo::HDXDataset>");
    qRegisterMetaType<QVector<fiorch::services::geo::UniqueCountry>>("QVector<fiorch::services::geo::UniqueCountry>");
    qRegisterMetaType<QVector<fiorch::services::geo::UniqueCategory>>("QVector<fiorch::services::geo::UniqueCategory>");
    qRegisterMetaType<fiorch::services::geo::EventsPage>("fiorch::services::geo::EventsPage");
    qRegisterMetaType<fiorch::services::maritime::VesselData>("fiorch::services::maritime::VesselData");
    qRegisterMetaType<QVector<fiorch::services::maritime::VesselData>>("QVector<fiorch::services::maritime::VesselData>");
    qRegisterMetaType<fiorch::services::maritime::VesselsPage>("fiorch::services::maritime::VesselsPage");
    qRegisterMetaType<fiorch::services::maritime::VesselHistoryPage>("fiorch::services::maritime::VesselHistoryPage");
    qRegisterMetaType<fiorch::relmap::RelationshipData>("fiorch::relmap::RelationshipData");

    // Crypto / Wallet (Phase 1 + Phase 2 Stage 2A.5 multi-token holdings)
    qRegisterMetaType<fiorch::wallet::WalletBalance>("fiorch::wallet::WalletBalance");
    qRegisterMetaType<fiorch::wallet::TokenHolding>("fiorch::wallet::TokenHolding");
    qRegisterMetaType<fiorch::wallet::TokenPrice>("fiorch::wallet::TokenPrice");
    qRegisterMetaType<fiorch::wallet::TokenMetadata>("fiorch::wallet::TokenMetadata");
    // FncptPrice is a typedef of TokenPrice — register its name as an alias so
    // Qt's metatype lookup serves either spelling.
    qRegisterMetaType<fiorch::wallet::FncptPrice>("fiorch::wallet::FncptPrice");
    // Phase 2 §2B activity feed — vector form is what publishes on the topic.
    qRegisterMetaType<fiorch::wallet::ParsedActivity>("fiorch::wallet::ParsedActivity");
    qRegisterMetaType<QVector<fiorch::wallet::ParsedActivity>>(
        "QVector<fiorch::wallet::ParsedActivity>");
    // Phase 2 §2C fee-discount eligibility.
    qRegisterMetaType<fiorch::wallet::FncptDiscount>("fiorch::wallet::FncptDiscount");

    // Phase 5 — buyback & burn dashboard (terminal-wide treasury:* topics).
    qRegisterMetaType<fiorch::wallet::BuybackEpoch>("fiorch::wallet::BuybackEpoch");
    qRegisterMetaType<fiorch::wallet::BurnTotal>("fiorch::wallet::BurnTotal");
    qRegisterMetaType<fiorch::wallet::SupplyHistoryPoint>(
        "fiorch::wallet::SupplyHistoryPoint");
    qRegisterMetaType<QVector<fiorch::wallet::SupplyHistoryPoint>>(
        "QVector<fiorch::wallet::SupplyHistoryPoint>");
    qRegisterMetaType<fiorch::wallet::TreasuryReserves>("fiorch::wallet::TreasuryReserves");
    qRegisterMetaType<fiorch::wallet::TreasuryRunway>("fiorch::wallet::TreasuryRunway");

    // Phase 3 — STAKE tab (veFNCPT lock + tier system).
    qRegisterMetaType<fiorch::wallet::LockPosition>("fiorch::wallet::LockPosition");
    qRegisterMetaType<QVector<fiorch::wallet::LockPosition>>(
        "QVector<fiorch::wallet::LockPosition>");
    qRegisterMetaType<fiorch::wallet::VeFncptAggregate>("fiorch::wallet::VeFncptAggregate");
    qRegisterMetaType<fiorch::wallet::YieldSnapshot>("fiorch::wallet::YieldSnapshot");
    qRegisterMetaType<fiorch::wallet::TreasuryRevenue>("fiorch::wallet::TreasuryRevenue");
    qRegisterMetaType<fiorch::wallet::TierStatus>("fiorch::wallet::TierStatus");

    LOG_INFO("DataHub", "Registered 83 payload meta-types");
}

} // namespace fiorch::datahub
