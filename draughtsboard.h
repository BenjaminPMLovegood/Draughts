#ifndef DRAUGHTSBOARD_H
#define DRAUGHTSBOARD_H

#include <QWidget>

class DraughtsBoard : public QWidget {
    Q_OBJECT
public:
    explicit DraughtsBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void paintBackground(QPainter & p);

signals:
    void onCellClick(int row, int column);

public slots:
};

#endif  // DRAUGHTSBOARD_H
