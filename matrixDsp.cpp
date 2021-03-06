#include "matrixDsp.h"

MatrixDsp::MatrixDsp(QWidget *parent) :
    QWidget(parent)
{
    QHeaderView *vHeader;
    QHeaderView *hHeader;

    // set up quantization and compression ratio labels
    whichQM = new QLabel(tr("non-uniform quantization"));
    whichQM->setAlignment(Qt::AlignCenter);
    cmpRate = new QLabel(tr("compression ratio: unavailable"));
    cmpRate->setAlignment(Qt::AlignCenter);
    qmLabel = new QLabel(tr("Quantization Table"));
    qmLabel->setAlignment(Qt::AlignCenter);
    oriLabel = new QLabel(tr("DCT (8x8 block)"));
    oriLabel->setAlignment(Qt::AlignCenter);
    qtzLabel = new QLabel(tr("Quantized 8x8 block"));
    qtzLabel->setAlignment(Qt::AlignCenter);

    // init a grid layout
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(6);

    // init matrices
    QMMatrix = new QTableWidget(8, 8, this);
    vHeader = QMMatrix->verticalHeader();
    vHeader->sectionResizeMode(QHeaderView::Fixed);
    vHeader->setDefaultSectionSize(22);
    vHeader->hide();
    hHeader = QMMatrix->horizontalHeader();
    hHeader->sectionResizeMode(QHeaderView::Fixed);
    hHeader->setDefaultSectionSize(40);
    hHeader->hide();

    oriMatrix = new QTableWidget(8, 8, this);
    vHeader = oriMatrix->verticalHeader();
    vHeader->sectionResizeMode(QHeaderView::Fixed);
    vHeader->setDefaultSectionSize(22);
    vHeader->hide();
    hHeader = oriMatrix->horizontalHeader();
    hHeader->sectionResizeMode(QHeaderView::Fixed);
    hHeader->setDefaultSectionSize(40);
    hHeader->hide();

    qtzMatrix = new QTableWidget(8, 8, this);
    vHeader = qtzMatrix->verticalHeader();
    vHeader->sectionResizeMode(QHeaderView::Fixed);
    vHeader->setDefaultSectionSize(22);
    vHeader->hide();
    hHeader = qtzMatrix->horizontalHeader();
    hHeader->sectionResizeMode(QHeaderView::Fixed);
    hHeader->setDefaultSectionSize(40);
    hHeader->hide();

    // put quantization and compression ratio labels into the grid layout
    mainLayout->addWidget(whichQM, 0, 0, 1, 1);
    mainLayout->addWidget(cmpRate, 1, 0, 1, 1);
    mainLayout->addWidget(QMMatrix, 2, 0, 7, 1);
    mainLayout->addWidget(qmLabel, 9, 0, 1, 1);
    mainLayout->addWidget(oriMatrix, 10, 0, 7, 1);
    mainLayout->addWidget(oriLabel, 17, 0, 1, 1);
    mainLayout->addWidget(qtzMatrix, 18, 0, 7, 1);
    mainLayout->addWidget(qtzLabel, 25, 0, 1, 1);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            oriMatrix->setItem(i, j, new QTableWidgetItem(""));
            qtzMatrix->setItem(i, j, new QTableWidgetItem(""));
            QMMatrix->setItem(i, j, new QTableWidgetItem(""));
        }
}

void MatrixDsp::matrix2ChangedBySsp(int **crtBlock) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            oriMatrix->setItem(i, j, new QTableWidgetItem(QString::number(crtBlock[i][j])));

    quantizationUpdate();
}

void MatrixDsp::QMUpdated(int **QM, QString QMtitle) {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            QMMatrix->setItem(i, j, new QTableWidgetItem(QString::number(QM[i][j])));

    delete whichQM;
    whichQM = new QLabel(QMtitle);
    whichQM->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(whichQM, 0, 0, 1, 1);
    quantizationUpdate();
}

void MatrixDsp::quantizationUpdate() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (QTableWidgetItem *item = oriMatrix->item(i, j)) {
                if (item->text().isEmpty())
                    return;
            }
            if (QTableWidgetItem *item = QMMatrix->item(i, j)) {
                if (item->text().isEmpty())
                    return;
            }
        }
    qDebug() << "reach here";
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            qtzMatrix->setItem(i, j, new QTableWidgetItem(QString::number(oriMatrix->item(i, j)->text().toInt() / QMMatrix->item(i, j)->text().toInt())));
}
