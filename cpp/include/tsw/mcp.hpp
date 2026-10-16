#pragma once
#include "tsw/game.hpp"
#include <memory>

namespace tsw {
// Native stdio MCP boundary; the original core has no transport or JSON dependency.
class McpServer {
  public:
    explicit McpServer(bool developer = false, Game game = Game{}, bool runtime_bridge = false);
    ~McpServer();
    void load(const std::filesystem::path&, SaveKind = SaveKind::Slot);
    // Notifications have no response. Malformed requests produce JSON-RPC errors.
    std::optional<std::string> respond(std::string_view request);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

void serve_mcp(McpServer&, std::istream&, std::ostream&);
} // namespace tsw
