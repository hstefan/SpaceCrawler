#include "Ship.hpp"

#include "SpriteBuffer.hpp"
#include "GameState.hpp"
#include "debug_sprite.hpp"

void Ship::draw(SpriteBuffer& sprite_buffer) const {
	Sprite ship_spr;
	ship_spr.setImg(0, 0, 32, 24);
	ship_spr.setPos(pos_x.integer(), pos_y.integer());

	SpriteMatrix matrix;
	matrix.loadIdentity().rotate(angle);

	sprite_buffer.append(ship_spr, matrix);
}

void Ship::update(InputButtons::Bitset& input) {
	static const float TURNING_SPEED = radiansFromDegrees(5.0f);

	if (input.test(InputButtons::LEFT)) {
		angle -= TURNING_SPEED;
	}

	if (input.test(InputButtons::RIGHT)) {
		angle += TURNING_SPEED;
	}

	if (input.test(InputButtons::THRUST)) {
		vec2 accel = 4.0f * complex_from_angle(angle);
		pos_x += PositionFixed(accel.x);
		pos_y += PositionFixed(accel.y);
	}
}
