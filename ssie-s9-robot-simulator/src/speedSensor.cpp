#include "speedSensor.hpp"

#include <cmath>
#include <numbers>
#include <iostream>


SpeedSensor::SpeedSensor(const sf::Vector2f & position, float wheelDiameter,
        std::size_t latticeCount)
    : _position(position)
    , _latticeStep(wheelDiameter*std::numbers::pi/latticeCount)
    , _lastGlobalPosition()
    , _distance(0.0)
    , _value(0u)
{
}

void SpeedSensor::update(float, const sf::Transform & parentWorldTransform)
{
    auto newPosition = parentWorldTransform.transformPoint(_position);
    // TODO Step1 Replace the stub below to compute _distance and _value from
    // _lastGlobalPosition, newPosition and _latticeStep
    // Begin stub

    sf::Vector2f direction = sf::Vector2f(cos(getRotation() * M_PI / 180), sin(getRotation() * M_PI / 180));
    sf::Vector2f position2 = _lastGlobalPosition + direction * _latticeStep;

    _distance = 0;
    while (_distance < _latticeStep && _map.getPixel(position2.x, position2.y) < 255)
    {
        _distance += 1;
        position2 += direction;
    }

    _value = _distance > _latticeStep / 2 ? 255 : 0;

    // End stub
}
