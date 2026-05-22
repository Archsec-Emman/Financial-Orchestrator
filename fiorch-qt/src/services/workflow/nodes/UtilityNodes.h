#pragma once

namespace fiorch::workflow {
class NodeRegistry;

/// Register utility node types (HttpRequest, Code, Set, DateTime, etc.)
void register_utility_nodes(NodeRegistry& registry);

} // namespace fiorch::workflow
