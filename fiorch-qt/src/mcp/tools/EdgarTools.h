#pragma once
// EdgarTools.h — SEC EDGAR MCP tools
// Direct interface to scripts/mcp/edgar/main.py (System 1)
// Separate from M&A Analytics — covers general SEC data: CIK resolution,
// XBRL financials, filing text, valuation multiples, filing search.

#include "mcp/McpTypes.h"

#include <vector>

namespace fiorch::mcp::tools {
std::vector<ToolDef> get_edgar_tools();
} // namespace fiorch::mcp::tools
