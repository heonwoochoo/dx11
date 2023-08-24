#include "pch.h"
#include "Transform.h"

Transform::Transform()
	:Super(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{
}

void Transform::Update()
{
}

// Quaternion을 Euler 각도로 변환하는 함수
Vec3 QuaternionToEulerAngles(const Quaternion& quaternion) {
	float sqw = quaternion.w * quaternion.w;
	float sqx = quaternion.x * quaternion.x;
	float sqy = quaternion.y * quaternion.y;
	float sqz = quaternion.z * quaternion.z;

	float pitch = std::asin(2.0f * (quaternion.w * quaternion.x - quaternion.y * quaternion.z));
	float yaw = std::atan2(2.0f * (quaternion.x * quaternion.z + quaternion.w * quaternion.y), 1.0f - 2.0f * (sqx + sqy));
	float roll = std::atan2(2.0f * (quaternion.x * quaternion.y + quaternion.w * quaternion.z), 1.0f - 2.0f * (sqy + sqz));

	return Vec3(pitch, yaw, roll);
}

void Transform::UpdateTransform()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;

	if (HasParent())
	{
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		// 부모가 없을 때는 로컬이 월드가 됨
		_matWorld = _matLocal;
	}

	Quaternion quat;
	_matWorld.Decompose(_scale, quat, _position);
	_rotation = QuaternionToEulerAngles(quat);

	// (1,0,0) * MatWorld

	/*
	* TransformCoord vs TransformNormal
	* Coord는 위치도 고려, Normal은 방향만 고려 (position 영향을 받지 않음)
	* Vec4의 4번째 인자로 1이 들어가냐, 0이 들어가냐의 차이다
	* ex) _right = Vec3::TransformNormal(Vec3::Right, _matWorld);
	*/

	// 부모가 변했기에 자식들도 업데이트
	for (const shared_ptr<Transform>& child : _children)
		child->UpdateTransform();
}

void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
		SetLocalScale(scale);
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const Vec3& worldRotation)
{
	if (HasParent())
	{
		Matrix inverseMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 rotation;
		rotation.TransformNormal(worldRotation, inverseMatrix);

		SetLocalRotation(rotation);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent())
	{
		// 월드에서 부모로가는 행렬
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		// 부모를 기준으로한 로컬 좌표
		Vec3 position;
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}
}
