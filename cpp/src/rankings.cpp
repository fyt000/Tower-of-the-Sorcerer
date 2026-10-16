#include "tsw/rankings.hpp"
#include <bit>
#include <format>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <utility>

namespace tsw {
namespace {
using RankingWords = std::array<std::array<std::uint32_t, 6>, 12>;
constexpr std::size_t RankingBytes = 288;
constexpr std::array<std::array<std::string_view, RankingEntryCount>, RankingCategoryCount> DefaultNames{
    {{{"Skeleton A", "Priest", "Skeleton B", "Gate-Keeper C", "Skeleton C", "Bat", "Red Slime", "Green Slime",
       "Iron Sword", "Iron Shield"}},
     {{"Vampire", "Superion Priest", "Zombie Knight", "Gate-Keeper B", "Rock", "Big Octopus", "Zombie",
       "Big Bat", "Big Slime", "Blue Crystal"}},
     {{"Magic Master", "Thief", "Fairy", "Merchant", "Princess", "Old Man", "Brave Man", "Mattock", "Cross",
       "Lucky Gold"}},
     {{"Golden Knight", "Knight", "Fancer", "Soldier", "Ghost Soldier", "Dragon", "Swordsman", "Slime Man",
       "Sword of Knight", "Shield of Knight"}},
     {{"Zeno", "Magician A", "Black Knight", "Magic Sergeant", "Gate-Keeper A", "Bloodsucker Bat",
       "Magician B", "King Slime", "Holy Sword", "Holy Shield"}}}};

void check_category(int category) {
    if (category < 1 || category > RankingCategoryCount)
        throw std::out_of_range("Ranking category must be between 1 and 5");
}

std::filesystem::path data_path(const std::filesystem::path& directory, int category) {
    return directory / std::format("option{}.dat", category);
}

std::filesystem::path names_path(const std::filesystem::path& directory, int category) {
    return directory / std::format("option{}1.dat", category);
}

void checksums(RankingWords& words, int category) {
    // Unsigned addition/subtraction reproduces the Pascal Longint wrap at 32 bits.
    for (int row = 0; row < RankingEntryCount; ++row) {
        const auto& values = words[row];
        words[row][4] = values[0] + values[1] + values[2] + values[3];
        words[row][5] = values[0] - values[1] + values[2] - values[3] + values[4];
    }
    for (int column = 0; column < 6; ++column) {
        words[10][column] = words[11][column] = 0;
        for (int row = 0; row < RankingEntryCount; ++row) {
            words[10][column] += words[row][column];
            words[11][column] += row % 2 ? 0u - words[row][column] : words[row][column];
        }
        // The column sum is the eleventh, positive term of the alternating checksum.
        words[11][column] += words[10][column];
    }
    // The format sentinel is -4; this final word replaces the sixth column's checksum.
    words[11][5] = static_cast<std::uint32_t>(-400 - category);
}

RankingWords encode(const RankingTable& table, int category) {
    RankingWords words{};
    for (int row = 0; row < RankingEntryCount; ++row) {
        const auto& entry = table[row];
        words[row][0] = static_cast<std::uint32_t>(entry.score);
        words[row][1] = static_cast<std::uint32_t>(entry.hp);
        words[row][2] = static_cast<std::uint32_t>(entry.attack);
        words[row][3] = static_cast<std::uint32_t>(entry.defense);
    }
    checksums(words, category);
    return words;
}

void check_name_line(const std::string& name) {
    if (name.find_first_of("\r\n") != std::string::npos)
        throw std::invalid_argument("Ranking names must fit on one line");
}

std::string submitted_name(std::string name) {
    if (name.empty())
        throw std::invalid_argument("Ranking name must not be empty");
    check_name_line(name);
    if (name.size() > RankingNameLimit) {
        std::size_t length = RankingNameLimit;
        // An ANSI name uses the full limit; UTF-8 names must stop before a partial character.
        while (length > 0 && (static_cast<unsigned char>(name[length]) & 0xc0u) == 0x80u)
            --length;
        name.resize(length);
    }
    return name;
}

bool read_name_line(std::istream& input, std::string& line) {
    line.clear();
    char character{};
    bool started = false;
    while (input.get(character)) {
        started = true;
        if (character == '\r') {
            if (input.peek() == '\n')
                input.get(character);
            return true;
        }
        if (character == '\n')
            return true;
        line += character;
    }
    return started && !input.bad();
}
} // namespace

RankingTable default_rankings(int category) {
    check_category(category);
    RankingTable table;
    for (int row = 0; row < RankingEntryCount; ++row) {
        auto& entry = table[row];
        const int level = RankingEntryCount - row;
        entry.score = level * 10;
        switch (category) {
        case 1:
            entry.hp = level * 50;
            entry.attack = 15 + level;
            break;
        case 2:
            entry.hp = level * 100;
            entry.attack = level * 5;
            break;
        case 3:
        case 5:
            entry.hp = level * 1000;
            entry.attack = level * 50;
            break;
        case 4:
            entry.hp = level * 500;
            entry.attack = 100 + level * 10;
            break;
        }
        entry.defense = entry.attack;
        entry.name = DefaultNames[category - 1][row];
    }
    return table;
}

RankingTables default_rankings() {
    RankingTables tables;
    for (int category = 1; category <= RankingCategoryCount; ++category)
        tables[category - 1] = default_rankings(category);
    return tables;
}

int ranking_position(const RankingTable& table, const RankingEntry& entry) noexcept {
    for (int row = 0; row < RankingEntryCount; ++row) {
        const auto& previous = table[row];
        // The last tie-break is attack + defense - previous HP, compared with previous attack.
        const auto combined = std::bit_cast<std::int32_t>(static_cast<std::uint32_t>(entry.attack) +
                                                          static_cast<std::uint32_t>(entry.defense) -
                                                          static_cast<std::uint32_t>(previous.hp));
        if (entry.score > previous.score ||
            (entry.score == previous.score &&
             (entry.hp > previous.hp || (entry.hp == previous.hp && combined > previous.attack))))
            return row + 1;
    }
    return 0;
}

void insert_ranking(RankingTable& table, int position, RankingEntry entry) {
    if (position < 1 || position > RankingEntryCount)
        throw std::out_of_range("Ranking position must be between 1 and 10");
    entry.name = submitted_name(std::move(entry.name));
    for (int row = RankingEntryCount - 1; row >= position; --row)
        table[row] = std::move(table[row - 1]);
    table[position - 1] = std::move(entry);
}

RankingTable load_rankings(const std::filesystem::path& directory, int category) {
    const auto defaults = default_rankings(category);
    try {
        std::ifstream data(data_path(directory, category), std::ios::binary);
        std::array<unsigned char, RankingBytes> bytes{};
        data.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        if (!data || data.peek() != std::char_traits<char>::eof())
            return defaults;
        RankingWords words{};
        std::size_t cursor{};
        for (auto& row : words)
            for (auto& word : row) {
                for (int byte = 0; byte < 4; ++byte)
                    word |= std::uint32_t(bytes[cursor++]) << (byte * 8);
            }
        auto expected = words;
        checksums(expected, category);
        if (words != expected)
            return defaults;
        RankingTable table;
        std::ifstream names(names_path(directory, category), std::ios::binary);
        for (int row = 0; row < RankingEntryCount; ++row) {
            auto& entry = table[row];
            if (!read_name_line(names, entry.name))
                return defaults;
            entry.score = std::bit_cast<std::int32_t>(words[row][0]);
            entry.hp = std::bit_cast<std::int32_t>(words[row][1]);
            entry.attack = std::bit_cast<std::int32_t>(words[row][2]);
            entry.defense = std::bit_cast<std::int32_t>(words[row][3]);
        }
        std::string extra;
        if (read_name_line(names, extra) || names.bad())
            return defaults;
        return table;
    } catch (const std::exception&) {
        return defaults;
    }
}

RankingTables load_rankings(const std::filesystem::path& directory) {
    RankingTables tables;
    for (int category = 1; category <= RankingCategoryCount; ++category)
        tables[category - 1] = load_rankings(directory, category);
    return tables;
}

void write_rankings(const std::filesystem::path& directory, int category, const RankingTable& table) {
    check_category(category);
    for (const auto& entry : table)
        check_name_line(entry.name);
    const auto words = encode(table, category);
    std::array<unsigned char, RankingBytes> bytes{};
    std::size_t cursor{};
    for (const auto& row : words)
        for (const auto word : row)
            for (int byte = 0; byte < 4; ++byte)
                bytes[cursor++] = static_cast<unsigned char>(word >> (byte * 8));
    if (!directory.empty())
        std::filesystem::create_directories(directory);
    std::ofstream data(data_path(directory, category), std::ios::binary | std::ios::trunc);
    data.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    data.close();
    if (!data)
        throw std::runtime_error("Unable to write ranking data");
    std::ofstream names(names_path(directory, category), std::ios::binary | std::ios::trunc);
    for (const auto& entry : table)
        names << entry.name << "\r\n";
    names.close();
    if (!names)
        throw std::runtime_error("Unable to write ranking names");
}

RankingTable reset_rankings(const std::filesystem::path& directory, int category) {
    auto table = default_rankings(category);
    write_rankings(directory, category, table);
    return table;
}
} // namespace tsw
