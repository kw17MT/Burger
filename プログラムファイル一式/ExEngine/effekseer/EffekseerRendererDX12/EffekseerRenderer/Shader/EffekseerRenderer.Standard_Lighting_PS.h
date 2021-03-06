#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0_level_9_3 /EPS /Fh
//    Shader/EffekseerRenderer.Standard_Lighting_PS.h
//    Shader/standard_renderer_lighting_PS.fx
//
//
// Buffer Definitions: 
//
// cbuffer PSConstantBuffer
// {
//
//   float4 fLightDirection;            // Offset:    0 Size:    16
//   float4 fLightColor;                // Offset:   16 Size:    16
//   float4 fLightAmbient;              // Offset:   32 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// g_colorSampler                    sampler      NA          NA    0        1
// g_normalSampler                   sampler      NA          NA    1        1
// g_colorTexture                    texture  float4          2d    0        1
// g_normalTexture                   texture  float4          2d    1        1
// PSConstantBuffer                  cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_POSITION              0   xyzw        0      POS  float       
// COLOR                    0   xyzw        1     NONE  float   xyzw
// TEXCOORD                 0   xy          2     NONE  float   xy  
// TEXCOORD                 1   xy          3     NONE  float       
// TEXCOORD                 6     zw        3     NONE  float       
// TEXCOORD                 2   xyz         4     NONE  float       
// TEXCOORD                 3   xyz         5     NONE  float   xyz 
// TEXCOORD                 4   xyz         6     NONE  float   xyz 
// TEXCOORD                 5   xyz         7     NONE  float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c0         cb1             0         3  ( FLT, FLT, FLT, FLT)
//
//
// Sampler/Resource to DX9 shader sampler mappings:
//
// Target Sampler Source Sampler  Source Resource
// -------------- --------------- ----------------
// s0             s0              t0               
// s1             s1              t1               
//
//
// Level9 shader bytecode:
//
    ps_2_x
    def c3, -1, -0, -0.5, 0
    dcl_centroid t0
    dcl_centroid t1.xy
    dcl_pp t4.xyz
    dcl_pp t5.xyz
    dcl_pp t6.xyz
    dcl_2d s0
    dcl_2d s1
    texld r0, t1, s0
    mul r0, r0, t0
    cmp r1, -r0.w, c3.x, c3.y
    texkill r1
    texld_pp r1, t1, s1
    add_pp r1.xyz, r1, c3.z
    add_pp r1.xyz, r1, r1
    mul_pp r2.xyz, r1.y, t6
    mad_pp r1.xyw, r1.x, t5.xyzz, r2.xyzz
    mad_pp r1.xyz, r1.z, t4, r1.xyww
    nrm_pp r2.xyz, r1
    dp3 r1.x, c0, r2
    mul r1.yzw, r1.x, c1.xxyz
    cmp r1.xyz, r1.x, r1.yzww, c3.w
    add r1.xyz, r1, c2
    mul r0.xyz, r0, r1
    mov oC0, r0

// approximately 19 instruction slots used (2 texture, 17 arithmetic)
ps_4_0
dcl_constantbuffer cb1[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps linear centroid v1.xyzw
dcl_input_ps linear centroid v2.xy
dcl_input_ps linear v5.xyz
dcl_input_ps linear v6.xyz
dcl_input_ps linear v7.xyz
dcl_output o0.xyzw
dcl_temps 3
sample r0.xyzw, v2.xyxx, t0.xyzw, s0
mul r0.xyzw, r0.xyzw, v1.xyzw
ge r1.x, l(0.000000), r0.w
discard r1.x
sample r1.xyzw, v2.xyxx, t1.xyzw, s1
add r1.xyz, r1.xyzx, l(-0.500000, -0.500000, -0.500000, 0.000000)
add r1.xyz, r1.xyzx, r1.xyzx
mul r2.xyz, r1.yyyy, v7.xyzx
mad r1.xyw, r1.xxxx, v6.xyxz, r2.xyxz
mad r1.xyz, r1.zzzz, v5.xyzx, r1.xywx
dp3 r1.w, r1.xyzx, r1.xyzx
rsq r1.w, r1.w
mul r1.xyz, r1.wwww, r1.xyzx
dp3 r1.x, cb1[0].xyzx, r1.xyzx
max r1.x, r1.x, l(0.000000)
mad r1.xyz, cb1[1].xyzx, r1.xxxx, cb1[2].xyzx
mul o0.xyz, r0.xyzx, r1.xyzx
mov o0.w, r0.w
ret 
// Approximately 19 instruction slots used
#endif

const BYTE g_PS[] =
{
     68,  88,  66,  67, 190, 172, 
    175, 153, 179, 113,  84, 183, 
    119, 113, 233,  17, 206, 151, 
    149,  67,   1,   0,   0,   0, 
     84,   8,   0,   0,   6,   0, 
      0,   0,  56,   0,   0,   0, 
    252,   1,   0,   0, 192,   4, 
      0,   0,  60,   5,   0,   0, 
     28,   7,   0,   0,  32,   8, 
      0,   0,  65, 111, 110,  57, 
    188,   1,   0,   0, 188,   1, 
      0,   0,   0,   2, 255, 255, 
    132,   1,   0,   0,  56,   0, 
      0,   0,   1,   0,  44,   0, 
      0,   0,  56,   0,   0,   0, 
     56,   0,   2,   0,  36,   0, 
      0,   0,  56,   0,   0,   0, 
      0,   0,   1,   1,   1,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   2, 255, 255,  81,   0, 
      0,   5,   3,   0,  15, 160, 
      0,   0, 128, 191,   0,   0, 
      0, 128,   0,   0,   0, 191, 
      0,   0,   0,   0,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      0,   0,  79, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      1,   0,  67, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      4,   0,  39, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      5,   0,  39, 176,  31,   0, 
      0,   2,   0,   0,   0, 128, 
      6,   0,  39, 176,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      0,   8,  15, 160,  31,   0, 
      0,   2,   0,   0,   0, 144, 
      1,   8,  15, 160,  66,   0, 
      0,   3,   0,   0,  15, 128, 
      1,   0, 228, 176,   0,   8, 
    228, 160,   5,   0,   0,   3, 
      0,   0,  15, 128,   0,   0, 
    228, 128,   0,   0, 228, 176, 
     88,   0,   0,   4,   1,   0, 
     15, 128,   0,   0, 255, 129, 
      3,   0,   0, 160,   3,   0, 
     85, 160,  65,   0,   0,   1, 
      1,   0,  15, 128,  66,   0, 
      0,   3,   1,   0,  47, 128, 
      1,   0, 228, 176,   1,   8, 
    228, 160,   2,   0,   0,   3, 
      1,   0,  39, 128,   1,   0, 
    228, 128,   3,   0, 170, 160, 
      2,   0,   0,   3,   1,   0, 
     39, 128,   1,   0, 228, 128, 
      1,   0, 228, 128,   5,   0, 
      0,   3,   2,   0,  39, 128, 
      1,   0,  85, 128,   6,   0, 
    228, 176,   4,   0,   0,   4, 
      1,   0,  43, 128,   1,   0, 
      0, 128,   5,   0, 164, 176, 
      2,   0, 164, 128,   4,   0, 
      0,   4,   1,   0,  39, 128, 
      1,   0, 170, 128,   4,   0, 
    228, 176,   1,   0, 244, 128, 
     36,   0,   0,   2,   2,   0, 
     39, 128,   1,   0, 228, 128, 
      8,   0,   0,   3,   1,   0, 
      1, 128,   0,   0, 228, 160, 
      2,   0, 228, 128,   5,   0, 
      0,   3,   1,   0,  14, 128, 
      1,   0,   0, 128,   1,   0, 
    144, 160,  88,   0,   0,   4, 
      1,   0,   7, 128,   1,   0, 
      0, 128,   1,   0, 249, 128, 
      3,   0, 255, 160,   2,   0, 
      0,   3,   1,   0,   7, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 160,   5,   0,   0,   3, 
      0,   0,   7, 128,   0,   0, 
    228, 128,   1,   0, 228, 128, 
      1,   0,   0,   2,   0,   8, 
     15, 128,   0,   0, 228, 128, 
    255, 255,   0,   0,  83,  72, 
     68,  82, 188,   2,   0,   0, 
     64,   0,   0,   0, 175,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   1,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      1,   0,   0,   0,  85,  85, 
      0,   0,  98,  24,   0,   3, 
    242,  16,  16,   0,   1,   0, 
      0,   0,  98,  24,   0,   3, 
     50,  16,  16,   0,   2,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   5,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   6,   0, 
      0,   0,  98,  16,   0,   3, 
    114,  16,  16,   0,   7,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      3,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   1,   0, 
      0,   0,  29,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     13,   0,   4,   3,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     69,   0,   0,   9, 242,   0, 
     16,   0,   1,   0,   0,   0, 
     70,  16,  16,   0,   2,   0, 
      0,   0,  70, 126,  16,   0, 
      1,   0,   0,   0,   0,  96, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,  10, 114,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0, 191,   0,   0, 
      0, 191,   0,   0,   0, 191, 
      0,   0,   0,   0,   0,   0, 
      0,   7, 114,   0,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    114,   0,  16,   0,   2,   0, 
      0,   0,  86,   5,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   7,   0,   0,   0, 
     50,   0,   0,   9, 178,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   1,   0, 
      0,   0,  70,  24,  16,   0, 
      6,   0,   0,   0,  70,   8, 
     16,   0,   2,   0,   0,   0, 
     50,   0,   0,   9, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    166,  10,  16,   0,   1,   0, 
      0,   0,  70,  18,  16,   0, 
      5,   0,   0,   0,  70,   3, 
     16,   0,   1,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   1,   0,   0,   0, 
     70,   2,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  68,   0, 
      0,   5, 130,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   1,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   1,   0,   0,   0, 
    246,  15,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   1,   0,   0,   0, 
     52,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  50,   0, 
      0,  11, 114,   0,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   0,   1,   0, 
      0,   0,   2,   0,   0,   0, 
     56,   0,   0,   7, 114,  32, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      1,   0,   0,   0,  54,   0, 
      0,   5, 130,  32,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
     19,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      6,   0,   0,   0,  11,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  82,  68,  69,  70, 
    216,   1,   0,   0,   1,   0, 
      0,   0,  12,   1,   0,   0, 
      5,   0,   0,   0,  28,   0, 
      0,   0,   0,   4, 255, 255, 
     16,   1,   0,   0, 166,   1, 
      0,   0, 188,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0, 203,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    219,   0,   0,   0,   2,   0, 
      0,   0,   5,   0,   0,   0, 
      4,   0,   0,   0, 255, 255, 
    255, 255,   0,   0,   0,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0, 234,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 250,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    103,  95,  99, 111, 108, 111, 
    114,  83,  97, 109, 112, 108, 
    101, 114,   0, 103,  95, 110, 
    111, 114, 109,  97, 108,  83, 
     97, 109, 112, 108, 101, 114, 
      0, 103,  95,  99, 111, 108, 
    111, 114,  84, 101, 120, 116, 
    117, 114, 101,   0, 103,  95, 
    110, 111, 114, 109,  97, 108, 
     84, 101, 120, 116, 117, 114, 
    101,   0,  80,  83,  67, 111, 
    110, 115, 116,  97, 110, 116, 
     66, 117, 102, 102, 101, 114, 
      0, 171, 250,   0,   0,   0, 
      3,   0,   0,   0,  36,   1, 
      0,   0,  48,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 108,   1,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    124,   1,   0,   0,   0,   0, 
      0,   0, 140,   1,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    124,   1,   0,   0,   0,   0, 
      0,   0, 152,   1,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    124,   1,   0,   0,   0,   0, 
      0,   0, 102,  76, 105, 103, 
    104, 116,  68, 105, 114, 101, 
     99, 116, 105, 111, 110,   0, 
      1,   0,   3,   0,   1,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 102,  76, 
    105, 103, 104, 116,  67, 111, 
    108, 111, 114,   0, 102,  76, 
    105, 103, 104, 116,  65, 109, 
     98, 105, 101, 110, 116,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171,  73,  83,  71,  78, 
    252,   0,   0,   0,   9,   0, 
      0,   0,   8,   0,   0,   0, 
    224,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,   0,   0,   0, 
    236,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,  15,  15,   0,   0, 
    242,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   3,   3,   0,   0, 
    242,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
    242,   0,   0,   0,   6,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,  12,   0,   0,   0, 
    242,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   4,   0, 
      0,   0,   7,   0,   0,   0, 
    242,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   5,   0, 
      0,   0,   7,   7,   0,   0, 
    242,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   6,   0, 
      0,   0,   7,   7,   0,   0, 
    242,   0,   0,   0,   5,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   7,   0, 
      0,   0,   7,   7,   0,   0, 
     83,  86,  95,  80,  79,  83, 
     73,  84,  73,  79,  78,   0, 
     67,  79,  76,  79,  82,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0, 171,  79,  83, 
     71,  78,  44,   0,   0,   0, 
      1,   0,   0,   0,   8,   0, 
      0,   0,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  83,  86,  95,  84, 
     97, 114, 103, 101, 116,   0, 
    171, 171
};
