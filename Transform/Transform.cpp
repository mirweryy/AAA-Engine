#include "Transform.h"

Transform::Transform()
{
    _position = Vector3();
    _rotation = Vector3();
    _scale = Vector3();
    _hasParent = false;
    _parent = nullptr;
}

Transform::Transform(const Vector3& nposition, const Vector3& nrotation, const Vector3& nscale)
{
    _position = nposition;
    _rotation = nrotation;
    _scale = nscale;
    _hasParent = false;
    _parent = nullptr;
}

Transform::~Transform() {}

Transform::Transform(const Transform& other)
{
    if (this == &other)
    {
        return;
    }
    _position = other.position;
    _rotation = other.rotation;
    _scale = other.scale;
    _hasParent = other.hasParent;
    if (_hasParent)
    {
        _parent = other._parent;
    }
    else
    {
        _parent = nullptr;
    }
}

Transform& Transform::operator=(const Transform& other)
{
    if (this == &other)
    {
        return *this;
    }
    _position = other.position;
    _rotation = other.rotation;
    _scale = other.scale;
    _hasParent = other.hasParent;
    if (hasParent)
    {
        _parent = other._parent;
    }
    else
    {
        _parent = nullptr;
    }
    return *this;
}

void Transform::SetParent()
{
    _parent = nullptr;
    _hasParent = false;
}

void Transform::SetParent(Transform& new_parent)
{
    if (this == &new_parent)
    {
        return;
    }
    _parent = new_parent.GetPointer();
    _hasParent = true;
}

Transform* Transform::GetPointer()
{
    return this;
}

#include <iostream>

int main()
{
    Transform tr;
    std::cout << tr.position.x << "\n";
    return 0;
}