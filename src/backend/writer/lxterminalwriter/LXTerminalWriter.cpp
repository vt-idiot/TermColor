#include "LXTerminalWriter.h"

#include "backend/exception/Exception.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace TermColor {

using namespace TermColor::Utils;

LXTerminalWriter::LXTerminalWriter()
    : Writer(".config/lxterminal/"
    , {"lxterminal", ".conf"})
{

}

void LXTerminalWriter::writeToLocation(std::string_view name,
                                       const std::vector<color_t> &bgfg,
                                       const std::vector<color_t> &bgfgIntense,
                                       const std::vector<color_t> &regular,
                                       const std::vector<color_t> &intense) {

    // Creates a backup config file
    if (!fs::exists(this->absolutePath("_BACKUP"))) {
        fs::copy_file(this->absolutePath(""), this->absolutePath("_BACKUP"));
    }

    std::ifstream fIn{absolutePath("")};
    std::ofstream fOut{absolutePath("_out")};

    if (!fIn || !fOut) {
        throw TermColorException{"Errors opening files"};
    }

    // Read input file by line and replace each of it lines
    std::string tempStr;
    int cIterNo = 0;
    const char *bgColor{"bgcolor="};
    const char *fgColor{"fgcolor="};
    const char *cPresent{"color_preset="};
    const char *cPallete{"palette_color_"}; // palette_color_0=rgb(0,0,0)

    while (std::getline(fIn, tempStr)) {
        // background
        if (tempStr.find(bgColor) != std::string::npos) {
            fOut << bgColor << "rgb(" << bgfg.at(0).getCommaSeparatedStr() << ")\n";
        }
        // foreground
        else if (tempStr.find(fgColor) != std::string::npos) {
            fOut << fgColor << "rgb(" << bgfg.at(1).getCommaSeparatedStr() << ")\n";
        }
        // colors
        else if (tempStr.find(cPallete) != std::string::npos) {
            // regular colors
            if (cIterNo < regular.size()) {
                fOut << cPallete
                     << std::to_string(cIterNo) << "=rgb("
                     << regular.at(cIterNo).getCommaSeparatedStr()
                     << ")\n";
            }
            // intense colors
            else {
                fOut << cPallete
                     << std::to_string(cIterNo) << "=rgb("
                     << intense.at(cIterNo - regular.size()).getCommaSeparatedStr()
                     << ")\n";
            }
            ++cIterNo;
        }
        // name of color-scheme
        else if (tempStr.find(cPresent) != std::string::npos) {
            fOut << cPresent << "TermColor\n";
        }
        else {
            fOut << tempStr << "\n";
        }
    }

    fIn.close();
    fOut.close();

    // Overwrite file
    fs::rename(this->absolutePath("_out"), this->absolutePath(""));
    fs::remove(this->absolutePath("_out"));
}

}
