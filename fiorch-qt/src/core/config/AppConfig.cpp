#include "core/config/AppConfig.h"

namespace fiorch {

AppConfig& AppConfig::instance() {
    static AppConfig s;
    return s;
}


QVariant AppConfig::get(const QString& key, const QVariant& default_val) const {
    return settings_.value(key, default_val);
}

void AppConfig::set(const QString& key, const QVariant& value) {
    settings_.setValue(key, value);
}

void AppConfig::remove(const QString& key) {
    settings_.remove(key);
}

QString AppConfig::api_base_url() const {
    return settings_.value("api/base_url", "https://api.fiorch.in").toString();
}

bool AppConfig::dark_mode() const {
    return settings_.value("ui/dark_mode", true).toBool();
}

int AppConfig::refresh_interval_ms() const {
    return settings_.value("data/refresh_interval_ms", 30000).toInt();
}

} // namespace fiorch
