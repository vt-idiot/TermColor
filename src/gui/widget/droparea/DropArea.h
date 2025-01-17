#ifndef DROPAREA_H
#define DROPAREA_H

#include <QLabel>

namespace TermColor {

class DropArea : public QLabel {
    Q_OBJECT
public:
    explicit DropArea(QWidget *parent = nullptr, const QSize &size = {200,200});
    void setLabelText(const QString &text);

signals:
    void imageDropped(const QString &path);

private:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void resetLabel();

private:
    QLabel *label_;
};

}

#endif // DROPAREA_H
