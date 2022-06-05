#pragma once

class GameEngineImage: public GameEngineNameBase
{
	//Friend Classes
	friend class GameEngineImageManager;
	friend class GameEngineRenderer;

	//Member Variables
	HBITMAP imageHBMP_;			//��Ʈ�� ���Ͽ��� �ҷ��� �̹����� �ڵ�. 
	HBITMAP prevHBMP_;			//imageHBMP_�� ������ �ִ� ���� �̹��������� �����ϴ� �ڵ�.
	HDC imageHDC_;				//�ҷ��� �̹����� ���� DC�ڵ�.
	BITMAP imageInfo_;			//�ҷ��� �̹����� ���� ����.

	//typedef struct tagBITMAP
	//{
	//	LONG        bmType;				���� Ÿ��. ��Ʈ�������� �ǹ��ϴ� 0������ ����.
	//	LONG        bmWidth;			�̹����� ���� �ȼ� ��.
	//	LONG        bmHeight;			�̹����� ���� �ȼ� ��.
	//	LONG        bmWidthBytes;		�̹��� ���� ������ ����Ʈ���� �뷮.
	//	WORD        bmPlanes;			����ϴ� ���� �÷��� ��. ������ ���� 1�̴�.
	//	WORD        bmBitsPixel;		�� �ȼ��� �� ��Ʈ ������ ����ϴ����� ���� ����. 
	//	LPVOID      bmBits;				��Ʈ�� ������ ����� �޸� �ּ�.
	//} BITMAP, * PBITMAP, NEAR* NPBITMAP, FAR* LPBITMAP;


	std::vector<float4> cuttingPos_;	//�Ѱ��� �� �̹����� �ڸ� �ȼ���ǥ ����.
	std::vector<float4> cuttingSizes_;	//�Ѱ��� �� �̹����� �ڸ� ũ��.
	int index_cuttingPos_;				//�߶� ������ �̹����� ����ų ��ȣ.


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

