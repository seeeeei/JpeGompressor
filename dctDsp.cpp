#include "dctDsp.h"

DctDsp::DctDsp(QWidget *parent) :
    YuvImgDsp(parent)
{
    dctData = NULL;
}

DctDsp::~DctDsp() {}

void DctDsp::dctChangedBySsp(RawImg &sspData)
{
    // delete former QImage and data
/*    delete imgY;
    delete imgU;
    delete imgV;*/
    if (dataY != NULL)
        delete dataY;
    if (dataU != NULL)
        delete dataU;
    if (dataV != NULL)
        delete dataV;

    // init dctData
    if (dctData != NULL)
        delete dctData;

    int Ybase=0;
    int Ubase=Ybase + sspData.width*sspData.height;
    int Vbase=Ubase + sspData.UVwidth*sspData.UVheight;

    dctData = new RawImg(sspData.width, sspData.height, sspData.UVwidth, sspData.UVheight);
    for(int i=sspData.width*sspData.height+2*sspData.UVheight*sspData.width-1; i>=0; i--)
        dctData->data[i] = sspData.data[i];

    dataY = new unsigned char[sspData.width * sspData.height * 4];
    dataU = new unsigned char[sspData.UVwidth * sspData.UVheight * 4];
    dataV = new unsigned char[sspData.UVwidth * sspData.UVheight * 4];

    // fill in data
    for (int i = 0, j = 0; i < sspData.width * sspData.height; ++i, j += 4)
    {
        dataY[j] = dataY[j + 1] = dataY[j + 2] = dctData->data[i];
        dataY[j + 3] = ~0;       // Alpha
    }
    for (int i = 0, j = 0; i < sspData.UVwidth * sspData.UVheight; ++i, j += 4)
    {
        dataU[j] = dataU[j + 1] = dataU[j + 2] = dctData->data[i+Ubase];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = dctData->data[i+Vbase];
        dataU[j + 3] = dataV[j + 3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, sspData.width, sspData.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, sspData.UVwidth, sspData.UVheight, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, sspData.UVwidth, sspData.UVheight, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    //emit dctChangingDct(*dctData);
}

void DctDsp::dctChangedByDct(RawImg &preDctData)
{
    // delete former QImage and data
/*    delete imgY;
    delete imgU;
    delete imgV;*/
    if (dataY != NULL)
        delete dataY;
    if (dataU != NULL)
        delete dataU;
    if (dataV != NULL)
        delete dataV;

    // init dctData
    if (dctData != NULL)
        delete dctData;

    int Ybase=0;
    int Ubase=Ybase + preDctData.width*preDctData.height;
    int Vbase=Ubase + preDctData.UVwidth*preDctData.UVheight;

    dctData = new RawImg(preDctData.width, preDctData.height, preDctData.UVwidth, preDctData.UVheight);
    for(int i=preDctData.width*preDctData.height+2*preDctData.UVheight*preDctData.width-1; i>=0; i--)
    {
        dctData->data[i] = preDctData.data[i];
    }

    dataY = new unsigned char[preDctData.width * preDctData.height * 4];
    dataU = new unsigned char[preDctData.UVwidth * preDctData.UVheight * 4];
    dataV = new unsigned char[preDctData.UVwidth * preDctData.UVheight * 4];

    // fill in data
    for (int i = 0, j = 0; i < preDctData.width * preDctData.height; ++i, j += 4)
    {
        dataY[j] = dataY[j + 1] = dataY[j + 2] = dctData->data[i];
        dataY[j + 3] = ~0;       // Alpha
    }
    for (int i = 0, j = 0; i < preDctData.UVwidth * preDctData.UVheight; ++i, j += 4)
    {
        dataU[j] = dataU[j + 1] = dataU[j + 2] = dctData->data[i+Ubase];
        dataV[j] = dataV[j + 1] = dataV[j + 2] = dctData->data[i+Vbase];
        dataU[j + 3] = dataV[j + 3] = ~0;       // Alpha
    }

    // display YUV images
    imgY = new QImage(dataY, preDctData.width, preDctData.height, QImage::Format_ARGB32);
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowY->show();
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);

    imgU = new QImage(dataU, preDctData.UVwidth, preDctData.UVheight, QImage::Format_ARGB32);
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowU->show();
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);

    imgV = new QImage(dataV, preDctData.UVwidth, preDctData.UVheight, QImage::Format_ARGB32);
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
    imgShowV->show();
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);

    //emit dctChangingSsp(*dctData);
}
