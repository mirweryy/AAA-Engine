#pragma once
#include "Property.h"

Mesh::Mesh()
{
	Type = None;
}
Mesh::Mesh(std::string GType)
{
	Type = GType;
}

virtual std::string Mesh::getType() override
{
	return Type;
}