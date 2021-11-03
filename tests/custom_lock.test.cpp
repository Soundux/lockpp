#include <catch2/catch.hpp>
#include <lock.hpp>

TEST_CASE("Check if custom locks work", "[custom_locking]")
{
    lockpp::lock<int> test(10);

    {
        auto read_1 = test.read();
        auto read_2 = test.read();
    }
    {
        auto read_1 = test.read<std::unique_lock>();
        auto read_2 = test.read<std::unique_lock>(std::adopt_lock);
    }

    REQUIRE_THROWS([&test]() {
        auto read_1 = test.read<std::unique_lock>();
        auto read_2 = test.read<std::unique_lock>();
        return true;
    }());
}