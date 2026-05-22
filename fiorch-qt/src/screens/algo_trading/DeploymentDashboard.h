// src/screens/algo_trading/DeploymentDashboard.h
#pragma once
#include "services/algo_trading/AlgoTradingTypes.h"

#include <QFrame>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>

namespace fiorch::screens {

/// Live deployment monitor — shows running strategies with real-time metrics.
class DeploymentDashboard : public QWidget {
    Q_OBJECT
  public:
    explicit DeploymentDashboard(QWidget* parent = nullptr);

  private slots:
    void on_deployments_loaded(QVector<fiorch::services::algo::AlgoDeployment> deployments);
    void on_error(const QString& context, const QString& msg);

  private:
    void build_ui();
    void connect_service();
    QWidget* build_deployment_card(const fiorch::services::algo::AlgoDeployment& d, QWidget* parent);
    void update_summary(const QVector<fiorch::services::algo::AlgoDeployment>& deployments);

    // Summary stats
    QLabel* active_count_ = nullptr;
    QLabel* total_pnl_    = nullptr;
    QLabel* total_trades_ = nullptr;
    QLabel* avg_win_rate_ = nullptr;

    // Equity curve placeholder
    QFrame* equity_placeholder_ = nullptr;

    QVBoxLayout* deployments_layout_ = nullptr;
    QLabel*      status_label_       = nullptr;
};

} // namespace fiorch::screens
