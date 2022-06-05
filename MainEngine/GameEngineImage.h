#pragma once

class GameEngineImage: public GameEngineNameBase
{
	//Friend Classes
	friend class GameEngineImageManager;
	friend class GameEngineRenderer;

	//Member Variables
	HBITMAP imageHBMP_;			//비트맵 파일에서 불러온 이미지의 핸들. 
	HBITMAP prevHBMP_;			//imageHBMP_가 가지고 있던 이전 이미지정보를 보관하는 핸들.
	HDC imageHDC_;				//불러온 이미지에 대한 DC핸들.
	BITMAP imageInfo_;			//불러온 이미지가 가진 정보.

	//typedef struct tagBITMAP
	//{
	//	LONG        bmType;				파일 타입. 비트맵파일을 의미하는 0번으로 고정.
	//	LONG        bmWidth;			이미지의 가로 픽셀 수.
	//	LONG        bmHeight;			이미지의 세로 픽셀 수.
	//	LONG        bmWidthBytes;		이미지 가로 한줄의 바이트단위 용량.
	//	WORD        bmPlanes;			사용하는 색상 플레인 수. 요즘은 보통 1이다.
	//	WORD        bmBitsPixel;		한 픽셀에 몇 비트 색상을 사용하는지에 대한 정보. 
	//	LPVOID      bmBits;				비트맵 파일이 저장된 메모리 주소.
	//} BITMAP, * PBITMAP, NEAR* NPBITMAP, FAR* LPBITMAP;


	std::vector<float4> cuttingPos_;	//한개의 통 이미지를 자를 픽셀좌표 모음.
	std::vector<float4> cuttingSizes_;	//한개의 통 이미지를 자를 크기.
	int index_cuttingPos_;				//잘라낸 각각의 이미지를 가리킬 번호.


public:
	GameEngineImage();
	~GameEngineImage();

protected:
	GameEngineImage(const GameEngineImage& _other) = delete;
	GameEngineImage(GameEngineImage&& _other) noexcept = delete;

private:
	GameEngineImage& operator=(const GameEngineImage& _other) = delete;
	GameEngineImage& operator=(const GameEngineImage&& _other) = delete;


public:	//Member Function Headers
	void Cut(const float4 _size);


public:	//Getter, Setter, Templated Member Functions
	HDC GetHDC() const
	{
		return imageHDC_;
	}

	float4 GetSize() const
	{
		return { static_cast<float>(imageInfo_.bmWidth),
			static_cast<float>(imageInfo_.bmHeight) };
	}

	float4 GetCuttingPos(int _index) const
	{
		return cuttingPos_[_index];
	}

	float4 GetCuttingSizes(int _index) const
	{
		return cuttingSizes_[_index];
	}

	bool IsCut() const
	{
		return false == cuttingSizes_.empty();
	}


private://Member Function Headers
	void BitCopy(
		GameEngineImage* _srcImage, 
		const float4& _srcImagePos,
		const float4& _srcImageSize,
		const float4& _renderPos
	);
	void TransparentCopy(
		GameEngineImage* _srcImage,
		const float4& _renderPos,
		const float4& _renderSize,
		const float4& _srcImagePos,
		const float4& _srcImageSize,
		int _transparency
	);
	void PlgCopy(	
		GameEngineImage* _srcImage,
		const float4& _srcImagePos,
		const float4& _srcImageSize,
		const float4& _renderPos,
		const float4& _renderSize,
		GameEngineImage* _maskImage,
		float _angle
	);

	bool Create(HDC _curWindowHDC);
	bool Create(HDC _curWindowHDC, const float4& _windowSize);
	bool Load(const std::string& _path);
	void GetImageInfo();
};

