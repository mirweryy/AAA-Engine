#pragma once

#include "../DataTypes/DataTypes.h"

class Transform
{
public:
    Transform();
    Transform(const Vector3& _position, const Vector3& _rotation, const Vector3& _scale);
    ~Transform();
    Transform(const Transform& other);
    Transform& operator=(const Transform& other);

    void SetParent();
    void SetParent(Transform& new_parent);

    const Vector3& position = _position;
    const Vector3& rotation = _rotation;
    const Vector3& scale = _scale;
    const bool &hasParent = _hasParent;
    const Transform* parent = _parent;
private:
    Transform* GetPointer();

    Vector3 _position;
    Vector3 _rotation;
    Vector3 _scale;
    bool _hasParent = false;
    Transform* _parent;
};