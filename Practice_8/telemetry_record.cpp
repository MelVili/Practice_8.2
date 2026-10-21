#include "telemetry_record.h"
#include <QDebug>

TelemetryPoint::TelemetryPoint()
    : time(QDateTime::currentDateTime()), altitude(0.0), battery(100.0), speed(0.0) {}

TelemetryPoint::TelemetryPoint(const QDateTime& t, double alt, double bat, double spd)
    : time(t),
    altitude(alt < 0.0 ? 0.0 : alt),
    battery(qBound(0.0, bat, 100.0)),
    speed(spd < 0.0 ? 0.0 : spd) {}

void TelemetryPoint::print() const {
    qDebug() << time.toString(Qt::ISODate)
    << "Altitude:" << altitude
    << "Battery:" << battery
    << "Speed:" << speed;
}

QDateTime TelemetryPoint::get_time() const { return time; }
double TelemetryPoint::get_altitude() const { return altitude; }
double TelemetryPoint::get_battery() const { return battery; }
double TelemetryPoint::get_speed() const { return speed; }

void TelemetryHistory::add_point(const TelemetryPoint& point) {
    points.append(point);
}

void TelemetryHistory::print_all() const {
    for (const auto& p : points) p.print();
}

int TelemetryHistory::size() const { return points.size(); }
void TelemetryHistory::clear() { points.clear(); }

const QVector<TelemetryPoint>& TelemetryHistory::get_points() const { return points; }

