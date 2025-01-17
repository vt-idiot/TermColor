#ifndef LXTERMINALWRITER_H
#define LXTERMINALWRITER_H

#include "backend/writer/Writer.h"

namespace TermColor {

class LXTerminalWriter : public Writer {
public:
    explicit LXTerminalWriter();
    ~LXTerminalWriter() = default;

    void writeToLocation(std::string_view name,
                         const std::vector<color_t> &,
                         const std::vector<color_t> &,
                         const std::vector<color_t> &,
                         const std::vector<color_t> &) override;
};

}

#endif // LXTERMINALWRITER_H
