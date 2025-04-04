#include "Transform.h"

Transform::Transform()
{
    _position = Vector3();
    _rotation = Vector3();
    _scale = Vector3();
    _localPosition = _position;
    _localRotation = _rotation;
    _localScale = _scale;
    _hasParent = false;
    _parent = nullptr;
}

Transform::Transform(const Vector3& nposition, const Vector3& nrotation, const Vector3& nscale)
{
    _position = nposition;
    _rotation = nrotation;
    _scale = nscale;
    _localPosition = _position;
    _localRotation = _rotation;
    _localScale = _scale;
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
    _localPosition = other.localPosition;
    _localRotation = other.localRotation;
    _localScale = other.localScale;
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
    _localPosition = other.localPosition;
    _localRotation = other.localRotation;
    _localScale = other.localScale;
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
    _localPosition = _position;
    _localRotation = _rotation;
    _localScale = _scale;
    _hasParent = false;
}

void Transform::SetParent(Transform& new_parent)
{
    if (this == &new_parent)
    {
        return;
    }
    _parent = new_parent.GetPointer();
    _localPosition = _position - new_parent.position;
    _localRotation = _rotation - new_parent.rotation;
    _localScale = _scale / new_parent.scale;
    _hasParent = true;
}

void Transform::SetPosition(const double x, const double y, const double z)
{
    SetPosition(Vector3(x, y, z));
}
void Transform::SetPosition(const Vector3& nposition)
{
    _position = nposition;
    if (hasParent)
    {
        _localPosition = _position - parent->position;
    }
    else
    {
        _localPosition = _position;
    }
}
void Transform::SetLocalPosition(const double x, const double y, const double z)
{
    SetLocalPosition(Vector3(x, y, z));
}
void Transform::SetLocalPosition(const Vector3& nposition)
{
    _localPosition = nposition;
    if (hasParent)
    {
        _position = _localPosition + parent->position;
    }
    else
    {
        _position = _localPosition;
    }
}

void Transform::SetRotation(const double x, const double y, const double z)
{
    SetRotation(Vector3(x, y, z));
}
void Transform::SetRotation(const Vector3& nrotation)
{
    _rotation = nrotation;
    if (hasParent)
    {
        _localRotation = _rotation - parent->rotation;
    }
    else
    {
        _localRotation = _rotation;
    }
}
void Transform::SetLocalRotation(const double x, const double y, const double z)
{
    SetLocalRotation(Vector3(x, y, z));
}
void Transform::SetLocalRotation(const Vector3& nrotation)
{
    _localRotation = nrotation;
    if (hasParent)
    {
        _rotation = _localRotation + parent->rotation;
    }
    else
    {
        _rotation = _localRotation;
    }
}

void Transform::SetScale(const double x, const double y, const double z)
{
    SetScale(Vector3(x, y, z));
}
void Transform::SetScale(const Vector3& nscale)
{
    _scale = nscale;
    if (hasParent)
    {
        _localScale = _scale / parent->scale;
    }
    else
    {
        _localScale = _scale;
    }
}
void Transform::SetLocalScale(const double x, const double y, const double z)
{
    SetLocalScale(Vector3(x, y, z));
}
void Transform::SetLocalScale(const Vector3& nscale)
{
    _localScale = nscale;
    if (hasParent)
    {
        _scale = _localScale * parent->scale;
    }
    else
    {
        _scale = _localScale;
    }
}



Transform* Transform::GetPointer()
{
    return this;
}

