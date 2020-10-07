#pragma once

#include <array>
#include <string>
#include <algorithm>


namespace hw2 {


    template<unsigned N>
    class Text {
    public:
        constexpr void value(std::string const & s) {
            _data.fill('\0');

            std::copy_n(std::begin(s), N, std::begin(_data));

            if (s.size() < N) {
                std::array<char, N> filler;
                filler.fill('*');
                std::copy_n(std::begin(filler), N, std::begin(_data) + s.size());
            }
        }

        auto value() -> std::string const {
            std::string{std::begin(_data), std::end(_data)};
            return std::string{std::begin(_data), std::end(_data)};
        }

    private:
        std::array<char, N> _data;
    };

    template<unsigned N>
    class Number {
    public:
        void value(int value) {
            auto val_string = std::to_string(value);

            _data.fill('0');

            if (val_string.size() < N) {
                std::array<char, N> filler;
                filler.fill('0');
                std::copy_n(std::begin(val_string), N - val_string.size(), std::begin(_data) + );
            }

            std::copy_n(std::begin(val_string), N, std::begin(_data));
        }

        auto value() -> std::string const {
            std::string out{std::begin(_data), std::end(_data)};
            return out;
        }

    private:
        std::array<char, N> _data;
    };

}
