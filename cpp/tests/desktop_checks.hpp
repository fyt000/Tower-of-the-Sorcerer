#pragma once
#include "desktop_session.hpp"

namespace tsw {
int verify_presentation(Presentation&, const std::filesystem::path&, const Assets&);
int verify_window(Presentation&, const std::filesystem::path&);
int verify_assets(const Assets&, const Assets&, const std::filesystem::path&, const std::filesystem::path&);
int verify_smoke(DesktopSession&, const std::string&, const std::filesystem::path&);
} // namespace tsw
