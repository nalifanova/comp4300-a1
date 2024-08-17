#include <iostream>
#include <math.h>
#include <utility>
#include <vector>

#include <SFML/Graphics.hpp>

/** Perhaps not the best way to use header for examples but... */

// using sf::Glsl::Vec2;
namespace  lib_ = sf::Glsl; // lib_::Vec2;

class Vec2_
{
    // Notes to implement:
    // - constructor,
    // - add        v1.add(v2)
    // - dist       d=√((x_2-x_1)²+(y_2-y_1)²)
    // - scale      (v1 * N)
    // - +          (v1 + v2)
    // - ==         (v1 == v2)
    // - chaining   v1.add(v2).scale(3).add(v1)
public:
    Vec2_() = default;
    Vec2_(const float xin, const float yin): x(xin), y(yin) {}
    ~Vec2_() = default;

    [[nodiscard]] Vec2_ operator + (const Vec2_& v)
    {
        return {x + v.x, y + v.y};
    }

    [[nodiscard]] Vec2_ operator * (const float s)
    {
        return {x * s, y * s};
    }

    [[nodiscard]] Vec2_ operator - (const Vec2_& v)
    {
        return {x - v.x, y - v.y};
    }

    bool operator == (const Vec2_& v) const
    {
        return x == v.x && y == v.y;
    }

    void operator += (const Vec2_& v)
    {
        x += v.x;
        y += v.y;
    }

    friend std::ostream&
    operator << (std::ostream& os, const Vec2_& v)
    {
        return os << v.x << ", " << v.y << "m";
    }

    [[nodiscard]] float length() const
    {
        return sqrtf((x * x) + (y * y));
    }

    /**
     * Calculates distance between a given v and a current v
     *
     *      d=√((x_2-x_1)²+(y_2-y_1)²)
     *
     * in our case it is
     *                  ,__________________________________
     *     distance = \/ (v1.x - v2.x)^2 + (v1.y - v2.y)^2
     * @param v
     * @return
     */
    [[nodiscard]] float dist(Vec2_ v) const
    {
        // options 1
        // float dx = v.x - x;
        // float dy = v.y - y;
        // return sqrtf((dx * dx) + (dy * dy));

        // option 2
        // *this == is a current object
        return (v - *this).length();
    }

    [[nodiscard]] Vec2_& add(const Vec2_ v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    [[nodiscard]] Vec2_& scale(const float s)
    {
        x *= s;
        y *= s;
        return *this;
    }

    void add_(const Vec2_ v)
    {
        x += v.x;
        y += v.y;
    }

    void scale_(const float s)
    {
        x *= s;
        y *= s;
    }

//public:
    float x = 0;
    float y = 0;

};

class CTransform_
{
public:
    CTransform_() = default;
    CTransform_(const Vec2_& p, const Vec2_& v): pos(p), velocity(v){};
    ~CTransform_() = default;

    Vec2_ pos = {0, 0};
    Vec2_ velocity = {0, 0};
};

class CName_
{
public:
    CName_() = default;
    explicit CName_(std::string  n): name(std::move(n)) {};
    ~CName_() = default;

    std::string name = "Name";
};

class ShapeEntity_
{
public:
    ShapeEntity_() = default;
    ~ShapeEntity_() = default;

    void setPosition(Vec2_ pos);
};

class CShape_
{
public:
    CShape_() = default;
    CShape_(ShapeEntity_& s): shape(s) {};
    ~CShape_() = default;

    ShapeEntity_ shape;
};

class CBBox_
{

};

class Entity_
{
public:
    Entity_() = default;
    Entity_(std::string tag, const size_t id)
    : m_tag(std::move(tag)), m_id(id) {}
    ~Entity_() = default;

    // void addComponent<T>(args);
    // void getComponent<T>(args);

// public:
    std::shared_ptr<CTransform_> cTransform;
    std::shared_ptr<CName_> cName;
    std::shared_ptr<CShape_> cShape;
    std::shared_ptr<CBBox_> cBBox;
private:
    // std::vector<Component> m_components;
    const size_t m_id = 0;
    const std::string m_tag = "Default";
    bool m_alive = true;
};

// void do_stuff(std::vector<Entity_>& entities)
// {
//     for (auto& e: entities)
//     {
//         e.cTransform->pos += e.cTransform->velocity;
//         e.cShape->shape.setPosition(e.cTransform->pos);
//         // window.draw(e.cShape->shape);
//     }
// }
//

void sMovement(const std::vector<Entity_>& entities)
{
    for (auto& e: entities)
    {
        e.cTransform->pos += e.cTransform->velocity;
    }
}

// void sRender(std::vector<Entity_>& entities)
// {
//     for (auto& e: entities)
//     {
//         if (e.cShape && e.cTransform)
//         {
//             e.cShape->shape.setPosition(e.cTransform->pos);
//             // window.draw(e.cShape->shape);
//         }
//     }
// }

void declaring_entity()
{
    std::vector<Entity_> entities;
    Vec2_ p(100, 200), v(10, 10);
    Entity_ e;

    e.cTransform = std::make_shared<CTransform_>(p, v);
    e.cName = std::make_shared<CName_>("Red Box");
    // e.cShape = std::make_shared<CShape_>(args);

    entities.push_back(e);
    // do_stuff(entities);
}

void checking_for_component()
{
    Entity_ e;
    e.cName = std::make_shared<CName_>("Red Box");
    // component stored as shared_ptr, false if not present

    if (e.cTransform) // will be false
        std::cout << "Nothing happens\n";

    if (e.cName) // will be true, coz it is "Red Box"
        std::cout << "We can show a name\n";

    if (e.cTransform && e.cShape) // need to render
        std::cout << "We may render if we have these data\n";

}

void example_of_vec2_usage()
{
    Vec2_ v1(100, 100);
    Vec2_ v2(150, 70);
    // v2.add(v1); // v2 parameters are gonna be changed

    Vec2_ v3 = (v1 + v2) * 2;

    std::cout << "Data: v3(";
    std::cout << v3.x << ", " << v3.y << "), v2(";
    std::cout << v2.x << ", " << v2.y << "), v1(";
    std::cout << v1.x << ", " << v1.y << ")\n";
    std::cout << "---------\n";

    float dist = v1.dist(v2);
    std::cout << "The distance between v1 and v2 is: " << dist << "\n";

    float length = v1.length();
    std::cout << "The length of v1 is: " << length << "\n";
}

void example_of_vec2_usage2()
{
    Vec2_ v1(100, 100);
    Vec2_ v2(150, 70);

    std::cout << "Data: v2(" << v2 << "), v1(" << v1 << ")\n";
    std::cout << "---------\n";

    // v1.add(v2);
    // v1.scale(7);
    // v1.add(v2);
    // v1.add(v2).scale(2).add(v2); // chaining

    std::cout << "v1 add v2, scale 2, add v2 = (" << v1 << ")\n";

    std::cout << "v1 == v2? " << (v1 == v2) << "\n";
}
