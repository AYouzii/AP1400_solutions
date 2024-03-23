#include "q4.h"

namespace q4 {
	Sensor::Sensor(Vector2D pos, double accuracy)
		: pos(pos), accuracy(accuracy) {}


	Vector2D kalman_filter(std::vector<Sensor> sensors)
	{
		double sumOfAccuracies = 0;
		double x = 0, y = 0;
		for (std::vector<Sensor>::const_iterator cit = sensors.cbegin(); cit != sensors.cend(); ++cit) {
			x += (*cit).pos.x * (*cit).accuracy;
			y += (*cit).pos.y * (*cit).accuracy;
			sumOfAccuracies += (*cit).accuracy;
		}
		x /= sumOfAccuracies;
		y /= sumOfAccuracies;
		return Vector2D{ x, y };
	}
}