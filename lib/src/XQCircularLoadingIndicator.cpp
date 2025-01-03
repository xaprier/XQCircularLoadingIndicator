#include "XQCircularLoadingIndicator.hpp"

namespace xaprier {
namespace qt {
namespace widgets {
XQCircularLoadingIndicator::XQCircularLoadingIndicator(QWidget *parent) : QWidget(parent), m_superClass(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(m_width, m_height);
    updateGeometry();
}

XQCircularLoadingIndicator::~XQCircularLoadingIndicator() { this->Stop(); }

void XQCircularLoadingIndicator::SetMaximumSpeed(const double &maximumSpeed) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change maximum speed while running. Please stop the "
            "indicator before changing the maximum speed.");
        return;
    }

    if (maximumSpeed < m_minSpeed) {
        qDebug() << QObject::tr(
            "Maximum speed cannot be less than minimum speed. Please "
            "provide a value greater than or equal to the minimum speed.");
        return;
    }

    if (m_maxSpeed != maximumSpeed) {
        m_maxSpeed = maximumSpeed;
        emit si_MaximumSpeedChanged(maximumSpeed);
    }
}

void XQCircularLoadingIndicator::SetMinimumSpeed(const double &minimumSpeed) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change minimum speed while running. Please stop the "
            "indicator before changing the minimum speed.");
        return;
    }

    if (minimumSpeed > m_maxSpeed) {
        qDebug() << QObject::tr(
            "Minimum speed cannot be greater than maximum speed. Please "
            "provide a value less than or equal to the maximum speed.");
        return;
    }

    if (m_minSpeed != minimumSpeed) {
        m_minSpeed = minimumSpeed;
        emit si_MinimumSpeedChanged(minimumSpeed);
    }
}

void XQCircularLoadingIndicator::SetSegmentSize(const int &segmentSize) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change segment size while running. Please stop the "
            "indicator before changing the segment size.");
        return;
    }
    this->m_segmentSize = segmentSize % m_circularDegree;
    emit si_SegmentChanged(segmentSize % m_circularDegree);
    update();
    repaint();
}

void XQCircularLoadingIndicator::SetWidth(const int &width) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change width while running. Please stop the "
            "indicator before changing the width.");
        return;
    }

    if (m_width != width) {
        m_width = width;
        emit si_WidthChanged(width);
        QResizeEvent event(this->size(), this->size());
        this->resizeEvent(&event);
        repaint();
    }
}

void XQCircularLoadingIndicator::SetHeight(const int &height) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change height while running. Please stop the "
            "indicator before changing the height.");
        return;
    }

    if (m_height != height) {
        m_height = height;
        emit si_HeightChanged(height);
        QResizeEvent event(this->size(), this->size());
        this->resizeEvent(&event);
        repaint();
    }
}

void XQCircularLoadingIndicator::SetMargin(const int &x, const int &y) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change margin while running. Please stop the "
            "indicator before changing the margin.");
        return;
    }

    if (m_marginX != x || m_marginY != y) {
        m_marginX = x;
        m_marginY = y;
        emit si_MarginChanged(x, y);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetMarginX(const int &x) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change margin while running. Please stop the "
            "indicator before changing the margin.");
        return;
    }

    if (m_marginX != x) {
        m_marginX = x;
        emit si_MarginXChanged(x);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetMarginY(const int &y) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change margin while running. Please stop the "
            "indicator before changing the margin.");
        return;
    }

    if (m_marginY != y) {
        m_marginY = y;
        emit si_MarginYChanged(y);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetProgressWidth(const int &width) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change progress width while running. Please stop the "
            "indicator before changing the progress width.");
        return;
    }

    if (m_progressWidth != width) {
        m_progressWidth = width;
        emit si_ProgressWidthChanged(width);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetSquare(const bool &enable) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change square while running. Please stop the "
            "indicator before changing the square.");
        return;
    }

    if (m_square != enable) {
        m_square = enable;
        emit si_SquareChanged(enable);
        QResizeEvent event(this->size(), this->size());
        this->resizeEvent(&event);
        repaint();
    }
}

void XQCircularLoadingIndicator::SetShadow(const bool &enable) {
    // todo: maybe this control will not be needed
    // if (m_running) {
    //   qDebug() << QObject::tr(
    //       "Cannot change shadow while running. Please stop the "
    //       "indicator before changing the shadow.");
    //   return;
    // }

    if (m_shadow != enable) {
        if (enable) {
            auto *shadow = new QGraphicsDropShadowEffect();
            shadow->setBlurRadius(15);
            shadow->setXOffset(0);
            shadow->setYOffset(0);
            shadow->setColor(QColor(0, 0, 0, 80));
            setGraphicsEffect(shadow);
        } else {
            setGraphicsEffect(nullptr);
        }
        m_shadow = enable;
        emit si_ShadowChanged(enable);
        update();
    }
}

void XQCircularLoadingIndicator::SetProgressRoundedCap(const bool &enable) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change progress rounded cap while running. Please stop the "
            "indicator before changing the progress rounded cap.");
        return;
    }

    if (m_progressRoundedCap != enable) {
        m_progressRoundedCap = enable;
        emit si_ProgressRoundedCapChanged(enable);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetEnableBg(const bool &enable) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change enable background while running. Please stop the "
            "indicator before changing the enable background.");
        return;
    }

    if (m_enableBg != enable) {
        m_enableBg = enable;
        emit si_EnableBgChanged(enable);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetEnableText(const bool &enable) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change enable text while running. Please stop the "
            "indicator before changing the enable background.");
        return;
    }

    if (m_enableText != enable) {
        m_enableText = enable;
        emit si_EnableBgChanged(enable);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetProgressAlignment(const Qt::Alignment &alignment) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change progress alignment while running. Please stop the "
            "indicator before changing the progress alignment.");
        return;
    }

    if (m_progressAlignment != alignment) {
        m_progressAlignment = alignment;
        emit si_ProgressAlignmentChanged(alignment);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetBgColor(const QColor &color) {
    if (m_running && !m_enableBg) {
        qDebug() << QObject::tr(
            "Cannot change background color while running. Please stop the "
            "indicator before changing the background color.");
        return;
    }

    if (m_bgColor != color) {
        m_bgColor = color;
        emit si_BgColorChanged(color);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetProgressColor(const QColor &color) {
    if (m_running) {
        qDebug() << QObject::tr(
            "Cannot change progress color while running. Please stop the "
            "indicator before changing the progress color.");
        return;
    }

    if (m_progressColor != color) {
        m_progressColor = color;
        emit si_ProgressColorChanged(color);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetTextColor(const QColor &color) {
    if (m_running && !m_enableText) {
        qDebug() << QObject::tr(
            "Cannot change text color while running. Please stop the "
            "indicator before changing the progress color.");
        return;
    }

    if (m_textColor != color) {
        m_textColor = color;
        emit si_ProgressColorChanged(color);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::SetText(const QString &text) {
    if (m_running && !m_enableText) {
        qDebug() << QObject::tr(
            "Cannot change text while running. Please stop the "
            "indicator before changing the text.");
        return;
    }

    if (m_text != text) {
        m_text = text;
        emit si_TextChanged(text);
        update();
        repaint();
    }
}

void XQCircularLoadingIndicator::Start() {
    if (this->m_running) {
        qDebug() << QObject::tr("Indicator is already running.");
        return;
    }

    this->m_running = true;

    // Launch a background thread using QtConcurrent
    this->m_future = QtConcurrent::run([this]() {
        while (m_running) {
            this->_Progress();  // Update progress
            QThread::msleep(10);
        }
    });
}

void XQCircularLoadingIndicator::Stop() {
    m_running = false;

    // Wait for the thread to finish
    if (m_future.isRunning()) {
        m_future.waitForFinished();
    }
}

void XQCircularLoadingIndicator::_Progress() {
    double angle = fmod(m_currentValue + 270, m_circularDegree);

    // calculate speed factor with normalized sin values
    double normalizedAngle = angle * M_PI / 180.0;                               // degree to radian
    double speedFactor = (std::sin(normalizedAngle) + 1.0) / 2.0;                // normalized factor
    double dynamicSpeed = m_minSpeed + speedFactor * (m_maxSpeed - m_minSpeed);  // [min, max]

    // Update progress value
    m_currentValue += dynamicSpeed;

    // Schedule UI update on the main thread
    QMetaObject::invokeMethod(
        this, [this]() { repaint(); }, Qt::QueuedConnection);
}

void XQCircularLoadingIndicator::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    auto pnwidth = m_width - m_progressWidth;
    auto pnheight = m_height - m_progressWidth;
    auto margin = m_progressWidth / 2;
    auto pnend = fmod(m_currentValue + 270, m_circularDegree);
    auto x = this->m_marginX + margin;
    auto y = this->m_marginY + margin;

    painter.setRenderHint(QPainter::Antialiasing);

    // create rect
    auto rect = QRect(std::abs(m_marginX - margin), std::abs(m_marginY - margin), m_width, m_height);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect);

    // pen
    auto pen = QPen();
    pen.setWidth(this->m_progressWidth);
    pen.setColor(this->m_progressColor);

    // bg pen
    auto penny = QPen();
    penny.setWidth(this->m_progressWidth);
    penny.setColor(this->m_bgColor);

    // text pen
    auto textPen = QPen();
    textPen.setColor(this->m_textColor);

    // set round cap
    if (this->m_progressRoundedCap) {
        pen.setCapStyle(Qt::RoundCap);
        penny.setCapStyle(Qt::RoundCap);
    }

    if (this->m_enableBg) {
        painter.setPen(penny);
        painter.drawArc(x, y, pnwidth, pnheight, -m_circularDegree * 16, m_circularDegree * 16);
    }

    if (this->m_enableText) {
        painter.setPen(textPen);
        painter.drawText(rect, Qt::AlignCenter, this->m_text);
    }

    // create arc/circular progress
    painter.setPen(pen);
    painter.drawArc(x, y, pnwidth, pnheight, -pnend * 16, m_segmentSize * 16);

    // end
    painter.end();
}

void XQCircularLoadingIndicator::resizeEvent(QResizeEvent *event) {
    QSize size;
    if (event->size().width() > m_width + m_marginX * 2)  // expand
        size.setWidth(qMax(event->size().width(), m_width + m_marginX * 2));
    else  // shrink
        size.setWidth(qMin(event->size().width(), m_width + m_marginX * 2));

    if (event->size().height() > m_height + m_marginY * 2)  // expand
        size.setHeight(qMax(event->size().height(), m_height + m_marginY * 2));
    else  // shrink
        size.setHeight(qMin(event->size().height(), m_height + m_marginY * 2));

    if (m_square) {
        this->m_width = qMin(size.width(), size.height());
        this->m_height = qMin(size.width(), size.height());
        if (m_progressAlignment & Qt::AlignCenter) {
            this->m_marginX = (size.width() - this->m_width) / 2;
            this->m_marginY = (size.height() - this->m_height) / 2;
        } else {
            if (m_progressAlignment & Qt::AlignHCenter) {
                this->m_marginX = (size.width() - this->m_width) / 2;
            } else if (m_progressAlignment & Qt::AlignRight) {
                this->m_marginX = (size.width() - this->m_width);
            } else if (m_progressAlignment & Qt::AlignLeft) {
                this->m_marginX = 0;
            }

            if (m_progressAlignment & Qt::AlignVCenter) {
                this->m_marginY = (size.height() - this->m_height) / 2;
            } else if (m_progressAlignment & Qt::AlignBottom) {
                this->m_marginY = (size.height() - this->m_height);
            } else if (m_progressAlignment & Qt::AlignTop) {
                this->m_marginY = 0;
            }
        }
    } else {
        this->m_width = size.width();
        this->m_height = size.height();
        this->m_marginX = 0;
        this->m_marginY = 0;
    }

    update();
}

}  // namespace widgets
}  // namespace qt
}  // namespace xaprier