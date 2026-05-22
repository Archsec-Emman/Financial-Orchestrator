#pragma once
#include <QString>

namespace fiorch {

/// Central registry for all application file-system paths.
///
/// All paths live under a single root directory:
///   Windows : %LOCALAPPDATA%/com.fiorch.terminal/
///   macOS   : ~/Library/Application Support/com.fiorch.terminal/
///   Linux   : ~/.local/share/com.fiorch.terminal/
///
/// Sub-directories:
///   data/    — SQLite databases (fincept.db, cache.db)
///   logs/    — Application log files
///   files/   — User-managed file attachments
///   cache/   — Tile caches and other transient network data
///   models/  — ML model files
///   runtime/ — Python interpreter, UV, virtual environments
///
/// Call AppPaths::ensure_all() once at startup to create every sub-directory.
class AppPaths {
  public:
    /// Root: %LOCALAPPDATA%\com.fiorch.terminal  (Windows)
    static QString root();

    /// root/data  — persistent databases
    static QString data();

    /// root/logs  — log files
    static QString logs();

    /// root/files — user-managed file attachments
    static QString files();

    /// root/cache — tile caches and transient network data
    static QString cache();

    /// root/models — ML model files
    static QString models();

    /// root/runtime — Python interpreter, UV, virtual environments
    static QString runtime();

    /// root/workspaces — saved workspace files (.fwsp)
    static QString workspaces();

    /// root/crashdumps — minidumps written by the unhandled-exception filter
    static QString crashdumps();

    /// Create all sub-directories if they don't exist.
    /// Call once before any path is used.
    static void ensure_all();
};

} // namespace fiorch
