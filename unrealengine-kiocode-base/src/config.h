#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
    static Config& GetInstance() {
        static Config instance;
        return instance;
    }

    template<typename T>
    void set(const std::string& key, const T& value) {
        data[key] = std::to_string(value);
    }

    template<typename T>
    T get(const std::string& key, const T& defaultValue) const {
        auto it = data.find(key);
        if (it != data.end()) {
            if constexpr (std::is_same<T, int>::value) {
                return std::stoi(it->second);
            }
            else if constexpr (std::is_same<T, float>::value) {
                return std::stof(it->second);
            }
            else if constexpr (std::is_same<T, bool>::value) {
                return it->second == "1" || it->second == "true";
            }
            else {
                return it->second;
            }
        }
        return defaultValue;
    }

private:
    std::unordered_map<std::string, std::string> data;

    Config() = default;
    ~Config() = default;

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

#endif
