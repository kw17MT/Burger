/*!
 * @brief	シャドウマップ描画用のシェーダー
 */



//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

cbuffer ShadowCb : register(b1)
{
    float4x4 LVP;
    float3 ligPos;
}


//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float3 normal	: NORMAL;		//法線。
	float2 uv 		: TEXCOORD0;	//UV座標。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float3 normal		: NORMAL;		//法線。
	float2 uv 			: TEXCOORD0;	//uv座標。
    float depth			: TEXCOORD1;
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////

Texture2D<float4> g_albedo : register(t0);		//アルベドマップ。
Texture2D<float4> g_shadowMap : register(t10);	//シャドウマップ。
sampler g_sampler : register(s0);				// サンプラステート。


/// <summary>
/// 頂点シェーダー。
/// <summary>
SPSIn VSMain(SVSIn vsIn)
{
	//シャドウマップ描画用の頂点シェーダーを実装。
	SPSIn psIn;
	psIn.pos = mul(mWorld, vsIn.pos);
    float3 worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);
	psIn.uv = vsIn.uv;
	psIn.normal = mul(mWorld, vsIn.normal);
	
    psIn.depth = length(worldPos - ligPos) / 2000.0f;
	
	return psIn;
}

static const float INFINITY = 40.0f;

/// <summary>
/// シャドウマップ描画用のピクセルシェーダー。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
    //return float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
	
	//分散シャドウマップに利用する深度値
    return float4(psIn.depth, psIn.depth * psIn.depth, 0.0f, 1.0f);
}