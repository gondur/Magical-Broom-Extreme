

#ifndef ___SMF_H___
#define ___SMF_H___


//------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------
#define MAX_BONE_COUNT			(48)				// 使用可能なボーン数（システム固定）


//------------------------------------------------------------------------------
// ENUM
//------------------------------------------------------------------------------
enum eSMFVersion
{
	SMF_VER_0100	= 0x0100,
};

enum eSMFDrawMode
{
	SMF_DRAW_NORMAL,
};


//------------------------------------------------------------------------------
// STRUCT
//------------------------------------------------------------------------------
struct SMF_VECTOR3
{
	float x;
	float y;
	float z;
};

struct SMF_VECTOR4
{
	float x;
	float y;
	float z;
	float w;
};

struct SMF_MATRIX
{
	SMF_VECTOR4 x;
	SMF_VECTOR4 y;
	SMF_VECTOR4 z;
	SMF_VECTOR4 w;
};

struct SMF_OBBDATA
{
	SMF_VECTOR3 vCenter;
	SMF_VECTOR3 vAxis[3];
	float fLength[3];
};

struct SMF_BONENAME
{
	char Name[64];
};

struct SMF_CHUNK
{
	unsigned long Chunk;							// チャンク
	unsigned long Size;								// サイズ
};

struct SMF_FILEHEAD
{
	unsigned long Version;
	unsigned long MeshCount;
	unsigned long FrameCount;
	unsigned long AnimationCount;
};

struct SMF_FRAMEDATA
{
	SMF_MATRIX mTransform;							// 親からの変換行列
	char Name[64];									// 名前
	long MeshNo;									// メッシュ
	long ParentFrameNo;								// 親のフレーム
};

struct SMF_MESHDATA
{
	char Name[64];									// 名前
	SMF_OBBDATA OBB;								// バウンディング
	unsigned long MaterialCount;					// マテリアル数
};

struct SMF_BONEDATA
{
	SMF_MATRIX mBoneOffset;
	SMF_BONENAME BoneNameList;
};

struct SMF_MATERIAL
{
	char TextureFileName[2][64];					// テクスチャ名
	SMF_VECTOR4 vDiffuse;							// マテリアル色
	unsigned long FaceStart;						// フェース開始位置
	unsigned long FaceCount;						// フェース数
	unsigned long VertexStart;						// 頂点開始位置
	unsigned long VertexCount;						// 頂点数
	unsigned long DrawMode;							// 描画モード
};


#endif // ___SMF_H___

