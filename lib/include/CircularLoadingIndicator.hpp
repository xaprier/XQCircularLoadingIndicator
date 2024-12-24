#ifndef CIRCULARLOADINGINDICATOR_HPP
#define CIRCULARLOADINGINDICATOR_HPP

#include <QColor>
#include <QDebug>
#include <QFont>
#include <QFuture>
#include <QGraphicsDropShadowEffect>
#include <QMap>
#include <QPaintEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include <cmath>

namespace xaprier {
namespace qt {
namespace widgets {
class CircularLoadingIndicator : public QWidget {
    Q_OBJECT
    Q_PROPERTY(double maxSpeed MEMBER m_maxSpeed READ GetMaximumSpeed WRITE SetMaximumSpeed NOTIFY si_MaximumSpeedChanged)
    Q_PROPERTY(double minSpeed MEMBER m_minSpeed READ GetMinimumSpeed WRITE SetMinimumSpeed NOTIFY si_MinimumSpeedChanged)
    Q_PROPERTY(int segmentSize MEMBER m_segmentSize READ GetSegmentSize WRITE SetSegmentSize NOTIFY si_SegmentChanged)
    Q_PROPERTY(int width MEMBER m_width READ GetWidth WRITE SetWidth NOTIFY si_WidthChanged)
    Q_PROPERTY(int height MEMBER m_height READ GetHeight WRITE SetHeight NOTIFY si_HeightChanged)
    Q_PROPERTY(int marginX MEMBER m_marginX READ GetMarginX WRITE SetMarginX NOTIFY si_MarginXChanged)
    Q_PROPERTY(int marginY MEMBER m_marginY READ GetMarginY WRITE SetMarginY NOTIFY si_MarginYChanged)
    Q_PROPERTY(int progressWidth MEMBER m_progressWidth READ GetProgressWidth WRITE SetProgressWidth NOTIFY si_ProgressWidthChanged)

    Q_PROPERTY(bool square MEMBER m_square READ GetSquare WRITE SetSquare NOTIFY si_SquareChanged)
    Q_PROPERTY(bool shadow MEMBER m_shadow READ GetShadow WRITE SetShadow NOTIFY si_ShadowChanged)
    Q_PROPERTY(bool progressRoundedCap MEMBER m_progressRoundedCap READ GetProgressRoundedCap WRITE SetProgressRoundedCap NOTIFY
                   si_ProgressRoundedCapChanged)
    Q_PROPERTY(bool enableBg MEMBER m_enableBg READ GetEnableBg WRITE SetEnableBg NOTIFY si_EnableBgChanged)
    Q_PROPERTY(bool enableText MEMBER m_enableText READ GetEnableText WRITE SetEnableText NOTIFY si_EnableTextChanged)

    Q_PROPERTY(Qt::Alignment progressAlignment MEMBER m_progressAlignment READ GetProgressAlignment WRITE SetProgressAlignment NOTIFY
                   si_ProgressAlignmentChanged)

    Q_PROPERTY(QColor bgColor MEMBER m_bgColor READ GetBgColor WRITE SetBgColor NOTIFY si_BgColorChanged)
    Q_PROPERTY(QColor progressColor MEMBER m_progressColor READ GetProgressColor WRITE SetProgressColor NOTIFY si_ProgressColorChanged)
    Q_PROPERTY(QColor textColor MEMBER m_textColor READ GetTextColor WRITE SetTextColor NOTIFY si_TextColorChanged)

    Q_PROPERTY(QString text MEMBER m_text READ GetText WRITE SetText NOTIFY si_TextChanged)

  public:
    /**
     * @brief Construct a new Circular Progress object
     *
     * @param parent Parent widget
     */
    CircularLoadingIndicator(QWidget *parent = nullptr);
    ~CircularLoadingIndicator();

    /**
     * @brief Starts the thread for animate loading
     */
    void Start();

    /**
     * @brief Stops the thread for animation of loading
     */
    void Stop();

    ///< SETTERS
    void SetMaximumSpeed(const double &speed = 3.0);
    void SetMinimumSpeed(const double &speed = 1.0);
    void SetUpdateValue(const int &updateValue = 2);
    void SetSegmentSize(const int &segmentSize = 12);
    void SetWidth(const int &width = 200);
    void SetHeight(const int &height = 200);
    void SetMargin(const int &x = 0, const int &y = 0);
    void SetMarginX(const int &x = 0);
    void SetMarginY(const int &y = 0);
    void SetProgressWidth(const int &width = 10);

    void SetSquare(const bool &enable = false);
    void SetShadow(const bool &enable = true);
    void SetProgressRoundedCap(const bool &enable = true);
    void SetEnableBg(const bool &enable = true);
    void SetEnableText(const bool &enable = false);

    void SetProgressAlignment(const Qt::Alignment &alignment = Qt::AlignCenter);

    void SetBgColor(const QColor &color = "#44475a");
    void SetProgressColor(const QColor &color = "#498BD1");
    void SetTextColor(const QColor &color = "#498BD1");

    void SetText(const QString &text = "Loading...");

    ///< GETTERS
    double GetMaximumSpeed() const { return m_maxSpeed; }
    double GetMinimumSpeed() const { return m_minSpeed; }
    int GetSegmentSize() const { return m_segmentSize; }
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetMarginX() const { return m_marginX; }
    int GetMarginY() const { return m_marginY; }
    int GetProgressWidth() const { return m_progressWidth; }

    bool GetSquare() const { return m_square; }
    bool GetShadow() const { return m_shadow; }
    bool GetProgressRoundedCap() const { return m_progressRoundedCap; }
    bool GetEnableBg() const { return m_enableBg; }
    bool GetEnableText() const { return m_enableText; }

    bool GetRunning() const { return m_running; }

    Qt::Alignment GetProgressAlignment() const { return m_progressAlignment; }

    QColor GetBgColor() const { return m_bgColor; }
    QColor GetProgressColor() const { return m_progressColor; }
    QColor GetTextColor() const { return m_textColor; }

    QString GetText() const { return m_text; }

  signals:
    void si_MaximumSpeedChanged(double speed);
    void si_MinimumSpeedChanged(double speed);
    void si_SegmentChanged(int segmentSize);
    void si_WidthChanged(int width);
    void si_HeightChanged(int height);
    void si_MarginChanged(int x, int y);
    void si_MarginXChanged(int x);
    void si_MarginYChanged(int y);
    void si_ProgressWidthChanged(int width);

    void si_SquareChanged(bool enable);
    void si_ShadowChanged(bool enable);
    void si_ProgressRoundedCapChanged(bool enable);
    void si_EnableBgChanged(bool enable);
    void si_EnableTextChanged(bool enable);

    void si_ProgressAlignmentChanged(Qt::Alignment alignment);

    void si_BgColorChanged(QColor color);
    void si_ProgressColorChanged(QColor color);
    void si_TextColorChanged(QColor color);

    void si_TextChanged(QString text);

  protected:
    /**
     * @brief The thread's function for progressing the loading animation
     */
    void _Progress();

    /**
     * @brief Qt's overrided functions for painting the widget and resizing the
     * widget
     */
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

  private:
    const int m_circularDegree = 360;
    QFuture<void> m_future;
    double m_maxSpeed = 3.0, m_minSpeed = 1.0;
    bool m_running = false;
    double m_currentValue = 0;
    int m_segmentSize = 12;
    QWidget *m_superClass = nullptr;
    int m_width = 200;
    int m_height = 200;
    int m_marginX = 0;
    int m_marginY = 0;
    int m_progressWidth = 10;
    bool m_square = false;  //> square progress bar
    bool m_shadow = false;
    bool m_progressRoundedCap = true;
    bool m_enableBg = true;
    bool m_enableText = false;
    Qt::Alignment m_progressAlignment = Qt::AlignCenter;
    QColor m_bgColor = "#44475a";
    QColor m_progressColor = "#498BD1";
    QColor m_textColor = "#498BD1";
    QString m_text = "Loading...";
};

}  // namespace widgets
}  // namespace qt
}  // namespace xaprier

#endif  // CIRCULARLOADINGINDICATOR_HPP