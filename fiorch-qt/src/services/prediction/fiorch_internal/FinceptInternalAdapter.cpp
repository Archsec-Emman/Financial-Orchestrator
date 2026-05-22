
#include "core/logging/Logger.h"
#include "datahub/DataHub.h"
#include "datahub/TopicPolicy.h"
#include "storage/secure/SecureStorage.h"

#include <QDateTime>
#include <QNetworkAccessManager>
#include <QPointer>
#include <QTimer>
#include <QVector>

#include <atomic>

namespace fiorch::services::prediction::fincept_internal {

namespace {

// SecureStorage keys.
constexpr const char* kKeyEndpoint = "fincept.markets_endpoint";
constexpr const char* kKeyMarketProgramId = "fincept.market_program_id";

// Hub topic prefix — mirrors `prediction:polymarket:*` and
// `prediction:kalshi:*` already in DATAHUB_TOPICS.md. The wildcard tail
// matches asset_ids and market_ids exactly the way the existing adapters
// do, so screens iterate the registry without special-casing.
constexpr const char* kTopicPrefixMarkets = "prediction:fincept:markets";
constexpr const char* kTopicPrefixOrderbook = "prediction:fincept:orderbook:";
constexpr const char* kTopicPrefixPrice = "prediction:fincept:price:";

// Curated demo dataset. The three example markets from plan §4.2 — used
// when `fincept.markets_endpoint` is unset so the MarketsTab is reviewable
// before the matching engine is deployed. Numbers are intentionally
// rounded — these are demo prices, not implied probabilities.
struct DemoMarketSeed {
    const char* market_id;       ///< stable id, used as an asset_id suffix too
    const char* question;
    const char* category;
    double yes_price;            ///< 0..1
    double volume;
    const char* end_date_iso;
};

constexpr DemoMarketSeed kDemoMarkets[] = {
    {"fincept-fed-cuts-2026-05",
     "Fed cuts in May 2026",
     "Macro", 0.62, 1'200'000.0, "2026-05-07"},
    {"fincept-nyc-80f-2026-05-01",
     "NYC max 80F+ on May 1",
     "Weather", 0.71, 83'000.0, "2026-05-01"},
    {"fincept-fncpt-1bp-2026-05-31",
     "$FNCPT > $0.0001 by month end",
     "Crypto", 0.45, 421'000.0, "2026-05-31"},
};

QString trim_trailing_slash(QString s) {
    while (s.endsWith('/')) s.chop(1);
    return s;
}

PredictionMarket build_demo_market(const DemoMarketSeed& seed) {
    PredictionMarket m;
    m.key.exchange_id = QStringLiteral("fiorch");
    m.key.market_id = QString::fromLatin1(seed.market_id);
    m.key.event_id = m.key.market_id; // 1:1 for binary demo markets
    m.key.asset_ids = {
        m.key.market_id + QStringLiteral(":yes"),
        m.key.market_id + QStringLiteral(":no"),
    };
    m.question = QString::fromUtf8(seed.question);
    m.category = QString::fromUtf8(seed.category);
    m.end_date_iso = QString::fromLatin1(seed.end_date_iso);
    m.volume = seed.volume;
    m.liquidity = seed.volume * 0.05; // illustrative
    m.active = true;
    m.closed = false;

    Outcome yes;
    yes.name = QStringLiteral("Yes");
    yes.asset_id = m.key.asset_ids.value(0);
    yes.price = seed.yes_price;

    Outcome no;
    no.name = QStringLiteral("No");
    no.asset_id = m.key.asset_ids.value(1);
    no.price = 1.0 - seed.yes_price;

    m.outcomes = {yes, no};
    m.tags = {m.category};
    m.extras.insert(QStringLiteral("is_demo"), true);
    m.extras.insert(QStringLiteral("settlement_currency"), QStringLiteral("FNCPT"));
    return m;
}

} // namespace

    : PredictionExchangeAdapter(parent) {
    nam_ = new QNetworkAccessManager(this);
}


// ── Identity ───────────────────────────────────────────────────────────────

    return QStringLiteral("fiorch");
}

}

    ExchangeCapabilities c;
    c.has_events = true;
    c.has_multi_outcome = false;        // binary markets only at launch
    c.has_orderbook_ws = true;
    c.has_trade_ws = true;
    c.has_rewards = false;
    c.has_maker_rebates = false;
    c.has_leaderboard = false;
    c.supports_limit_orders = true;
    c.supports_market_orders = true;
    c.supports_gtd = false;
    c.supports_fok = true;
    c.supports_fak = true;
    c.supports_decrease_order = false;
    c.supports_batch_orders = false;
    c.quote_currency = QStringLiteral("FNCPT");
    c.min_order_size = 1.0;
    c.default_tick_size = 0.01;
    c.max_requests_per_sec = 5;
    return c;
}

// ── Endpoint resolution ────────────────────────────────────────────────────

    auto r = SecureStorage::instance().retrieve(QString::fromLatin1(kKeyEndpoint));
    if (r.is_ok()) return trim_trailing_slash(r.value().trimmed());
    return {};
}

    return resolve_endpoint().isEmpty();
}

// ── Read endpoints ─────────────────────────────────────────────────────────
//
// All read endpoints currently route through the demo emitters when the
// markets endpoint is unset. The HTTP path is left as a TODO seam: when
// against `<endpoint>/markets`, `<endpoint>/orderbook/<asset_id>`, etc.

                                          const QString& /*sort_by*/,
                                          int /*limit*/, int /*offset*/) {
    if (is_demo_mode()) {
        emit_mock_markets();
    } else {
        // Real HTTP path lands when the matching engine ships. For now,
        // surface a clean error so the UI shows "service unavailable"
        // instead of hanging.
        emit_demo_unavailable(QStringLiteral("list_markets"));
    }
}

                                         const QString& /*sort_by*/,
                                         int /*limit*/, int /*offset*/) {
    if (is_demo_mode()) {
        emit_mock_events();
    } else {
        emit_demo_unavailable(QStringLiteral("list_events"));
    }
}

    if (is_demo_mode()) {
        // Filter the curated dataset client-side. Cheap and good enough
        // for demo mode.
        QVector<PredictionMarket> hits;
        for (const auto& seed : kDemoMarkets) {
            const auto question = QString::fromUtf8(seed.question);
            if (query.isEmpty() ||
                question.contains(query, Qt::CaseInsensitive)) {
                hits.push_back(build_demo_market(seed));
            }
        }
        QTimer::singleShot(0, this, [self, hits]() {
            if (!self) return;
            emit self->search_results_ready(hits, {});
        });
        return;
    }
    emit_demo_unavailable(QStringLiteral("search"));
}

    if (is_demo_mode()) {
        QTimer::singleShot(0, this, [self]() {
            if (!self) return;
            emit self->tags_ready(QStringList{
                QStringLiteral("Macro"),
                QStringLiteral("Weather"),
                QStringLiteral("Crypto"),
            });
        });
        return;
    }
    emit_demo_unavailable(QStringLiteral("list_tags"));
}

    if (is_demo_mode()) {
        for (const auto& seed : kDemoMarkets) {
            if (key.market_id == QString::fromLatin1(seed.market_id)) {
                auto m = build_demo_market(seed);
                QTimer::singleShot(0, this, [self, m]() {
                    if (!self) return;
                    emit self->market_detail_ready(m);
                });
                return;
            }
        }
    }
    emit_demo_unavailable(QStringLiteral("fetch_market"));
}

    fetch_market(key); // 1:1 in demo binary markets
}

    if (is_demo_mode()) {
        // A flat shallow book centred on each demo asset's price. Replace
        // with a real orderbook fetch when the matching engine ships.
        PredictionOrderBook book;
        book.asset_id = asset_id;
        for (const auto& seed : kDemoMarkets) {
            const auto yes_id = QString::fromLatin1(seed.market_id) +
                                QStringLiteral(":yes");
            if (asset_id == yes_id) {
                const double mid = seed.yes_price;
                book.bids = {
                    {mid - 0.01, 250.0},
                    {mid - 0.02, 500.0},
                    {mid - 0.05, 1'200.0},
                };
                book.asks = {
                    {mid + 0.01, 250.0},
                    {mid + 0.02, 500.0},
                    {mid + 0.05, 1'200.0},
                };
                break;
            }
        }
        QTimer::singleShot(0, this, [self, book]() {
            if (!self) return;
            emit self->order_book_ready(book);
        });
        return;
    }
    emit_demo_unavailable(QStringLiteral("fetch_order_book"));
}

                                                 const QString& /*interval*/,
                                                 int /*fidelity*/) {
    if (is_demo_mode()) {
        emit_demo_unavailable(QStringLiteral("fetch_price_history (demo)"));
        return;
    }
    emit_demo_unavailable(QStringLiteral("fetch_price_history"));
}

    QTimer::singleShot(0, this, [self]() {
        if (!self) return;
        emit self->recent_trades_ready({});
    });
}

// ── Real-time ──────────────────────────────────────────────────────────────

    // No-op in demo mode. Real path: open a WS to <endpoint>/ws and forward
    // ws_price_updated / ws_orderbook_updated when the engine ships.
}

    // No-op in demo mode.
}

    // Demo mode is never "connected" — screens use this to choose a
    // disabled state for live-stream-only widgets.
    return false;
}

// ── Trading ────────────────────────────────────────────────────────────────
//
// Trading is gated behind both `has_credentials()` and the existence of
// the on-chain `fincept_market` program. Until either lands, all trading
// methods emit `error_occurred("not deployed", …)` so the order ticket
// can stay disabled with a clear message.

    auto r = SecureStorage::instance().retrieve(
        QString::fromLatin1(kKeyMarketProgramId));
    return r.is_ok() && !r.value().trimmed().isEmpty();
}

    return QStringLiteral("(connect wallet)");
}


    emit_demo_unavailable(QStringLiteral("place_order"));
}

    emit error_occurred(QStringLiteral("cancel_order"),
                        QStringLiteral("fincept_market program not deployed"));
    emit order_cancelled(order_id, /*ok=*/false,
                         QStringLiteral("fincept_market program not deployed"));
}

                                                   const QString& /*asset_id*/) {
    emit_demo_unavailable(QStringLiteral("cancel_all_for_market"));
}

// ── Hub ────────────────────────────────────────────────────────────────────

    if (hub_registered_) return;
    hub_registered_ = true;

    // No producer to register yet — until the matching engine is up,
    // the adapter doesn't own any topic family that's ready to publish.
    // Reserve the topic policies anyway so subscribers in screens see a
    // policy when they peek (TTL applied to mock publishes once we have
    // a producer for them).
    auto& hub = fiorch::datahub::DataHub::instance();
    fiorch::datahub::TopicPolicy markets_p;
    markets_p.ttl_ms = 30 * 1000;
    markets_p.min_interval_ms = 10 * 1000;
    hub.set_policy_pattern(QString::fromLatin1(kTopicPrefixMarkets), markets_p);

    fiorch::datahub::TopicPolicy book_p;
    book_p.ttl_ms = 5 * 1000;
    book_p.min_interval_ms = 1 * 1000;
    hub.set_policy_pattern(QString::fromLatin1(kTopicPrefixOrderbook) +
                           QStringLiteral("*"), book_p);

    fiorch::datahub::TopicPolicy price_p;
    price_p.ttl_ms = 5 * 1000;
    price_p.min_interval_ms = 1 * 1000;
    hub.set_policy_pattern(QString::fromLatin1(kTopicPrefixPrice) +
                           QStringLiteral("*"), price_p);

    static std::atomic<bool> logged{false};
    if (!logged.exchange(true)) {
        if (is_demo_mode()) {
                     "registered (demo mode — no fincept.markets_endpoint configured)");
        } else {
                     QString("registered (endpoint=%1)").arg(resolve_endpoint()));
        }
    }
}

// ── Mock emitters ──────────────────────────────────────────────────────────

    QVector<PredictionMarket> markets;
    markets.reserve(static_cast<int>(std::size(kDemoMarkets)));
    for (const auto& seed : kDemoMarkets) {
        markets.push_back(build_demo_market(seed));
    }
    QTimer::singleShot(0, this, [self, markets]() {
        if (!self) return;
        emit self->markets_ready(markets);
    });
}

    QVector<PredictionEvent> events;
    events.reserve(static_cast<int>(std::size(kDemoMarkets)));
    for (const auto& seed : kDemoMarkets) {
        PredictionEvent e;
        e.key.exchange_id = QStringLiteral("fiorch");
        e.key.event_id = QString::fromLatin1(seed.market_id);
        e.title = QString::fromUtf8(seed.question);
        e.category = QString::fromUtf8(seed.category);
        e.volume = seed.volume;
        e.active = true;
        e.markets = {build_demo_market(seed)};
        e.tags = {e.category};
        e.extras.insert(QStringLiteral("is_demo"), true);
        events.push_back(e);
    }
    QTimer::singleShot(0, this, [self, events]() {
        if (!self) return;
        emit self->events_ready(events);
    });
}

    QTimer::singleShot(0, this, [self]() {
        if (!self) return;
        emit self->tags_ready(QStringList{
            QStringLiteral("Macro"),
            QStringLiteral("Weather"),
            QStringLiteral("Crypto"),
        });
    });
}

    const auto msg = QStringLiteral(
        "`fincept.markets_endpoint` in SecureStorage to enable live data.");
    QTimer::singleShot(0, this, [self, context, msg]() {
        if (!self) return;
        emit self->error_occurred(context, msg);
    });
}

} // namespace fiorch::services::prediction::fincept_internal
