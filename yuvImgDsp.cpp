#include "yuvImgDsp.h"

YuvImgDsp::YuvImgDsp(QWidget *parent) :
    QWidget(parent)
{
    // init img & img Labels
    imgY = new QImage();
    imgY->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowY = new QLabel(this);
    imgShowY->setPixmap(QPixmap::fromImage(imgY->scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgU = new QImage();
    imgU->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowU = new QLabel(this);
    imgShowU->setPixmap(QPixmap::fromImage(imgU->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    imgV = new QImage();
    imgV->load("/Users/Kingston/Desktop/lynn.jpg");
    imgShowV = new QLabel(this);
    imgShowV->setPixmap(QPixmap::fromImage(imgV->scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

    // init title
    title = new QLabel(tr("YUV image show"));
    title->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(imgShowY, 0, 0, 10, 2);
    mainLayout->addWidget(imgShowU, 0, 2, 5, 1);
    mainLayout->addWidget(imgShowV, 5, 2, 5, 1);
    mainLayout->addWidget(title, 10, 0, 1, 3);

    // init data arrays
    dataY = NULL;
    dataU = NULL;
    dataV = NULL;
}

YuvImgDsp::~YuvImgDsp() {}

/*
RGB->Ycbcr
Y = 0.257*R+0.564*G+0.098*B+16
Cb = -0.148*R-0.291*G+0.439*B+128
Cr = 0.439*R-0.368*G-0.071*B+128

Ycbcr->RGB
R = 1.164*(Y-16)+1.596*(Cr-128)
G = 1.164*(Y-16)-0.392*(Cb-128)-0.813*(Cr-128)
B =1.164*(Y-16)+2.017*(Cb-128)
*/

void YuvImgDsp::rgb2yuv(int *a)
{
    static const float b[3][3] = {{0.257, 0.564, 0.098}, {-0.148, -0.291, 0.439}, {0.439, -0.368, -0.071}};
    float c[3] = {16, 128, 128};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            c[i] += b[i][j] * a[j];

    for (int i = 0; i < 3; i++)
        a[i] = c[i];
}

