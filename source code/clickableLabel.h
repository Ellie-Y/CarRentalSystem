#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QWidget>
#include <QLabel>

class clickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit clickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~clickableLabel();

signals:
    void clicked();

public slots:
     void mousePressEvent(QMouseEvent* event);

};

#endif // CLICKABLELABEL_H
