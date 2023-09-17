#pragma once
#include "IExecute.h"

class CollisionDemo : public IExecute
{
	struct Input
	{
		float value;
	};

	struct Output
	{
		uint32 groupID[3];
		uint32 groupThreadID[3];
		uint32 dispatchThreadID[3];
		uint32 groupIndex;
		float value;
	};

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Shader> _shader;

};

#include "MonoBehaviour.h"

class MoveScript : public MonoBehaviour
{
public: 
	virtual void Update() override;
};
