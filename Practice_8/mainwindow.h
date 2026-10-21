#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QColor>
#include "telemetry_record.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TelemetryGraphWidget : public QWidget {
    Q_OBJECT
public:
    enum DataType { Altitude, Speed, Battery };

    TelemetryGraphWidget(const QString& title, const QString& unit,
                         const QColor& color, DataType type,
                         QWidget *parent = nullptr);

    void setHistory(const TelemetryHistory* history);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double valueOf(const TelemetryPoint& pt) const;
    QPointF pointAt(int i, int n, double v, const QRectF& plot,
                    double minV, double maxV) const;

    QString m_title, m_unit;
    QColor  m_color;
    DataType m_type;
    const TelemetryHistory* m_history;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTelemetryTick();
    void onStartStopClicked();
    void onClearClicked();

private:
    void updateDashboard();

    Ui::MainWindow *ui;
    TelemetryHistory history;
    QTimer *timer;

    TelemetryGraphWidget *altitudeChart;
    TelemetryGraphWidget *speedChart;
    TelemetryGraphWidget *batteryChart;

    double phase = 0.0;
    double currentAltitude = 120.0;
    double currentSpeed    = 16.0;
    double currentBattery  = 98.0;
};

#endif // MAINWINDOW_H