#include "rypipetableview.h"
#include <QDebug>

RyPipeTableView::RyPipeTableView(QWidget *parent) :
    QTableView(parent){
}
void RyPipeTableView::mousePressEvent(QMouseEvent *event){
    qDebug()<<"mouse press";
}