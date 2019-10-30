#include "Visible.hpp"

Visible::Visible()
{
}

Visible::~Visible()
{
}

void Visible::FacingVector(tle::IModel* model, float &x, float &y, float &z)
{
	float matrix[16];

	model->GetMatrix(matrix);
	x = matrix[8];
	y = matrix[9];
	z = matrix[10];
}

bool Visible::IsVisible(tle::IModel* firstModel, tle::IModel* secondModel)
{
	float vx, vy, vz;
	FacingVector(firstModel, vx, vy, vz); // In this program we are checking for the guards facing vector
	const float wx = firstModel->GetLocalX() - secondModel->GetLocalX();
	const float wy = firstModel->GetLocalY() - secondModel->GetLocalY();
	const float wz = firstModel->GetLocalZ() - secondModel->GetLocalZ();

	return (vx * wx) + (vy * wy) + (vz * wz) > 0; // Below 0 is not visible because angle > 90
}