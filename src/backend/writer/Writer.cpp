#include "Writer.h"

#include "backend/exception/Exception.h"
#include <zconf.h>
#include <windows.h>
#include <Lmcons.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace TermColor {

Writer::Writer(std::string_view loc, const filename &fileInfo)
    : location_{loc.data()}
    , fileInfo_{fileInfo}
{
    checkDirectory(location_);
}

std::string Writer::absolutePath(std::string_view fileName) {
    return location_ + fileInfo_.prefix + fileName.data() + fileInfo_.format;
}

void Writer::checkDirectory(std::string_view path) {
    fs::path dirPath{path.data()};
    fs::directory_entry dirEntry{dirPath};
}

}
