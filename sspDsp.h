#ifndef SSPDSP_H
#define SSPDSP_H

#include <QDebug>
#include <QGridLayout>
#include <QDebug>
#include <QEvent>
#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QWidget>
#include "yuvImgDsp.h"
#include "rawImg.h"

class SspDsp : public YuvImgDsp
{
    Q_OBJECT
public:
    explicit SspDsp(QString widgetName, QWidget *parent = 0);
    ~SspDsp();

    bool isYellow(int bX, int bY, int p); // This function is to judge if a pixel should be dyed yellow

    unsigned char *tmpDataY;
    unsigned char *tmpDataU;
    unsigned char *tmpDataV;
    int **crtBlock; // current 8x8 block

    RawImg *sspData;

protected:
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void sspChangingRgb(RawImg &sspData);
    void sspChangingDct(RawImg &sspData);
    void sspChangingMatrix2(int bX, int bY, int offset);

public slots:
    void sspChangedByRgb(RawImg &rawImg);
    void sspChangedByDct(RawImg &dctData);
};

#endif // SSPDSP_H
