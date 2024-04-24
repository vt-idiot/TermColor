#include "DropArea.h"
#include "qevent.h"
#include <QMimeData>

namespace TermColor {

DropArea::DropArea(QWidget *parent, const QSize &size) {
    setMinimumSize(size);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setAutoFillBackground(true);

    resetLabel();
}

void DropArea::dragEnterEvent(QDragEnterEvent *event) {
    setBackgroundRole(QPalette::Highlight);
    event->acceptProposedAction();
}

// To unpack dropped data and handle it
void DropArea::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            // Convert the first URL to a local file path
            QString localPath = urlList.first().toLocalFile();
            emit imageDropped(localPath);
        }
    }

    setBackgroundRole(QPalette::Midlight);
    event->acceptProposedAction();
}

void DropArea::dragLeaveEvent(QDragLeaveEvent *event) {
    resetLabel();
    event->accept();
}

void DropArea::resetLabel() {
    setLabelText("<< Drop Image >>");
    setBackgroundRole(QPalette::Midlight);
}

void DropArea::setLabelText(const QString &text) {
    setText(text);
    repaint();
}

}
