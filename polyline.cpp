#include <cmath>
#include "polyline.h"

void Polyline::mallen(QPainter* objkt, bool deko_){
    objkt->setPen(QPen(color,2,Qt::SolidLine));
    objkt->drawPolyline(punkten);
}

bool Polyline::isNaehe(QPointF punkt){
    // Define a tolerance (this might need to be adjusted based on your specific use case)
    const double tolerance = 1.0;

    for (double i = 0; i < punkten.size() - 1; i++) {
        // Calculate the distances from the point to the endpoints of the line segment
        double d1 = std::hypot(punkt.x() - punkten[i].x(), punkt.y() - punkten[i].y());
        double d2 = std::hypot(punkt.x() - punkten[i+1].x(), punkt.y() - punkten[i+1].y());

        // Calculate the length of the line segment
        double lineLength = std::hypot(punkten[i].x() - punkten[i+1].x(), punkten[i].y() - punkten[i+1].y());

        // The point is on (or very close to) the line if the sum of d1 and d2 is equal to the line length within the tolerance
        if (std::abs(d1 + d2 - lineLength) < tolerance) {
            return true;
        }
    }
    return false;
}
