#include "stdafx.h"
#include "Model.h"
#include "Material.h"

void Model::Init(const ModelInitData& initData)
{
	MY_ASSERT(
		initData.m_fxFilePath, 
		"error : initData.m_fxFilePathが指定されていません。"
	);
	MY_ASSERT(
		initData.m_tkmFilePath,
		"error : initData.m_tkmFilePathが指定されていません。"
	);
	
	if (initData.m_skeleton != nullptr) {
		//スケルトンが指定されている。
		m_meshParts.BindSkeleton(*initData.m_skeleton);
	}
	
	m_modelUpAxis = initData.m_modelUpAxis;

	//内部のシェーダーをロードする処理が求めているのが
	//wchar_t型の文字列なので、ここで変換しておく。
	//wchar_t wfxFilePath[256] = {L""};
	//if (initData.m_fxFilePath != nullptr) {
	//	//MessageBoxA(nullptr, "fxファイルパスが指定されていません。", "エラー", MB_OK);
	//	//std::abort();
	//	mbstowcs(wfxFilePath, initData.m_fxFilePath, 256);
	//}
	
	

	//ここからTKMファイルのロードをするかすでにロードしているものを使うかの判定
	auto tkmFile = g_engine->GetTkmFileFromBank(initData.m_tkmFilePath);
	//未登録だった時
	if (tkmFile == nullptr) {
		tkmFile = new TkmFile;
		tkmFile->Load(initData.m_tkmFilePath);
		g_engine->RegistTkmFileToBank(initData.m_tkmFilePath, tkmFile);
	}

	//m_tkmFile.Load(initData.m_tkmFilePath);
	m_tkmFile = tkmFile;
	
	//ここまで/////////////////////////////////////////////////////
	

	m_meshParts.InitFromTkmFile(
		*m_tkmFile,
		initData.m_fxFilePath,
		initData.m_vsEntryPointFunc,
		initData.m_vsSkinEntryPointFunc,
		initData.m_psEntryPointFunc,
		initData.m_expandConstantBuffer,
		initData.m_expandConstantBufferSize,
		//initData.m_expandConstantBufferForLight,
		//initData.m_expandConstantBufferForLightSize,
		initData.m_expandShaderResoruceView,
		initData.cullingMode,
		initData.m_colorBufferFormat
	);

	UpdateWorldMatrix(g_vec3Zero, g_quatIdentity, g_vec3One);
	m_isInited = true;
}

void Model::UpdateWorldMatrix(Vector3 pos, Quaternion rot, Vector3 scale)
{
	Matrix mBias;
	if (m_modelUpAxis == enModelUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(Math::PI * -0.5f);
	}
	Matrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(pos);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world = mBias * mScale * mRot * mTrans;
}

void Model::ChangeAlbedoMap(const char* materialName, Texture& albedoMap)
{
	m_meshParts.QueryMeshs([&](const SMesh& mesh) {
		//todo マテリアル名をtkmファイルに出力したなかった・・・。
		//todo 今は全マテリアル差し替えます
		for (Material* material : mesh.m_materials) {
			material->GetAlbedoMap().InitFromD3DResource(albedoMap.Get());
		}
	});
	//ディスクリプタヒープの再作成。
	m_meshParts.CreateDescriptorHeaps();
	
}
void Model::Draw(RenderContext& rc)
{
	m_meshParts.Draw(
		rc, 
		m_world, 
		g_camera3D->GetViewMatrix(), 
		g_camera3D->GetProjectionMatrix()
	);
}

//影を生成するときに使用する。
void Model::Draw(RenderContext& renderContext, Camera camera)
{
	m_meshParts.Draw(
		renderContext,
		m_world,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
	);
}
