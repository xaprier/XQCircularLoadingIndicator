#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>

#include "CircularLoadingIndicator.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    static MainWindow *Instance();

    //* Delete copy constructor and assignment operator
    MainWindow(const MainWindow &) = delete;
    MainWindow &operator=(const MainWindow &) = delete;
    //* Delete move constructor and assignment operator
    MainWindow(MainWindow &&) = delete;
    MainWindow &operator=(MainWindow &&) = delete;

  protected:
    virtual void _LoadDefaults();
    virtual void _CreateConnections();
    virtual void _GetRunningError();
    virtual void resizeEvent(QResizeEvent *event) override;

  protected slots:
    void _OnProgressColorButtonClicked();
    void _OnBackgroundColorButtonClicked();
    void _OnTextColorButtonClicked();
    void _OnSquareCheckStateChanged(int state);
    void _OnShadowCheckStateChanged(int state);
    void _OnTextEnabledCheckStateChanged(int state);
    void _OnBgEnabledCheckStateChanged(int state);
    void _OnProgressRoundedCheckStateChanged(int state);
    void _OnStartButtonClicked(bool checked);
    void _OnStopButtonClicked(bool checked);

    void _OnSegmentSizeValueChanged(int value);
    void _OnHeightSizeValueChanged(int value);
    void _OnWidthSizeValueChanged(int value);
    void _OnProgressWidthValueChanged(int value);
    void _OnMarginXValueChanged(int value);
    void _OnMarginYValueChanged(int value);
    void _OnMinimumSpeedValueChanged(double value);
    void _OnMaximumSpeedValueChanged(double value);

    void _OnTextContentChanged(const QString &text);

  private:
    static MainWindow *instance;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    xaprier::qt::widgets::CircularLoadingIndicator *indicator;
    Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_HPP
