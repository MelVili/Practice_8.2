#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <cmath>
#include <algorithm>



TelemetryGraphWidget::TelemetryGraphWidget(const QString& title, const QString& unit,
                                           const QColor& color, DataType type,
                                           QWidget *parent)
    : QWidget(parent), m_title(title), m_unit(unit),
    m_color(color), m_type(type), m_history(nullptr)
{
    setMinimumHeight(180);
}

void TelemetryGraphWidget::setHistory(const TelemetryHistory* h) {
    m_history = h;
    update();
}

double TelemetryGraphWidget::valueOf(const TelemetryPoint& pt) const {
    if (m_type == Altitude) return pt.get_altitude();
    if (m_type == Speed)    return pt.get_speed();
    return pt.get_battery();
}

QPointF TelemetryGraphWidget::pointAt(int i, int n, double v,
                                      const QRectF& plot,
                                      double minV, double maxV) const
{
    double x = plot.left() + plot.width() * i / std::max(1, n - 1);
    double r = (v - minV) / (maxV - minV);
    r = std::clamp(r, 0.0, 1.0);
    double y = plot.bottom() - r * plot.height();
    return QPointF(x, y);
}

void TelemetryGraphWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);


    p.setPen(QColor("#30363d"));
    p.setBrush(QColor("#161b22"));
    p.drawRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8);


    QRectF plot(58, 38, width() - 78, height() - 64);
    if (plot.width() < 10 || plot.height() < 10) return;


    p.setFont(QFont("Segoe UI", 10, QFont::Bold));
    p.setPen(QColor("#e6edf3"));
    p.drawText(QPointF(plot.left(), 24), m_title);

    if (!m_history || m_history->size() < 2) return;


    const auto& all = m_history->get_points();
    int start = std::max(0, static_cast<int>(all.size()) - 60);
    int n = all.size() - start;


    double minV = 0.0;
    double maxV = (m_type == Battery) ? 100.0 : 10.0;
    if (m_type != Battery) {
        for (int i = start; i < all.size(); ++i)
            maxV = std::max(maxV, valueOf(all[i]));
        maxV = std::ceil(maxV * 1.15 / 10.0) * 10.0;
    }


    p.setFont(QFont("Consolas", 11, QFont::Bold));
    p.setPen(m_color);
    p.drawText(QRectF(plot.right() - 150, 8, 150, 24),
               Qt::AlignRight | Qt::AlignVCenter,
               QString("%1 %2").arg(valueOf(all.last()), 0, 'f', 1).arg(m_unit));

    p.setPen(QPen(m_color, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QPointF prev = pointAt(0, n, valueOf(all[start]), plot, minV, maxV);
    for (int i = 1; i < n; ++i) {
        QPointF cur = pointAt(i, n, valueOf(all[start + i]), plot, minV, maxV);
        p.drawLine(prev, cur);
        prev = cur;
    }


    p.setFont(QFont("Consolas", 8));
    p.setPen(QColor("#8b949e"));
    p.drawText(QPointF(plot.left(), height() - 7),
               all[start].get_time().toString("HH:mm:ss"));
    p.drawText(QRectF(plot.right() - 70, height() - 19, 70, 15),
               Qt::AlignRight,
               all.last().get_time().toString("HH:mm:ss"));
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    altitudeChart = new TelemetryGraphWidget("ВЫСОТА",   "м",   QColor("#00e5ff"), TelemetryGraphWidget::Altitude, this);
    speedChart    = new TelemetryGraphWidget("СКОРОСТЬ", "м/с", QColor("#ff9100"), TelemetryGraphWidget::Speed,    this);
    batteryChart  = new TelemetryGraphWidget("БАТАРЕЯ",  "%",   QColor("#00e676"), TelemetryGraphWidget::Battery,  this);

    ui->chartsLayout->addWidget(altitudeChart);
    ui->chartsLayout->addWidget(speedChart);
    ui->chartsLayout->addWidget(batteryChart);

    altitudeChart->setHistory(&history);
    speedChart->setHistory(&history);
    batteryChart->setHistory(&history);

    timer = new QTimer(this);
    timer->setInterval(250);
    connect(timer, &QTimer::timeout, this, &MainWindow::onTelemetryTick);
    connect(ui->btnStartStop, &QPushButton::clicked, this, &MainWindow::onStartStopClicked);
    connect(ui->btnClear,     &QPushButton::clicked, this, &MainWindow::onClearClicked);

    timer->start();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onTelemetryTick() {
    phase += 0.2;

    currentAltitude = 120.0 + std::sin(phase * 0.6) * 35.0;
    currentSpeed    = 16.0  + std::cos(phase * 0.9) * 6.0;
    currentBattery -= 0.15;
    if (currentBattery <= 0.0) currentBattery = 100.0;

    history.add_point(TelemetryPoint(QDateTime::currentDateTime(),
                                     currentAltitude, currentBattery, currentSpeed));
    updateDashboard();
}

void MainWindow::updateDashboard() {
    altitudeChart->update();
    speedChart->update();
    batteryChart->update();

    if (history.size() == 0) {
        ui->lblStats->setText("История пуста.\nЗаписей: 0");
        return;
    }

    const TelemetryPoint& last = history.get_points().last();

    ui->lblStats->setText(QString(
                              "БПЛА:       BPLA-01\n"
                              "Время:      %1\n"
                              "-------------------------\n"
                              "Высота:     %2 м\n"
                              "Скорость:   %4 м/с\n"
                              "Батарея:    %5 %\n"
                              "-------------------------\n"
                              "Записей:    %6"
                              ).arg(last.get_time().toString("HH:mm:ss"))
                              .arg(last.get_altitude(), 0, 'f', 1)
                              .arg(last.get_speed(), 0, 'f', 1)
                              .arg(last.get_battery(), 0, 'f', 1)
                              .arg(history.size()));
}

void MainWindow::onStartStopClicked() {
    if (timer->isActive()) {
        timer->stop();
        ui->btnStartStop->setText("Возобновить приём");
    } else {
        timer->start();
        ui->btnStartStop->setText("Пауза телеметрии");
    }
}

void MainWindow::onClearClicked() {
    history.clear();
    currentBattery = 100.0;
    updateDashboard();
}