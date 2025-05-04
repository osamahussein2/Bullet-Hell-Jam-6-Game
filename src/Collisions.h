#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <glm.hpp>
#include <vector>
#include <functional>

struct CircleCollision;
//struct LaserCollision;

struct Collision{
    virtual ~Collision() = default;

    virtual bool collidesWith(Collision& other) = 0;

    virtual bool collideWithCircle(CircleCollision& circle) = 0;
    //virtual bool collideWithLaser(Collision& laser) = 0;

    virtual void UpdatePosition(glm::vec2 host_pos) = 0;
};

struct CircleCollision : public Collision {
    float radius;
    glm::vec2 rel_center;
    glm::vec2 center;

    CircleCollision(float radius_, glm::vec2 rel_center_) : radius(radius_), rel_center(rel_center_) {}

    virtual bool collidesWith(Collision& other) override {
        return other.collideWithCircle(*this);
    };

    virtual bool collideWithCircle(CircleCollision& circle) override {
        float dx = center.x - circle.center.x;
        float dy = center.y - circle.center.y;
        float dist2 = dx*dx + dy*dy;
        float rsum = radius + circle.radius;
        // checking squared distance for performance
        return dist2 <= rsum * rsum;
    };

    virtual void UpdatePosition(glm::vec2 host_pos) {
        center = host_pos + rel_center;
    }
};

struct Body {

    ~Body() {
        for (Collision* collision : collisions) {
            delete collision;
        }
    }

    glm::vec2 body_position;

    std::vector<Collision*> collisions;
    virtual void OnCollide(Body* other) = 0;

    void UpdatePositions() {
        for (Collision* collision : collisions) {
            collision->UpdatePosition(body_position);
        }
    }

    bool CollideWith(Body* other) {
        for (Collision* collision : collisions) {
            for (Collision* other_collision : other->collisions) {
                if (collision->collidesWith(*other_collision)) {
                    OnCollide(other);
                    other->OnCollide(this);
                    return true;
                }
            }
        } 
        return false;
    }
};

#endif