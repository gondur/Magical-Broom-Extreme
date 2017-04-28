

#ifndef ___SELENE__QUATERNION___
#define ___SELENE__QUATERNION___


//-----------------------------------------------------------------------------------
// NAMESPACE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief élå≥êîÉNÉâÉX
	*/
	class SELENE_DLL_API CQuaternion
	{
	public:
		Float x;
		Float y;
		Float z;
		Float w;

	public:
		void Add( CQuaternion &In1, CQuaternion &In2 );
		void Sub( CQuaternion &In1, CQuaternion &In2 );
		void Mul( CQuaternion &In1, CQuaternion &In2 );
		void Lerp( CQuaternion &In0, CQuaternion &In1, Float fRate );
		void Slerp( CQuaternion &In0, CQuaternion &In1, Float fRate );

		void Add( CQuaternion &In );
		void Sub( CQuaternion &In );
		void Mul( CQuaternion &In );
		void Lerp( CQuaternion &In, Float fRate );
		void Slerp( CQuaternion &In, Float fRate );

		void Identity( void );
		Float LengthSq( void );
		Float Length( void );
		Float Dot( CQuaternion &In );
		void Conjugate( void );
	};
}

#endif // ___SELENE__QUATERNION___
