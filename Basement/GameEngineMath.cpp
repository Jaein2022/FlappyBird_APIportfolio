#include "PreCompile.h"
#include "GameEngineMath.h"

const float GameEngineMath::PI = 3.14159265359f;
const float GameEngineMath::TAU = PI * 2.0f;
const float GameEngineMath::DegreeToRadian = GameEngineMath::PI / 180.0f;	//60분법->호도법(0.017453...)
const float GameEngineMath::RadianToDegree = 180.0f / GameEngineMath::PI;	//호도법->60분법(57.29577...)

const float4 float4::ZERO = { 0, 0, 0, 0 };
const float4 float4::ONE = { 1, 1, 1, 1 };

const float4 float4::LEFT = { -1.0f, 0.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f };
const float4 float4::UP = { 0.0f, 1.0f };
const float4 float4::DOWN = { 0.0f, -1.0f };

const float4 float4::RED = { 1, 0, 0, 1 };
const float4 float4::GREEN = { 0, 1, 0, 1 };
const float4 float4::BLUE = { 0, 0, 1, 1 };
const float4 float4::BLACK = { 0, 0, 0, 1 };
const float4 float4::WHITE = { 1, 1, 1, 1 };
const float4 float4::NONE = { 0, 0, 0, 0 };