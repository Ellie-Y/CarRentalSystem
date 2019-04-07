#include "clickableLabel.h"

clickableLabel::clickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

clickableLabel::~clickableLabel() {}

void clickableLabel::mousePressEvent(QMouseEvent *event) {
    //clickable label
    emit clicked();
}
