#include "FileManager.h"


FileManager::FileManager(std::string_view fileName)
    : m_fileName{ fileName }
    , m_file{ std::ofstream(m_fileName) } {
}

FileManager::FileManager()
    : m_fileName{ "output.txt" }
    , m_file{ std::ofstream(m_fileName) } {
}