#ifndef TELEMETRY_RECORD_H
#define TELEMETRY_RECORD_H

#include <QDateTime>
#include <QVector>


class TelemetryPoint {
private:
    QDateTime time;
    double altitude;
    double battery;
    double speed;

public:
    TelemetryPoint();
    TelemetryPoint(const QDateTime& t, double alt, double bat, double spd);

    void print() const;

    QDateTime get_time() const;
    double get_altitude() const;
    double get_battery() const;
    double get_speed() const;
};


class TelemetryHistory {
private:
    QVector<TelemetryPoint> points;

public:
    void add_point(const TelemetryPoint& point);
    void print_all() const;
    int size() const;
    void clear();

    const QVector<TelemetryPoint>& get_points() const;


};

#endif // TELEMETRY_RECORD_H