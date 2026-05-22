#pragma once
#include "mcp/McpTypes.h"

#include <vector>

namespace fiorch::mcp::tools {

/// Generic DataHub introspection surface for LLMs. See Phase 9 plan.
std::vector<ToolDef> get_datahub_tools();

} // namespace fiorch::mcp::tools
