#include "MainWindow.h"
#include <ui/gui/colorstablewidget/ColorsTableWidget.h>
#include <ui/gui/displaywidget/DisplayWidget.h>
#include <ui/gui/guimodel/GuiModel.h>
#include <ui/gui/imagedropwidget/ImageDropWidget.h>
#include <QHBoxLayout>
#include <memory>

// Main window (controller)
class MainWindow::MainWindowImpl : public QWidget {
    Q_OBJECT
public:
    explicit MainWindowImpl(MainWindow *parent);
    QHBoxLayout *getLayout() { return layout_; }

public slots:
    void undoHideWidgets();
    void onProcessColors(const std::string &imgPath);

private:
    void doLayout();
    void doConnections();

    QHBoxLayout *layout_;
    MainWindow &parent_;

    // Views
    ColorsTableWidget *colorsTableWidget_;
    DisplayWidget *displayWidget_;
    ImageDropWidget *imageDropWidget_;

    // Model
    GuiModel *guiModel_;

    // Where the logic about image processing lives
    std::unique_ptr<DominantColor> domColor;
};

MainWindow::MainWindowImpl::MainWindowImpl(MainWindow *parent) : QWidget{parent}, parent_{*parent} {
    guiModel_          = new GuiModel{this};
    colorsTableWidget_ = new ColorsTableWidget{this};
    displayWidget_     = new DisplayWidget{this};
    imageDropWidget_   = new ImageDropWidget{this};
    domColor           = std::make_unique<DominantColor>();

    layout_ = new QHBoxLayout{this};
    doLayout();

    colorsTableWidget_->hide();
    displayWidget_->hide();

    doConnections();
}

void MainWindow::MainWindowImpl::doLayout() {
    layout_->addWidget(imageDropWidget_, 0, Qt::AlignCenter);
    layout_->addWidget(colorsTableWidget_, 0, Qt::AlignTop);
    layout_->addWidget(displayWidget_, 0, Qt::AlignTop);
}

void MainWindow::MainWindowImpl::doConnections() {
    // Connect ImageDropWidget (view) to model
    connect(imageDropWidget_, SIGNAL(imageDropped(QString)), guiModel_, SLOT(onImageDropped(QString)));
    connect(guiModel_, SIGNAL(hideImageDropWidget()), imageDropWidget_, SLOT(hideWidget()));
    connect(guiModel_, SIGNAL(doProcessColors(std::string)), this, SLOT(onProcessColors(std::string)));

    // Connect ImageDropWidget (view) to controller
    connect(imageDropWidget_, SIGNAL(onHideWidget()), this, SLOT(undoHideWidgets()));

    // Do the rest of connections...
}

void MainWindow::MainWindowImpl::undoHideWidgets() {
    colorsTableWidget_->show();
    displayWidget_->show();
}

// TODO: try-catch and noexcept (in the views??)
void MainWindow::MainWindowImpl::onProcessColors(const std::string &imgPath) {
    domColor->readImage(imgPath);
    domColor->performKMeans();

    auto dominantColors = domColor->getColors();
    auto intenseColors  = domColor->intenseColors();

    dominantColors.insert(dominantColors.end(), intenseColors.begin(), intenseColors.end());
    guiModel_->setColors(dominantColors);
}

// MainWindow

MainWindow::MainWindow(int, char *[], QWidget *parent) : QMainWindow{parent} {
    pimpl_ = new MainWindowImpl{this};
    setCentralWidget(pimpl_);
    setFixedSize(845, 500);
}

#include "MainWindow.moc"
