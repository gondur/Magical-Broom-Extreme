

#ifndef ___SMF_H___
#define ___SMF_H___


//------------------------------------------------------------------------------
// DEFINE
//------------------------------------------------------------------------------
#define MAX_BONE_COUNT			(48)				// �g�p�\�ȃ{�[�����i�V�X�e���Œ�j


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
	unsigned long Chunk;							// �`�����N
	unsigned long Size;								// �T�C�Y
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
	SMF_MATRIX mTransform;							// �e����̕ϊ��s��
	char Name[64];									// ���O
	long MeshNo;									// ���b�V��
	long ParentFrameNo;								// �e�̃t���[��
};

struct SMF_MESHDATA
{
	char Name[64];									// ���O
	SMF_OBBDATA OBB;								// �o�E���f�B���O
	unsigned long MaterialCount;					// �}�e���A����
};

struct SMF_BONEDATA
{
	SMF_MATRIX mBoneOffset;
	SMF_BONENAME BoneNameList;
};

struct SMF_MATERIAL
{
	char TextureFileName[2][64];					// �e�N�X�`����
	SMF_VECTOR4 vDiffuse;							// �}�e���A���F
	unsigned long FaceStart;						// �t�F�[�X�J�n�ʒu
	unsigned long FaceCount;						// �t�F�[�X��
	unsigned long VertexStart;						// ���_�J�n�ʒu
	unsigned long VertexCount;						// ���_��
	unsigned long DrawMode;							// �`�惂�[�h
};


#endif // ___SMF_H___

