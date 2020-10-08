#pragma once

#include <array>
#include <string>
#include <algorithm>


namespace hw2 {


    template<unsigned N>
    class Text {
    public:
        constexpr void value(std::string const & s) {

            std::copy_n(std::begin(s), N, std::begin(_data));

            if (s.size() < N) {
                std::array<char, N> filler;
                filler.fill('*');
                std::copy_n(std::begin(filler), N - s.size(), std::begin(_data) + s.size());
            }
            _data.back() = '\0';
        }

        auto value() const -> std::string {
            std::string{std::begin(_data), std::end(_data)};
            return std::string{std::begin(_data), std::end(_data)};
        }

    private:
        std::array<char, N + 1> _data;
    };

    template<unsigned N>
    class Number {
    public:
        void value(int value) {
            auto val_string = std::to_string(value);

            if (val_string.size() < N) {
                std::array<char, N> filler;
                filler.fill('0');
                const auto diff = N - val_string.size();
                std::copy_n(std::begin(filler), diff, std::begin(_data));
                std::copy_n(std::begin(val_string), val_string.size(), std::begin(_data) + diff);
            }
            else {
                std::copy_n(std::begin(val_string), N, std::begin(_data));
            }

            _data.back() = '\0';
        }

        auto value() const -> std::string {
            return std::string{std::begin(_data), std::end(_data)};
        }

    private:
        std::array<char, N + 1> _data;
    };

}
