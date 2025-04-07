#pragma once

#include "../DataTypes/DataTypes.h"

class Transform
{
public:
    Transform();
    Transform(const Vector3& nposition, const Vector3& nrotation, const Vector3& nscale);
    ~Transform();
    Transform(const Transform& other);
    Transform& operator=(const Transform& other);

    void SetParent();
    void SetParent(Transform& new_parent);
    void SetPosition(const double x, const double y, const double z);
    void SetPosition(const Vector3& nposition);
    void SetLocalPosition(const double x, const double y, const double z);
    void SetLocalPosition(const Vector3& nposition);
    void SetRotation(const double x, const double y, const double z);
    void SetRotation(const Vector3& nrotation);
    void SetLocalRotation(const double x, const double y, const double z);
    void SetLocalRotation(const Vector3& nrotation);
    void SetScale(const double x, const double y, const double z);
    void SetScale(const Vector3& nscale);
    void SetLocalScale(const double x, const double y, const double z);
    void SetLocalScale(const Vector3& nscale);

    const Vector3& position = _position;
    const Vector3& rotation = _rotation;
    const Vector3& scale = _scale;
    const Vector3& localPosition = _localPosition;
    const Vector3& localRotation = _localRotation;
    const Vector3& localScale = _localScale;
    const bool &hasParent = _hasParent;
    Transform* const& parent = _parent;
private:
    Transform* GetPointer();

    Vector3 _position;
    Vector3 _rotation;
    Vector3 _scale;
    Vector3 _localPosition;
    Vector3 _localRotation;
    Vector3 _localScale;
    bool _hasParent = false;
    Transform* _parent;
};