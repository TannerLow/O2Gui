#include <O2/Util/VertexHelper.h>

void o2::vh::updateQuadTexture(sf::Vertex* vertex, const sf::IntRect texCoords) {
    const sf::Vector2i& pos = texCoords.position;
    const sf::Vector2i& size = texCoords.size;
    vertex[0].texCoords = sf::Vector2f(pos.x, pos.y);
    vertex[1].texCoords = sf::Vector2f(pos.x + size.x, pos.y);
    vertex[2].texCoords = sf::Vector2f(pos.x, pos.y + size.y - 0.25f);
    vertex[3].texCoords = sf::Vector2f(pos.x, pos.y + size.y - 0.25f);
    vertex[4].texCoords = sf::Vector2f(pos.x + size.x, pos.y);
    vertex[5].texCoords = sf::Vector2f(pos.x + size.x, pos.y + size.y - 0.25f);
}

void o2::vh::positionQuad(sf::Vertex* vertex, const sf::FloatRect rect) {
    const sf::Vector2f& pos = rect.position;
    const sf::Vector2f& size = rect.size;
    vertex[0].position = sf::Vector2f(pos.x, pos.y);
    vertex[1].position = sf::Vector2f(pos.x + size.x, pos.y);
    vertex[2].position = sf::Vector2f(pos.x, pos.y + size.y);
    vertex[3].position = sf::Vector2f(pos.x, pos.y + size.y);
    vertex[4].position = sf::Vector2f(pos.x + size.x, pos.y);
    vertex[5].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
}

void o2::vh::colorQuad(sf::Vertex* vertex, const sf::Color color) {
    for (int i = 0; i < 6; i++) {
        vertex[i].color = color;
    }
}

bool o2::vh::containedByQuad(const sf::Vertex* vertex, const sf::Vector2f point) {
    return vertex[0].position.x <= point.x and point.x <= vertex[5].position.x and
        vertex[0].position.y <= point.y and point.y <= vertex[5].position.y;
}
