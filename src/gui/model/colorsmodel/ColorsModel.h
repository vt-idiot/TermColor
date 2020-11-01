#ifndef COLORSMODEL_H
#define COLORSMODEL_H

#include "backend/dominantcolor/DominantColor.h"
#include <QObject>
#include <memory>
#include <map>

namespace TermColor {

class ColorsModel : public QObject {
    class ColorsModelImpl;
    Q_OBJECT
public:
    explicit ColorsModel(QObject *parent = nullptr);
    ~ColorsModel();

    // To mark what changed: nothing, new colors added, changed background color
    enum class ChangedState { None, NewColors, Background };

    // Storing colors data
    struct Colors {
        Colors();

        ChangedState changedState_;
        std::vector<TermColor::Utils::color> BGFG_;        // Background and Foreground colors
        std::vector<TermColor::Utils::color> BGFGintense_; // Same as above, but intense
        std::vector<TermColor::Utils::color> regular_;     // Regular colors
        std::vector<TermColor::Utils::color> intense_;     // Intense colors
    };

    // Methods for Colors
    const Colors &getColors() const;
    void setImgColors(const std::vector<TermColor::Utils::color> &colors);
    void setBGFGColors(const std::vector<TermColor::Utils::color> &bgfg);

public slots:
    void onImageDropped(const QString& path);

signals:
    void hideImageDropWidget();
    void doProcessColors(std::string_view);
    void modelChanged();

private:
    std::unique_ptr<ColorsModelImpl> pimpl_;
};

}

#endif // COLORSMODEL_H