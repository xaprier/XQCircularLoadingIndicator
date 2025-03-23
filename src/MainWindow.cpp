#include "MainWindow.hpp"

#include <qboxlayout.h>
#include <qcheckbox.h>
#include <qgridlayout.h>
#include <qlineedit.h>
#include <qnamespace.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qspinbox.h>

#include <QColorDialog>
#include <QFontDialog>
#include <QLayout>
#include <QSpinBox>

#include "../design/ui_MainWindow.h"

MainWindow *MainWindow::instance = nullptr;

MainWindow *MainWindow::Instance() {
    if (MainWindow::instance == nullptr) MainWindow::instance = new MainWindow();
    return MainWindow::instance;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto layout = new QGridLayout(this->ui->indicatorGroupBox);
    this->ui->indicatorGroupBox->setLayout(layout);

    this->indicator = new xaprier::Qt::Widgets::XQCircularLoadingIndicator(this->ui->indicatorGroupBox);
    this->indicator->SetProgressAlignment(Qt::AlignCenter);
    this->indicator->SetSquare(true);

    layout->addWidget(this->indicator);

    this->_LoadDefaults();
    this->_CreateConnections();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::_LoadDefaults() {
    this->ui->progressColorPushButton->setStyleSheet(
        QString("QPushButton { background-color: %1; }").arg(this->indicator->GetProgressColor().name()));
    this->ui->backgroundColorPushButton->setStyleSheet(QString("QPushButton { background-color: %1; }").arg(this->indicator->GetBgColor().name()));
    this->ui->textColorPushButton->setStyleSheet(QString("QPushButton { background-color: %1; }").arg(this->indicator->GetTextColor().name()));

    this->ui->squareCheckBox->setChecked(this->indicator->GetSquare());
    this->ui->shadowCheckBox->setChecked(this->indicator->GetShadow());
    this->ui->textEnableCheckBox->setChecked(this->indicator->GetEnableText());
    this->ui->backgroundEnableCheckBox->setChecked(this->indicator->GetEnableBg());
    this->ui->progressRoundedCapCheckBox->setChecked(this->indicator->GetProgressRoundedCap());

    auto width = this->width();
    auto height = this->height();
    this->ui->heightSizeSpinBox->setMaximum(height);
    this->ui->widthSizeSpinBox->setMaximum(width);

    this->ui->segmentSizeSpinBox->setValue(this->indicator->GetSegmentSize());
    this->ui->heightSizeSpinBox->setValue(this->indicator->GetHeight());
    this->ui->widthSizeSpinBox->setValue(this->indicator->GetWidth());
    this->ui->progressWidthSpinBox->setValue(this->indicator->GetProgressWidth());

    this->ui->marginXSpinBox->setValue(this->indicator->GetMarginX());
    this->ui->marginYSpinBox->setValue(this->indicator->GetMarginY());
    this->ui->minimumSpeedSpinBox->setValue(this->indicator->GetMinimumSpeed());
    this->ui->maximumSpeedSpinBox->setValue(this->indicator->GetMaximumSpeed());

    this->ui->textContentLineEdit->setText(this->indicator->GetText());
}

void MainWindow::_CreateConnections() {
    connect(this->ui->progressColorPushButton, &QPushButton::clicked, this, &MainWindow::_OnProgressColorButtonClicked);
    connect(this->ui->backgroundColorPushButton, &QPushButton::clicked, this, &MainWindow::_OnBackgroundColorButtonClicked);
    connect(this->ui->textColorPushButton, &QPushButton::clicked, this, &MainWindow::_OnTextColorButtonClicked);

    connect(this->ui->squareCheckBox, &QCheckBox::stateChanged, this, &MainWindow::_OnSquareCheckStateChanged);
    connect(this->ui->shadowCheckBox, &QCheckBox::stateChanged, this, &MainWindow::_OnShadowCheckStateChanged);
    connect(this->ui->textEnableCheckBox, &QCheckBox::stateChanged, this, &MainWindow::_OnTextEnabledCheckStateChanged);
    connect(this->ui->backgroundEnableCheckBox, &QCheckBox::stateChanged, this, &MainWindow::_OnBgEnabledCheckStateChanged);
    connect(this->ui->progressRoundedCapCheckBox, &QCheckBox::stateChanged, this, &MainWindow::_OnProgressRoundedCheckStateChanged);

    connect(this->ui->startPushButton, &QPushButton::clicked, this, &MainWindow::_OnStartButtonClicked);
    connect(this->ui->stopPushButton, &QPushButton::clicked, this, &MainWindow::_OnStopButtonClicked);

    connect(this->ui->segmentSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnSegmentSizeValueChanged);
    connect(this->ui->heightSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnHeightSizeValueChanged);
    connect(this->ui->widthSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnWidthSizeValueChanged);
    connect(this->ui->progressWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnProgressWidthValueChanged);
    connect(this->ui->marginXSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnMarginXValueChanged);
    connect(this->ui->marginYSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::_OnMarginYValueChanged);
    connect(this->ui->minimumSpeedSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_OnMinimumSpeedValueChanged);
    connect(this->ui->maximumSpeedSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::_OnMaximumSpeedValueChanged);

    connect(this->ui->textContentLineEdit, &QLineEdit::textChanged, this, &MainWindow::_OnTextContentChanged);
}

void MainWindow::_GetRunningError() {
    QMessageBox::warning(this, "Warning", "The indicator is running. Please stop the indicator to change the settings.");
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    auto width = this->width();
    auto height = this->height();
    this->ui->heightSizeSpinBox->setMaximum(height);
    this->ui->widthSizeSpinBox->setMaximum(width);
}

void MainWindow::_OnProgressColorButtonClicked() {
    if (this->indicator->GetRunning()) return _GetRunningError();
    QColorDialog colorDialog;

    colorDialog.setCurrentColor(Qt::red);

    if (colorDialog.exec()) {
        QColor selectedColor = colorDialog.selectedColor();
        QString colorHex = selectedColor.name();

        this->indicator->SetProgressColor(colorHex);
        this->ui->progressColorPushButton->setStyleSheet(QString("QPushButton { background-color: %1; }").arg(colorHex));
    }
}

void MainWindow::_OnBackgroundColorButtonClicked() {
    if (this->indicator->GetRunning()) return _GetRunningError();
    QColorDialog colorDialog;

    // Pencere başlangıçta görünecek olan renk
    colorDialog.setCurrentColor(Qt::red);

    // Renk seçildiğinde gerçekleştirilecek işlemler
    if (colorDialog.exec()) {
        // Kullanıcı bir renk seçti
        QColor selectedColor = colorDialog.selectedColor();
        QString colorHex = selectedColor.name();  // Renk değerini al

        this->indicator->SetBgColor(colorHex);
        this->ui->backgroundColorPushButton->setStyleSheet(QString("QPushButton { background-color: %1; }").arg(colorHex));
    }
}

void MainWindow::_OnTextColorButtonClicked() {
    if (this->indicator->GetRunning()) return _GetRunningError();
    QColorDialog colorDialog;

    // Pencere başlangıçta görünecek olan renk
    colorDialog.setCurrentColor(Qt::red);

    // Renk seçildiğinde gerçekleştirilecek işlemler
    if (colorDialog.exec()) {
        // Kullanıcı bir renk seçti
        QColor selectedColor = colorDialog.selectedColor();
        QString colorHex = selectedColor.name();  // Renk değerini al

        this->indicator->SetTextColor(colorHex);
        this->ui->textColorPushButton->setStyleSheet(QString("QPushButton { background-color: %1; }").arg(colorHex));
    }
}

void MainWindow::_OnSquareCheckStateChanged(int state) {
    bool checked = state == Qt::Checked;
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->squareCheckBox->blockSignals(true);
        this->ui->squareCheckBox->setChecked(!checked);
        this->ui->squareCheckBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetSquare(checked);
}

void MainWindow::_OnShadowCheckStateChanged(int state) {
    bool checked = state == Qt::Checked;
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->shadowCheckBox->blockSignals(true);
        this->ui->shadowCheckBox->setChecked(!checked);
        this->ui->shadowCheckBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetShadow(checked);
}

void MainWindow::_OnTextEnabledCheckStateChanged(int state) {
    bool checked = state == Qt::Checked;
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->textEnableCheckBox->blockSignals(true);
        this->ui->textEnableCheckBox->setChecked(!checked);
        this->ui->textEnableCheckBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetEnableText(checked);
}

void MainWindow::_OnBgEnabledCheckStateChanged(int state) {
    bool checked = state == Qt::Checked;
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->backgroundEnableCheckBox->blockSignals(true);
        this->ui->backgroundEnableCheckBox->setChecked(!checked);
        this->ui->backgroundEnableCheckBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetEnableBg(checked);
}

void MainWindow::_OnProgressRoundedCheckStateChanged(int state) {
    bool checked = state == Qt::Checked;
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->progressRoundedCapCheckBox->blockSignals(true);
        this->ui->progressRoundedCapCheckBox->setChecked(!checked);
        this->ui->progressRoundedCapCheckBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetProgressRoundedCap(checked);
}

void MainWindow::_OnStartButtonClicked(bool checked) { this->indicator->Start(); }
void MainWindow::_OnStopButtonClicked(bool checked) { this->indicator->Stop(); }

void MainWindow::_OnSegmentSizeValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->segmentSizeSpinBox->blockSignals(true);
        this->ui->segmentSizeSpinBox->setValue(this->indicator->GetSegmentSize());
        this->ui->segmentSizeSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetSegmentSize(value);
}

void MainWindow::_OnHeightSizeValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->heightSizeSpinBox->blockSignals(true);
        this->ui->heightSizeSpinBox->setValue(this->indicator->GetHeight());
        this->ui->heightSizeSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetHeight(value);
}

void MainWindow::_OnWidthSizeValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->widthSizeSpinBox->blockSignals(true);
        this->ui->widthSizeSpinBox->setValue(this->indicator->GetWidth());
        this->ui->widthSizeSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetWidth(value);
}

void MainWindow::_OnProgressWidthValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->progressWidthSpinBox->blockSignals(true);
        this->ui->progressWidthSpinBox->setValue(this->indicator->GetProgressWidth());
        this->ui->progressWidthSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetProgressWidth(value);
}

void MainWindow::_OnMarginXValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->marginXSpinBox->blockSignals(true);
        this->ui->marginXSpinBox->setValue(this->indicator->GetMarginX());
        this->ui->marginXSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetMarginX(value);
}

void MainWindow::_OnMarginYValueChanged(int value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->marginYSpinBox->blockSignals(true);
        this->ui->marginYSpinBox->setValue(this->indicator->GetMarginY());
        this->ui->marginYSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetMarginY(value);
}

void MainWindow::_OnMinimumSpeedValueChanged(double value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->minimumSpeedSpinBox->blockSignals(true);
        this->ui->minimumSpeedSpinBox->setValue(this->indicator->GetMinimumSpeed());
        this->ui->minimumSpeedSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetMinimumSpeed(value);
}

void MainWindow::_OnMaximumSpeedValueChanged(double value) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->maximumSpeedSpinBox->blockSignals(true);
        this->ui->maximumSpeedSpinBox->setValue(this->indicator->GetMaximumSpeed());
        this->ui->maximumSpeedSpinBox->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetMaximumSpeed(value);
}

void MainWindow::_OnTextContentChanged(const QString &text) {
    if (this->indicator->GetRunning()) {
        // set the state back to the previous state
        this->ui->textContentLineEdit->blockSignals(true);
        this->ui->textContentLineEdit->setText(this->indicator->GetText());
        this->ui->textContentLineEdit->blockSignals(false);
        return _GetRunningError();
    }
    this->indicator->SetText(text);
}