#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

template< typename T >
struct Rectangle_generic {
    glm::vec< 2, T > position;
    glm::vec< 2, T > size;

    Rectangle_generic() { }

    Rectangle_generic(const glm::vec< 2, T >& _position, const glm::vec< 2, T >& _size) {
        position = _position;
        size = _size;
    }
    
    Rectangle_generic(T _X, T _Y, T _width, T _height) {
        position = glm::vec< 2, T >(_X, _Y);
        size = glm::vec< 2, T >(_width, _height);
    }

	static bool CheckAABB(const Rectangle_generic& lhs, const Rectangle_generic& rhs) {
		return (lhs.position.x + lhs.size.x > rhs.position.x &&
				lhs.position.x < rhs.position.x + rhs.size.x &&
				lhs.position.y + lhs.size.y > rhs.position.y &&
				lhs.position.y < rhs.position.y + rhs.size.y);
	}

	static glm::vec< 2, T > AABBDistance(const Rectangle_generic& lhs, const Rectangle_generic& rhs) {
		T dx, dy;
		if (lhs.position.x < rhs.position.x) {
			dx = rhs.position.x - (lhs.position.x + lhs.size.X);
		}
		else {
			dx = lhs.position.x - (rhs.position.x + rhs.size.x);
		}

		if (lhs.position.y < rhs.position.y) {
			dy = rhs.position.y - (lhs.position.y + lhs.size.y);
		}
		else {
			dy = lhs.position.y - (rhs.position.y + rhs.size.y);
		}

		return glm::vec< 2, T >(-dx, -dy);	// we want them to be positive
	}
};

typedef Rectangle_generic< int > Rectanglei;
typedef Rectangle_generic< float > Rectangle;
typedef Rectangle_generic< double > Rectangled;

struct Box {
	glm::vec3 position;
	glm::vec3 size;

	Box() { }

	Box(const glm::vec3& _position, const glm::vec3& _size) {
		position = _position;
		size = _size;
	}

	Box(float x, float y, float z, float width, float height, float length) {
		position = glm::vec3(x, y, z);
		size = glm::vec3(width, height, length);
	}

	static bool IsInside(const glm::vec3& point, const Box& aabb) {
		return (point.x >= aabb.position.x && point.x <= aabb.position.x + aabb.size.x &&
				point.y >= aabb.position.y && point.y <= aabb.position.y + aabb.size.y &&
				point.z >= aabb.position.z && point.z <= aabb.position.z + aabb.size.z);
	}

	static bool CheckAABB(const Box& lhs, const Box& rhs) {
		return (lhs.position.x < rhs.position.x + rhs.size.x &&
				lhs.position.x + lhs.size.x > rhs.position.x &&
				lhs.position.y < rhs.position.y + rhs.size.y &&
				lhs.position.y + lhs.size.y > rhs.position.y &&
				lhs.position.z < rhs.position.z + rhs.size.z &&
				lhs.position.z + lhs.size.z > rhs.position.z);
	}

	static glm::vec3 AABBDistance(const Box& lhs, const Box& rhs) {
		float dx, dy, dz;
		if (lhs.position.x < rhs.position.x) {
			dx = rhs.position.x - (lhs.position.x + lhs.size.x);
		}
		else {
			dx = lhs.position.x - (rhs.position.x + rhs.size.x);
		}

		if (lhs.position.y < rhs.position.y) {
			dy = rhs.position.y - (lhs.position.y + lhs.size.y);
		}
		else {
			dy = lhs.position.y - (rhs.position.y + rhs.size.y);
		}

		if (lhs.position.z < rhs.position.z) {
			dz = rhs.position.z - (lhs.position.z + lhs.size.z);
		}
		else {
			dz = lhs.position.z - (rhs.position.z + rhs.size.z);
		}

		return glm::vec3(-dx, -dy, -dz);
	}
};

#endif