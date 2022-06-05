#include "PreCompile.h"
#include "GameEngineImage.h"
#pragma comment(lib, "msimg32.lib")
//msimg32.lib: transparentBlt()���� �̹��� ���� ������ ���ԵǾ��ִ� ���̺귯��. 
//�����쿡�� �̹� �������ֹǷ� ��μ����� �߰��� �� �� �ʿ䰡 ����.

GameEngineImage::GameEngineImage()
	: imageHBMP_(nullptr),
	prevHBMP_(nullptr),
	imageHDC_(nullptr),
	imageInfo_({ 0 }),
	index_cuttingPos_(-1)
{
}

GameEngineImage::~GameEngineImage()
{
}

void GameEngineImage::Cut(const float4 _size)
{
	if (0.0f >= _size.x || 0.0f >= _size.y)
	{
		GameEngineDebug::MsgBoxError("�ڸ��� ����� 0�Դϴ�.");
		return;
	}

	if (false == cuttingPos_.empty() || false == cuttingSizes_.empty())
	{
		GameEngineDebug::MsgBoxError("�̹� �߸� �̹����Դϴ�.");
		return;
	}

	size_t xCount = static_cast<size_t>(this->GetSize().x / _size.x);
	size_t yCount = static_cast<size_t>(this->GetSize().y / _size.y);

	cuttingPos_.reserve(xCount * yCount);
	cuttingSizes_.reserve(xCount * yCount);

	float4 cuttingPos = float4::Zero;
	float4 cuttingSize = _size;

	for (size_t y = 0; y < yCount; y++)
	{
		for (size_t x = 0; x < xCount; x++)
		{
			cuttingPos_.push_back(cuttingPos);
			cuttingSizes_.push_back(cuttingSize);
			cuttingPos.x += cuttingSize.x;
		}
		cuttingPos.x = 0.0f;
		cuttingPos.y += cuttingSize.y;
	}
}

void GameEngineImage::BitCopy(
	GameEngineImage* _srcImage,
	const float4& _srcImagePos,
	const float4& _srcImageSize,
	const float4& _renderPos
)
{
	if (nullptr == _srcImage)
	{
		GameEngineDebug::MsgBoxError("������ �̹����� �����ϴ�.");
		return;
	}

	if (0.0f >= _srcImageSize.x || 0.0f >= _srcImageSize.y)
	{
		GameEngineDebug::MsgBoxError("�׸� �̹����� ũ�Ⱑ 0�Դϴ�.");
		return;
	}

	int bitBltResult = BitBlt(		//ù HDC�� �̹��� ���� �ι�° HDC�� �̹����� �߶� ���̴� �Լ�. �����ϸ� 0 ��ȯ.
		this->imageHDC_,			//srcImage�� �׷��� ����� �̹����� HDC.
		_srcImagePos.IntX(),		//srcImage�� ������, srcImage �� ���ʻ�� x��ǥ.
		_srcImagePos.IntY(),		//srcImage�� ������, srcImage �� ���ʻ�� y��ǥ.
		_srcImageSize.IntX(),		//srcImage���� �߶�� �̹����� ���� �ȼ�����.
		_srcImageSize.IntY(),		//srcImage���� �߶�� �̹����� ���� �ȼ�����.
		_srcImage->GetHDC(),			//�׸� srcImage�� DC�ڵ�.
		_renderPos.IntX(),			//srcImage�� �׷��� ����� �̹��� �� x��ǥ. ���ʻ�� ����.
		_renderPos.IntY(),			//srcImage�� �׷��� ����� �̹��� �� y��ǥ. ���ʻ�� ����.
		SRCCOPY						//������. SRCCOPY: ���� �̹����� ������� �״�� ����. 
	);								//�ٸ� �÷��׵��� ���� ���� ��Ʈ�����̹Ƿ� �Ű澵 �ʿ� ����.

	if (0 == bitBltResult)
	{
		GameEngineDebug::MsgBoxError("BitBlt ����.");
		return;
	}
}

void GameEngineImage::TransparentCopy(
	GameEngineImage* _srcImage,
	const float4& _renderPos,
	const float4& _renderSize,
	const float4& _srcImagePos,
	const float4& _srcImageSize,
	int _transparency
)
{
	if (nullptr == _srcImage)
	{
		GameEngineDebug::MsgBoxError("������ �̹����� �����ϴ�.");
		return;
	}

	if (0.0f >= _renderSize.x || 0.0f >= _renderSize.y)
	{
		GameEngineDebug::MsgBoxError("��������� 0�Դϴ�.");
		return;
	}

	if (0.0f >= _srcImageSize.x || 0.0f >= _srcImageSize.y)
	{
		GameEngineDebug::MsgBoxError("�׸� �̹����� ũ�Ⱑ 0�Դϴ�.");
		return;
	}

	int transparentBltResult = TransparentBlt(	//��Ʈ�� �̹����� Ư�� ������ �����ϰ� �ϰų� ũ�⸦ �����ؼ� �ű�� �Լ�. �����ϸ� 0 ��ȯ.
		this->imageHDC_,			//srcImage�� �׷��� ��ü ����� �̹����� HDC.
		_renderPos.IntX(),			//src�̹����� �׷��� ����� �̹��� �� x��ǥ. ���ʻ�� ����.
		_renderPos.IntY(),			//src�̹����� �׷��� ����� �̹��� �� y��ǥ. ���ʻ�� ����.
		_renderSize.IntX(),			//src�̹����� �׷��� ����� �̹��� �� x ����.
		_renderSize.IntY(),			//src�̹����� �׷��� ����� �̹��� �� y ����.
		_srcImage->GetHDC(),			//src �̹����� HDC.
		_srcImagePos.IntX(),		//src�̹����� ������, src�̹��� �� ���ʻ�� x��ǥ. 
		_srcImagePos.IntY(),		//src�̹����� ������, src�̹��� �� ���ʻ�� y��ǥ.
		_srcImageSize.IntX(),		//src�̹����� ������ ���� �ȼ�����.
		_srcImageSize.IntY(),		//src�̹����� ������ ���� �ȼ�����.
		_transparency				//����ó���� RGB����.
	);
	//ũ�������� ������ ���ɼ��� �����Ƿ� �����ϸ� _renderSize�� _srcImageSize�� ���� �Ѵ�.

	if (0 == transparentBltResult)
	{
		GameEngineDebug::MsgBoxError("TransparentBlt ����.");
		return;
	}
}

void GameEngineImage::PlgCopy(
	GameEngineImage* _srcImage,
	const float4& _srcImagePos,
	const float4& _srcImageSize, 
	const float4& _renderPos,	//���ʻ�� ����.
	const float4& _renderSize,
	GameEngineImage* _maskImage,
	float _angle
)
{
	if (nullptr == _srcImage)
	{
		GameEngineDebug::MsgBoxError("������ �̹����� �����ϴ�.");
		return;
	}
	
	if (nullptr == _maskImage)
	{
		GameEngineDebug::MsgBoxError("����ũ �̹����� �����ϴ�.");
		return;
	}

	if (1 != _maskImage->imageInfo_.bmBitsPixel)
	{
		//�ȼ��� ������ �����ϰ� 0�̳� 1�θ� �Ǿ��ִ� ��� ��Ʈ�� �̹����� ����ũ �̹����� ����� �� �ִ�. 
		GameEngineDebug::MsgBoxError("����� �� ���� ����ũ �̹����Դϴ�.");
		return;
	}     

	float4 renderCenter = _renderPos + _renderSize.Half();

	GameEngineRect renderRect = GameEngineRect(float4::Zero, _renderSize);

	float4 renderVertex_LT = { //�»�.
		renderCenter + renderRect.LeftTopfloat4().Rotate2DByDegree(_angle)
	};
	float4 renderVertex_RT = { //���. 
		renderCenter + renderRect.RightTopfloat4().Rotate2DByDegree(_angle)
	};
	float4 renderVertex_LB = { //����.
		renderCenter + renderRect.LeftBotfloat4().Rotate2DByDegree(_angle)
	};

	POINT renderVertexes[3] = {
		renderVertex_LT.ConvertToPoint(),
		renderVertex_RT.ConvertToPoint(),
		renderVertex_LB.ConvertToPoint() 
	};

	//�»�, ���, ���� ������ ��ġ.

	int plgBltResult = PlgBlt(	//
		this->imageHDC_,		//sourceImage�� �׷��� ��ü ����� �̹����� HDC.
		renderVertexes,		//srcImage�� ��ġ��, ������̹��� �� �� ���� ��ġ�� ���� POINT ����ü �迭.  
		_srcImage->GetHDC(),	//srcImage�� HDC.
		_srcImagePos.IntX(),	//srcImage�� ������, srcImage �� ���ʻ�� x��ǥ. 
		_srcImagePos.IntY(),	//srcImage�� ������, srcImage �� ���ʻ�� y��ǥ.
		_srcImageSize.IntX(),	//srcImage�� ������ ���� �ȼ�����.
		_srcImageSize.IntY(),	//srcImage�� ������ ���� �ȼ�����.
		_maskImage->imageHBMP_, //����ũ �̹����� ������ ���� �ڵ�.
		_srcImagePos.IntX(),		//����ũ �̹����� ������, ����ũ �̹��� �� ���ʻ�� x��ǥ.
		_srcImagePos.IntY()		//����ũ �̹����� ������, ����ũ �̹��� �� ���ʻ�� y��ǥ.
		//����ũ �̹����� srcImage�� ���� ũ�� ���� ��ġ���� ���縦 �����ؾ� �Ѵ�.
	);

	if (0 == plgBltResult)
	{
		GameEngineDebug::MsgBoxError("PlgBlt ����.");
		return;
	}
}

bool GameEngineImage::Create(HDC _curWindowHDC)
{
	if (nullptr == _curWindowHDC)
	{
		GameEngineDebug::MsgBoxError("���� ������ HDC�� �����ϴ�.");
		return false;
	}
	else
	{
		imageHDC_ = _curWindowHDC;
		GetImageInfo();
		return true;
	}
}

bool GameEngineImage::Create(HDC _curWindowHDC, const float4& _windowSize)
{
	if (nullptr == _curWindowHDC)	
	{
		GameEngineDebug::MsgBoxError("���� ������ HDC�� �����ϴ�.");
		return false;
	}

	imageHBMP_ = CreateCompatibleBitmap(_curWindowHDC, _windowSize.IntX(), _windowSize.IntY());
	//�� ��Ʈ�� �ڵ��� imageHBMP�� _curWindowHDC�� ���� ������ ������ �Է����ִ� ũ�������� ���� ��Ʈ�� �ڵ��� ���� �Ҵ��Ѵ�.

	imageHDC_ = CreateCompatibleDC(NULL);	//��¥ �޸�DC�� ���⼭ ����. 
	//NULL�� ���ڷ� ������ ���� ������ ������ ����ִ� CreateCompatibleDC()�Լ��� ��ü HDC�� �����ؼ� ��ȯ�Ѵ�. 
	//��ȯ�� HDC���� �⺻������ 1x1 �ȼ� ������ �̹����� ����� ���·� �޸𸮿��� �����ϰ� �ִ�.

	HANDLE tempHandle = SelectObject(imageHDC_, static_cast<HGDIOBJ>(imageHBMP_));
	//imageHBMP�� ���� �̹����� imageHDC�� �����ϰ� imageHDC�� ���� ������ �ִ� 1x1 �ȼ� �̹����� tempHandle���� ��ȯ�Ѵ�.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//tempHandle�� ���� �̹����� prevHBMP�� �޾� �����Ѵ�.

	GetImageInfo();	//imageHDC�� ���� �̹����� ������ �����´�.

	return true;
}

bool GameEngineImage::Load(const std::string& _path)
{
	//HANDLE == void*.
	HANDLE loadedHBMP = LoadImageA(		//������ ��ο��� �̹��������� �ҷ����� �Լ�.
		nullptr,			//�ҷ������� �̹����� �ִ� exe�����̳� ���̺귯���� �ν��Ͻ� �ڵ�. �̹��� �ϳ��� �ִ� ������ �ҷ��ö��� NULL�� �ִ´�.
		_path.c_str(),		//�ҷ������� �̹��������� ��θ� ������ �̸�.
		IMAGE_BITMAP,		//�̹��� Ÿ��. IMAGE_BITMAP�� ������ ��Ʈ�� ������ ������ �ҷ��´�.
		0,					//�̹��� ���α���. ���� 0���� �ϰ� ������ ���ڰ� LR_DEFAULTSIZE�� �ƴ϶�� �̹��� ���� ũ��� �ҷ��´�.
		0,					//�̹��� ���α���. ���� 0���� �ϰ� ������ ���ڰ� LR_DEFAULTSIZE�� �ƴ϶�� �̹��� ���� ũ��� �ҷ��´�.
		LR_LOADFROMFILE		//�̹��� �ϳ��� �ִ� ������ �ҷ��ö� �ι�° ���ڿ� ���� ��ο� �̸���, ���⿡ LR_LOADFROMFILE�� �־��ش�.
	);

	if (NULL == loadedHBMP)
	{
		GameEngineDebug::MsgBoxError("�̹����� �ҷ����µ� �����߽��ϴ�.");
		return false;
	}

	imageHBMP_ = static_cast<HBITMAP>(loadedHBMP);


	imageHDC_ = CreateCompatibleDC(NULL);		//�� HDC�� imageHDC_�� 1x1�ȼ�¥�� �̹����� ����� DC �ڵ��� �ش�.
	//�� �� imageHDC�� ȭ��� ���� �׷����� �ʰ� �޸𸮻󿡸� �����ϴ� �޸�DC�� �ڵ��̴�.
	//GetDC()�� ȭ��� ���� ����Ǿ� �ִ� DC�� ��ȯ�ϹǷ� ���⼭ �� �� ���ٰ� �Ѵ�.


	HANDLE tempHandle = SelectObject(
		//SelectObject(): HDC�� �Ű������� HGDIOBJ�� �Ű������� ���� DC�� �ڵ��� �ѱ��, HDC�� �Ű������� �������� ������ �ִ� �̹����� �ڵ��� ��ȯ�ϴ� �Լ�.
		imageHDC_,							//�̹����� �Ѱܹ��� HDC.
		static_cast<HGDIOBJ>(loadedHBMP)	//�Ѱ��� �̹����� �������ִ� �ڵ�.
	);										//HGDIOBJ: DC�� ���� HANDLE.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//imageHDC�� ������ �ִ� �̹����� �ڵ��� ������ tempHandle�� ��ȯ�޾� prevHBMP�� �����ؼ� �����Ѵ�. 

	GetImageInfo();

	return true;
}

void GameEngineImage::GetImageInfo()
{
	if (nullptr == imageHDC_)
	{
		GameEngineDebug::MsgBoxError("�̹��� HDC�� �����ϴ�.");
		return;
	}

	HBITMAP tempHBMP = static_cast<HBITMAP>(GetCurrentObject(imageHDC_, OBJ_BITMAP));
	if (0 == GetObjectA(tempHBMP, sizeof(BITMAP), &imageInfo_))
	{
		GameEngineDebug::MsgBoxError("GetObjectA ����.");
		return;
	}
}

