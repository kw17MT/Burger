#pragma once
#include "math.h"
#include "stdafx.h"

struct DirectionalLight
{
	Vector3 direction = { 0.0f,1.0f,0.0f };
	float pad0;
	Vector3 color = {10.0f, 10.0f, 10.0f };
};

struct Light
{
	//���K�����邱��
	/*Vector3 DirDirection = { 0.0f,-1.0f,0.0f };
	float pad;
	Vector3 DirColor = { 0.5f,0.5f,0.5f };
	float pad2;*/
	DirectionalLight directionalLight;
	float pad1;
	Vector3 eyePos;
	float specPow = 0.5f;
	Vector3 ambientLight = { 0.6f, 0.6f, 0.6f };

	/////////////////////////////////////////////////////////////////////////////////////////////////
	////Point
	//Vector3 ptPosition = { 0.0f, 300.0f,0.0f };
	//float pad3;
	//Vector3 ptColor = { 100.0f, 50.0f,100.0f };
	//float ptRange = 300.0f;
	////Spot
	////���K�����邱�ƁB
	//Vector3 spDirection = { 1.0f,-1.0f,0.0f };
	//float spAngle = Math::DegToRad(30.0f);
	/////////////////////////////////////////////////////////////////////////////////////////////////
};


