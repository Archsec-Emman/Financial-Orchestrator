// src/ui/navigation/CommandBar_internal.h
//
// Private header — included only by CommandBar*.cpp translation units.
// Cross-file constants shared between the partial-class split files.

#pragma once

namespace fiorch::ui::commandbar_internal {

// Caps the dropdown result list AND the upstream /market/search request.
inline constexpr int kMaxResults = 10;

} // namespace fiorch::ui::commandbar_internal
