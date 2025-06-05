#pragma once
#include <string_view>
#include <fstream>
#include <iostream>

class FileManager {
public:
    explicit FileManager(std::string_view fileName);
    FileManager();

    // To use the save function, the passed object must overload the std::ofstream operator<<
    template<typename T>
    void save(const T& obj) {
        m_file << obj << std::endl;
    }

    std::string_view fileName() const { return m_fileName; }

private:
    std::string m_fileName;
    std::ofstream m_file;
};
