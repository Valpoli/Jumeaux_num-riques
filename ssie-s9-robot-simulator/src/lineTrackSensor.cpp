#include "lineTrackSensor.hpp"

#include "map.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


LineTrackSensor::LineTrackSensor(const sf::Vector2f & position, const Map & map,
        std::uint8_t threshold)
    : _map(map)
    , _shape(std::make_unique<sf::RectangleShape>(sf::Vector2f(DISPLAY_SIZE, DISPLAY_SIZE)))
    , _threshold(threshold)
    , _value(0)
{
    _shape->setOrigin(DISPLAY_SIZE/2.0, DISPLAY_SIZE/2.0);
    setPosition(position);
}

void LineTrackSensor::update(float, const sf::Transform & parentWorldTransform)
{
    auto worldTranform = parentWorldTransform * getTransform();
    _shape->setPosition(worldTranform.transformPoint(sf::Vector2f(0.0, 0.0)));
    //Replace the stub below to compute _value from _map and _shape->getPosition()
    // Begin stub

    sf::Vector2f position = _shape->getPosition();
    sf::Vector2f direction = sf::Vector2f(cos(_shape->getRotation() * M_PI / 180), sin(_shape->getRotation() * M_PI / 180));
    sf::Vector2f position2 = position + direction * DISPLAY_SIZE;

    _value = _map.getPixel(position.x, position.y) > _threshold ? 255 : 0;
    _value += _map.getPixel(position2.x, position2.y) > _threshold ? 255 : 0;
    _value /= 2;

    // End stub
}

void LineTrackSensor::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    _shape->setFillColor(sf::Color(_value, _value, _value));
    states.transform = sf::Transform::Identity;
    target.draw(*_shape, states);
}
