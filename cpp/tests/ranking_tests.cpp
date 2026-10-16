#include "tsw/rankings.hpp"
#include <bit>
#include <catch2/catch_test_macros.hpp>
#include <chrono>
#include <fstream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace tsw;

namespace {
struct RankingFiles {
    std::filesystem::path directory =
        std::filesystem::path(TSW_TEST_TEMP) /
        ("rankings-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));

    RankingFiles() { std::filesystem::create_directories(directory); }

    ~RankingFiles() {
        std::error_code error;
        std::filesystem::remove_all(directory, error);
    }

    std::filesystem::path data(int category) const {
        return directory / ("option" + std::to_string(category) + ".dat");
    }

    std::filesystem::path names(int category) const {
        return directory / ("option" + std::to_string(category) + "1.dat");
    }
};

std::vector<unsigned char> read_bytes(const std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

void write_bytes(const std::filesystem::path& path, const std::vector<unsigned char>& bytes) {
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    output.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
}

void write_text(const std::filesystem::path& path, const std::string& text) {
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    output << text;
}

std::int32_t stored_word(const std::vector<unsigned char>& bytes, int row, int column) {
    const auto offset = static_cast<std::size_t>((row * 6 + column) * 4);
    const auto value = std::uint32_t(bytes.at(offset)) | (std::uint32_t(bytes.at(offset + 1)) << 8) |
                       (std::uint32_t(bytes.at(offset + 2)) << 16) |
                       (std::uint32_t(bytes.at(offset + 3)) << 24);
    return std::bit_cast<std::int32_t>(value);
}
} // namespace

TEST_CASE("Ranking defaults cover all five checkpoint categories", "[rankings]") {
    const auto tables = default_rankings();
    const std::array<std::int32_t, 5> top_hp{500, 1000, 10000, 5000, 10000};
    const std::array<std::int32_t, 5> top_attack{25, 50, 500, 200, 500};
    const std::array<std::string, 5> first_names{"Skeleton A", "Vampire", "Magic Master", "Golden Knight",
                                                 "Zeno"};
    const std::array<std::string, 5> last_names{"Iron Shield", "Blue Crystal", "Lucky Gold",
                                                "Shield of Knight", "Holy Shield"};
    for (int category = 1; category <= RankingCategoryCount; ++category) {
        const auto& table = tables[category - 1];
        CAPTURE(category);
        REQUIRE(table == default_rankings(category));
        REQUIRE(table[0].score == 100);
        REQUIRE(table[0].hp == top_hp[category - 1]);
        REQUIRE(table[0].attack == top_attack[category - 1]);
        REQUIRE(table[0].defense == table[0].attack);
        REQUIRE(table[0].name == first_names[category - 1]);
        REQUIRE(table[9].score == 10);
        REQUIRE(table[9].name == last_names[category - 1]);
    }
    REQUIRE_THROWS_AS(default_rankings(0), std::out_of_range);
    REQUIRE_THROWS_AS(default_rankings(6), std::out_of_range);
}

TEST_CASE("Ranking tie breaks preserve the saved scoring rules", "[rankings]") {
    auto table = default_rankings(1);
    REQUIRE(ranking_position(table, {415, 1000, 100, 100, "Hero"}) == 1);
    REQUIRE(ranking_position(table, {100, 501, 0, 0, "Hero"}) == 1);
    REQUIRE(ranking_position(table, {100, 499, 999, 999, "Hero"}) == 2);
    // Equal score and HP compare ATK + DEF - row HP with the row's ATK, strictly.
    REQUIRE(ranking_position(table, {100, 500, 25, 500, "Hero"}) == 2);
    REQUIRE(ranking_position(table, {100, 500, 26, 500, "Hero"}) == 1);
    REQUIRE(ranking_position(table, {10, 50, 16, 50, "Hero"}) == 0);
    REQUIRE(ranking_position(table, {10, 50, 17, 50, "Hero"}) == 10);
    const auto maximum = std::numeric_limits<std::int32_t>::max();
    REQUIRE(ranking_position(table, {100, 500, maximum, maximum, "Hero"}) == 2);
    for (auto& entry : table)
        entry.score = 500;
    REQUIRE(ranking_position(table, {415, 1000, 100, 100, "Hero"}) == 0);
}

TEST_CASE("Ranking insertion shifts entries and limits submitted names", "[rankings]") {
    auto table = default_rankings(1);
    const auto before = table;
    const RankingEntry candidate{95, 1234, 321, 222, "ABCDEFGHIJKLMNOPQRSTUV"};
    insert_ranking(table, 5, candidate);
    for (int row = 0; row < 4; ++row)
        REQUIRE(table[row] == before[row]);
    REQUIRE((table[4] == RankingEntry{95, 1234, 321, 222, "ABCDEFGHIJKLMNOPQR"}));
    for (int row = 5; row < RankingEntryCount; ++row)
        REQUIRE(table[row] == before[row - 1]);
    insert_ranking(table, 10, {1, 2, 3, 4, "Last"});
    REQUIRE((table[9] == RankingEntry{1, 2, 3, 4, "Last"}));
    const std::string utf8 = "abcdefghijklm\xe5\xa1\x94\xe5\x86\x85";
    insert_ranking(table, 1, {500, 1000, 10, 20, utf8});
    REQUIRE(table[0].name == "abcdefghijklm\xe5\xa1\x94");
    REQUIRE(table[0].name.size() <= RankingNameLimit);
    const auto unchanged = table;
    REQUIRE_THROWS_AS(insert_ranking(table, 0, candidate), std::out_of_range);
    REQUIRE_THROWS_AS(insert_ranking(table, 11, candidate), std::out_of_range);
    REQUIRE_THROWS_AS(insert_ranking(table, 1, {1, 2, 3, 4, ""}), std::invalid_argument);
    REQUIRE_THROWS_AS(insert_ranking(table, 1, {1, 2, 3, 4, "Two\nlines"}), std::invalid_argument);
    REQUIRE(table == unchanged);
}

TEST_CASE("Ranking files store the Pascal rows checksums and category markers", "[rankings]") {
    RankingFiles files;
    const std::array<std::array<std::int32_t, 6>, 5> first_rows{{{{100, 500, 25, 25, 650, 250}},
                                                                 {{100, 1000, 50, 50, 1200, 300}},
                                                                 {{100, 10000, 500, 500, 11100, 1200}},
                                                                 {{100, 5000, 200, 200, 5500, 600}},
                                                                 {{100, 10000, 500, 500, 11100, 1200}}}};
    const std::array<std::array<std::int32_t, 6>, 5> column_sums{{{{550, 2750, 205, 205, 3710, 1510}},
                                                                  {{550, 5500, 275, 275, 6600, 1650}},
                                                                  {{550, 55000, 2750, 2750, 61050, 6600}},
                                                                  {{550, 27500, 1550, 1550, 31150, 4200}},
                                                                  {{550, 55000, 2750, 2750, 61050, 6600}}}};
    const std::array<std::array<std::int32_t, 6>, 5> alternating_sums{
        {{{600, 3000, 210, 210, 4020, -401}},
         {{600, 6000, 300, 300, 7200, -402}},
         {{600, 60000, 3000, 3000, 66600, -403}},
         {{600, 30000, 1600, 1600, 33800, -404}},
         {{600, 60000, 3000, 3000, 66600, -405}}}};
    for (int category = 1; category <= RankingCategoryCount; ++category) {
        CAPTURE(category);
        const auto table = default_rankings(category);
        write_rankings(files.directory, category, table);
        const auto bytes = read_bytes(files.data(category));
        REQUIRE(bytes.size() == 288);
        for (int column = 0; column < 6; ++column) {
            CAPTURE(column);
            REQUIRE(stored_word(bytes, 0, column) == first_rows[category - 1][column]);
            REQUIRE(stored_word(bytes, 10, column) == column_sums[category - 1][column]);
            REQUIRE(stored_word(bytes, 11, column) == alternating_sums[category - 1][column]);
        }
        const auto names = read_bytes(files.names(category));
        const std::string text(names.begin(), names.end());
        REQUIRE(text.starts_with(table[0].name + "\r\n"));
        REQUIRE(text.ends_with(table[9].name + "\r\n"));
        REQUIRE(load_rankings(files.directory, category) == table);
    }
}

TEST_CASE("Ranking checksums wrap without losing signed values", "[rankings]") {
    RankingFiles files;
    auto table = default_rankings(1);
    const auto maximum = std::numeric_limits<std::int32_t>::max();
    for (auto& entry : table)
        entry.score = entry.hp = entry.attack = entry.defense = maximum;
    write_rankings(files.directory, 1, table);
    const auto bytes = read_bytes(files.data(1));
    REQUIRE(stored_word(bytes, 0, 4) == -4);
    REQUIRE(stored_word(bytes, 0, 5) == -4);
    REQUIRE(stored_word(bytes, 10, 0) == -10);
    REQUIRE(stored_word(bytes, 10, 4) == -40);
    REQUIRE(stored_word(bytes, 11, 0) == -10);
    REQUIRE(load_rankings(files.directory, 1) == table);
    table[0].score = std::numeric_limits<std::int32_t>::min();
    table[0].defense = -123;
    write_rankings(files.directory, 1, table);
    REQUIRE(load_rankings(files.directory, 1) == table);
}

TEST_CASE("Invalid numeric ranking files restore the complete default table", "[rankings]") {
    RankingFiles files;
    for (int category = 1; category <= RankingCategoryCount; ++category) {
        CAPTURE(category);
        const auto defaults = default_rankings(category);
        REQUIRE(load_rankings(files.directory, category) == defaults);
        auto custom = defaults;
        insert_ranking(custom, 1, {415, 1234, 321, 222, "Previous winner"});
        write_rankings(files.directory, category, custom);
        const auto valid = read_bytes(files.data(category));
        REQUIRE(load_rankings(files.directory, category) == custom);
        for (int word : {0, 4, 5, 60, 65, 66, 71}) {
            CAPTURE(word);
            auto corrupt = valid;
            corrupt[word * 4] ^= 1;
            write_bytes(files.data(category), corrupt);
            REQUIRE(load_rankings(files.directory, category) == defaults);
        }
        for (std::size_t length : {std::size_t(0), std::size_t(287), std::size_t(289)}) {
            CAPTURE(length);
            auto corrupt = valid;
            corrupt.resize(length);
            write_bytes(files.data(category), corrupt);
            REQUIRE(load_rankings(files.directory, category) == defaults);
        }
    }
}

TEST_CASE("Invalid ranking name files discard loaded numeric rows", "[rankings]") {
    RankingFiles files;
    for (int category = 1; category <= RankingCategoryCount; ++category) {
        CAPTURE(category);
        const auto defaults = default_rankings(category);
        auto custom = defaults;
        insert_ranking(custom, 1, {415, 1234, 321, 222, "Previous winner"});
        write_rankings(files.directory, category, custom);
        std::filesystem::remove(files.names(category));
        REQUIRE(load_rankings(files.directory, category) == defaults);
        for (int count : {0, 9, 11}) {
            CAPTURE(count);
            std::string text;
            for (int row = 0; row < count; ++row)
                text += "Name " + std::to_string(row) + "\r\n";
            write_text(files.names(category), text);
            REQUIRE(load_rankings(files.directory, category) == defaults);
        }
        for (const std::string ending : {"\r\n", "\n", "\r"}) {
            CAPTURE(ending);
            std::string text;
            for (const auto& entry : custom)
                text += entry.name + ending;
            write_text(files.names(category), text);
            REQUIRE(load_rankings(files.directory, category) == custom);
        }
        std::string text;
        for (int row = 0; row < RankingEntryCount; ++row) {
            text += custom[row].name;
            if (row + 1 != RankingEntryCount)
                text += '\n';
        }
        write_text(files.names(category), text);
        REQUIRE(load_rankings(files.directory, category) == custom);
    }
}

TEST_CASE("Ranking persistence and reset keep categories independent", "[rankings]") {
    RankingFiles files;
    auto second = default_rankings(2);
    auto third = default_rankings(3);
    insert_ranking(second, 1, {500, 1000, 100, 100, "Second winner"});
    insert_ranking(third, 3, {500, 1000, 100, 100, "Third winner"});
    write_rankings(files.directory, 2, second);
    write_rankings(files.directory, 3, third);
    REQUIRE(load_rankings(files.directory, 2) == second);
    REQUIRE(load_rankings(files.directory, 3) == third);
    REQUIRE(reset_rankings(files.directory, 3) == default_rankings(3));
    REQUIRE(load_rankings(files.directory, 3) == default_rankings(3));
    REQUIRE(load_rankings(files.directory, 2) == second);
    std::filesystem::copy_file(files.data(2), files.data(3),
                               std::filesystem::copy_options::overwrite_existing);
    REQUIRE(load_rankings(files.directory, 3) == default_rankings(3));
    REQUIRE_THROWS_AS(load_rankings(files.directory, 0), std::out_of_range);
    REQUIRE_THROWS_AS(write_rankings(files.directory, 6, second), std::out_of_range);
    REQUIRE_THROWS_AS(reset_rankings(files.directory, 0), std::out_of_range);
    second[0].name = "Broken\rline";
    REQUIRE_THROWS_AS(write_rankings(files.directory, 2, second), std::invalid_argument);
    second[0].name = "Second winner";
    REQUIRE(load_rankings(files.directory, 2) == second);
}
