#include "embedded_media.hpp"
#include <array>
#include <fstream>
#include <stdexcept>

namespace tsw {
namespace {
class PeFile {
    std::ifstream file_;
    std::uint64_t size_{};
    std::uint32_t resource_base_{}, resource_size_{};

    void read(std::uint64_t offset, unsigned char* output, std::size_t length) {
        if (offset > size_ || length > size_ - offset)
            throw std::runtime_error("Truncated embedded media resource");
        file_.seekg(static_cast<std::streamoff>(offset));
        file_.read(reinterpret_cast<char*>(output), static_cast<std::streamsize>(length));
        if (!file_)
            throw std::runtime_error("Unable to read embedded media resource");
    }

    std::uint16_t u16(std::uint64_t offset) {
        std::array<unsigned char, 2> bytes{};
        read(offset, bytes.data(), bytes.size());
        return std::uint16_t(bytes[0] | bytes[1] << 8);
    }

    std::uint32_t u32(std::uint64_t offset) {
        std::array<unsigned char, 4> bytes{};
        read(offset, bytes.data(), bytes.size());
        return std::uint32_t(bytes[0]) | std::uint32_t(bytes[1]) << 8 | std::uint32_t(bytes[2]) << 16 |
               std::uint32_t(bytes[3]) << 24;
    }

    std::uint32_t file_offset(std::uint32_t rva, std::uint32_t length = 1) {
        const auto pe = u32(0x3c);
        const auto sections = u16(pe + 6), optional_size = u16(pe + 20);
        for (unsigned i = 0; i < sections; ++i) {
            const std::uint64_t section = std::uint64_t(pe) + 24 + optional_size + i * 40;
            const auto address = u32(section + 12), raw_size = u32(section + 16);
            if (rva >= address && rva - address < raw_size && length <= raw_size - (rva - address))
                return u32(section + 20) + (rva - address);
        }
        throw std::runtime_error("Embedded media points outside the executable's sections");
    }

    std::uint64_t resource_offset(std::uint32_t offset, unsigned length) const {
        if (offset > resource_size_ || length > resource_size_ - offset)
            throw std::runtime_error("Invalid embedded media directory");
        return std::uint64_t(resource_base_) + offset;
    }

    std::uint32_t entry(std::uint32_t directory, int id) {
        const auto header = resource_offset(directory, 16);
        const unsigned count = unsigned(u16(header + 12)) + u16(header + 14);
        if (count > 4096)
            throw std::runtime_error("Invalid embedded media entry count");
        for (unsigned i = 0; i < count; ++i) {
            const auto offset = resource_offset(directory + 16 + i * 8, 8);
            const auto name = u32(offset);
            if (id < 0 || name == unsigned(id))
                return u32(offset + 4);
        }
        throw std::runtime_error("Required embedded media resource is missing");
    }

  public:
    explicit PeFile(const std::filesystem::path& path) : file_(path, std::ios::binary) {
        if (!file_)
            throw std::runtime_error("Unable to open the replacement executable's embedded media");
        size_ = std::filesystem::file_size(path);
        if (u16(0) != 0x5a4d)
            throw std::runtime_error("Embedded media requires a Windows PE executable");
        const auto pe = u32(0x3c);
        if (u32(pe) != 0x00004550)
            throw std::runtime_error("Invalid replacement executable header");
        const auto magic = u16(pe + 24);
        if (magic != 0x10b && magic != 0x20b)
            throw std::runtime_error("Unsupported replacement executable format");
        const auto data_directory = std::uint64_t(pe) + 24 + (magic == 0x20b ? 112 : 96);
        const auto rva = u32(data_directory + 16);
        resource_size_ = u32(data_directory + 20);
        resource_base_ = file_offset(rva, resource_size_);
    }

    std::vector<unsigned char> media(int id) {
        constexpr std::uint32_t DirectoryFlag = 0x80000000u;
        auto directory = entry(0, 10); // RT_RCDATA.
        if (!(directory & DirectoryFlag))
            throw std::runtime_error("Invalid embedded media type directory");
        directory = entry(directory & ~DirectoryFlag, id);
        if (!(directory & DirectoryFlag))
            throw std::runtime_error("Invalid embedded media name directory");
        const auto data = entry(directory & ~DirectoryFlag, -1); // First language entry.
        if (data & DirectoryFlag)
            throw std::runtime_error("Invalid embedded media language entry");
        const auto offset = resource_offset(data, 16);
        const auto rva = u32(offset), length = u32(offset + 4);
        if (!length || length > 64 * 1024 * 1024)
            throw std::runtime_error("Invalid embedded media size");
        std::vector<unsigned char> bytes(length);
        read(file_offset(rva, length), bytes.data(), bytes.size());
        return bytes;
    }
};
} // namespace

std::vector<unsigned char> read_embedded_media(const std::filesystem::path& executable, EmbeddedMedia media) {
    return PeFile(executable).media(int(media));
}
} // namespace tsw
