#include "PreCompile.h"
#include "GameEngineImage.h"
#pragma comment(lib, "msimg32.lib")
//msimg32.lib: transparentBlt()등의 이미지 관련 내용이 포함되어있는 라이브러리. 
//윈도우에서 이미 지원해주므로 경로설정을 추가로 해 줄 필요가 없다.

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
		GameEngineDebug::MsgBoxError("자르는 사이즈가 0입니다.");
		return;
	}

	if (false == cuttingPos_.empty() || false == cuttingSizes_.empty())
	{
		GameEngineDebug::MsgBoxError("이미 잘린 이미지입니다.");
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
		GameEngineDebug::MsgBoxError("복사할 이미지가 없습니다.");
		return;
	}

	if (0.0f >= _srcImageSize.x || 0.0f >= _srcImageSize.y)
	{
		GameEngineDebug::MsgBoxError("그릴 이미지의 크기가 0입니다.");
		return;
	}

	int bitBltResult = BitBlt(		//첫 HDC의 이미지 위에 두번째 HDC의 이미지를 잘라 붙이는 함수. 실패하면 0 반환.
		this->imageHDC_,			//srcImage가 그려질 백버퍼 이미지의 HDC.
		_srcImagePos.IntX(),		//srcImage를 가져올, srcImage 내 왼쪽상단 x좌표.
		_srcImagePos.IntY(),		//srcImage를 가져올, srcImage 내 왼쪽상단 y좌표.
		_srcImageSize.IntX(),		//srcImage에서 잘라올 이미지의 가로 픽셀길이.
		_srcImageSize.IntY(),		//srcImage에서 잘라올 이미지의 세로 픽셀길이.
		_srcImage->GetHDC(),			//그릴 srcImage의 DC핸들.
		_renderPos.IntX(),			//srcImage가 그려질 백버퍼 이미지 내 x좌표. 왼쪽상단 기준.
		_renderPos.IntY(),			//srcImage가 그려질 백버퍼 이미지 내 y좌표. 왼쪽상단 기준.
		SRCCOPY						//복사방식. SRCCOPY: 원본 이미지를 변경없이 그대로 복사. 
	);								//다른 플래그들은 전부 색상 비트연산이므로 신경쓸 필요 없음.

	if (0 == bitBltResult)
	{
		GameEngineDebug::MsgBoxError("BitBlt 실패.");
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
		GameEngineDebug::MsgBoxError("복사할 이미지가 없습니다.");
		return;
	}

	if (0.0f >= _renderSize.x || 0.0f >= _renderSize.y)
	{
		GameEngineDebug::MsgBoxError("렌더사이즈가 0입니다.");
		return;
	}

	if (0.0f >= _srcImageSize.x || 0.0f >= _srcImageSize.y)
	{
		GameEngineDebug::MsgBoxError("그릴 이미지의 크기가 0입니다.");
		return;
	}

	int transparentBltResult = TransparentBlt(	//비트맵 이미지의 특정 색상값을 투명하게 하거나 크기를 조정해서 옮기는 함수. 실패하면 0 반환.
		this->imageHDC_,			//srcImage가 그려질 전체 백버퍼 이미지의 HDC.
		_renderPos.IntX(),			//src이미지가 그려질 백버퍼 이미지 내 x좌표. 왼쪽상단 기준.
		_renderPos.IntY(),			//src이미지가 그려질 백버퍼 이미지 내 y좌표. 왼쪽상단 기준.
		_renderSize.IntX(),			//src이미지가 그려질 백버퍼 이미지 내 x 길이.
		_renderSize.IntY(),			//src이미지가 그려질 백버퍼 이미지 내 y 길이.
		_srcImage->GetHDC(),			//src 이미지의 HDC.
		_srcImagePos.IntX(),		//src이미지를 가져올, src이미지 내 왼쪽상단 x좌표. 
		_srcImagePos.IntY(),		//src이미지를 가져올, src이미지 내 왼쪽상단 y좌표.
		_srcImageSize.IntX(),		//src이미지를 가져올 가로 픽셀길이.
		_srcImageSize.IntY(),		//src이미지를 가져올 세로 픽셀길이.
		_transparency				//투명처리할 RGB색상값.
	);
	//크기조정은 느려질 가능성이 높으므로 웬만하면 _renderSize와 _srcImageSize를 같게 한다.

	if (0 == transparentBltResult)
	{
		GameEngineDebug::MsgBoxError("TransparentBlt 실패.");
		return;
	}
}

void GameEngineImage::PlgCopy(
	GameEngineImage* _srcImage,
	const float4& _srcImagePos,
	const float4& _srcImageSize, 
	const float4& _renderPos,	//왼쪽상단 기준.
	const float4& _renderSize,
	GameEngineImage* _maskImage,
	float _angle
)
{
	if (nullptr == _srcImage)
	{
		GameEngineDebug::MsgBoxError("복사할 이미지가 없습니다.");
		return;
	}
	
	if (nullptr == _maskImage)
	{
		GameEngineDebug::MsgBoxError("마스크 이미지가 없습니다.");
		return;
	}

	if (1 != _maskImage->imageInfo_.bmBitsPixel)
	{
		//픽셀별 색상이 순수하게 0이나 1로만 되어있는 흑백 비트맵 이미지만 마스크 이미지로 사용할 수 있다. 
		GameEngineDebug::MsgBoxError("사용할 수 없는 마스크 이미지입니다.");
		return;
	}     

	float4 renderCenter = _renderPos + _renderSize.Half();

	GameEngineRect renderRect = GameEngineRect(float4::Zero, _renderSize);

	float4 renderVertex_LT = { //좌상.
		renderCenter + renderRect.LeftTopfloat4().Rotate2DByDegree(_angle)
	};
	float4 renderVertex_RT = { //우상. 
		renderCenter + renderRect.RightTopfloat4().Rotate2DByDegree(_angle)
	};
	float4 renderVertex_LB = { //좌하.
		renderCenter + renderRect.LeftBotfloat4().Rotate2DByDegree(_angle)
	};

	POINT renderVertexes[3] = {
		renderVertex_LT.ConvertToPoint(),
		renderVertex_RT.ConvertToPoint(),
		renderVertex_LB.ConvertToPoint() 
	};

	//좌상, 우상, 좌하 순으로 배치.

	int plgBltResult = PlgBlt(	//
		this->imageHDC_,		//sourceImage가 그려질 전체 백버퍼 이미지의 HDC.
		renderVertexes,		//srcImage를 배치할, 백버퍼이미지 내 세 점의 위치를 가진 POINT 구조체 배열.  
		_srcImage->GetHDC(),	//srcImage의 HDC.
		_srcImagePos.IntX(),	//srcImage를 가져올, srcImage 내 왼쪽상단 x좌표. 
		_srcImagePos.IntY(),	//srcImage를 가져올, srcImage 내 왼쪽상단 y좌표.
		_srcImageSize.IntX(),	//srcImage를 가져올 가로 픽셀길이.
		_srcImageSize.IntY(),	//srcImage를 가져올 세로 픽셀길이.
		_maskImage->imageHBMP_, //마스크 이미지의 정보를 가진 핸들.
		_srcImagePos.IntX(),		//마스크 이미지를 가져올, 마스크 이미지 내 왼쪽상단 x좌표.
		_srcImagePos.IntY()		//마스크 이미지를 가져올, 마스크 이미지 내 왼쪽상단 y좌표.
		//마스크 이미지는 srcImage와 같은 크기 같은 위치에서 복사를 시작해야 한다.
	);

	if (0 == plgBltResult)
	{
		GameEngineDebug::MsgBoxError("PlgBlt 실패.");
		return;
	}
}

bool GameEngineImage::Create(HDC _curWindowHDC)
{
	if (nullptr == _curWindowHDC)
	{
		GameEngineDebug::MsgBoxError("현재 윈도우 HDC가 없습니다.");
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
		GameEngineDebug::MsgBoxError("현재 윈도우 HDC가 없습니다.");
		return false;
	}

	imageHBMP_ = CreateCompatibleBitmap(_curWindowHDC, _windowSize.IntX(), _windowSize.IntY());
	//빈 비트맵 핸들인 imageHBMP에 _curWindowHDC가 가진 윈도우 정보와 입력해주는 크기정보를 가진 비트맵 핸들을 새로 할당한다.

	imageHDC_ = CreateCompatibleDC(NULL);	//진짜 메모리DC는 여기서 생성. 
	//NULL을 인자로 넣으면 현재 윈도우 정보가 들어있는 CreateCompatibleDC()함수의 자체 HDC를 생성해서 반환한다. 
	//반환된 HDC에는 기본값으로 1x1 픽셀 검은색 이미지만 연결된 상태로 메모리에만 존재하고 있다.

	HANDLE tempHandle = SelectObject(imageHDC_, static_cast<HGDIOBJ>(imageHBMP_));
	//imageHBMP가 가진 이미지는 imageHDC에 연결하고 imageHDC가 원래 가지고 있던 1x1 픽셀 이미지는 tempHandle에게 반환한다.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//tempHandle이 가진 이미지는 prevHBMP가 받아 보관한다.

	GetImageInfo();	//imageHDC가 가진 이미지의 정보를 가져온다.

	return true;
}

bool GameEngineImage::Load(const std::string& _path)
{
	//HANDLE == void*.
	HANDLE loadedHBMP = LoadImageA(		//지정된 경로에서 이미지파일을 불러오는 함수.
		nullptr,			//불러오려는 이미지가 있는 exe파일이나 라이브러리의 인스턴스 핸들. 이미지 하나만 있는 파일을 불러올때는 NULL을 넣는다.
		_path.c_str(),		//불러오려는 이미지파일의 경로를 포함한 이름.
		IMAGE_BITMAP,		//이미지 타입. IMAGE_BITMAP를 넣으면 비트맵 형식의 파일을 불러온다.
		0,					//이미지 가로길이. 여길 0으로 하고 마지막 인자가 LR_DEFAULTSIZE가 아니라면 이미지 자제 크기로 불러온다.
		0,					//이미지 세로길이. 여길 0으로 하고 마지막 인자가 LR_DEFAULTSIZE가 아니라면 이미지 자제 크기로 불러온다.
		LR_LOADFROMFILE		//이미지 하나만 있는 파일을 불러올때 두번째 인자에 파일 경로와 이름을, 여기에 LR_LOADFROMFILE를 넣어준다.
	);

	if (NULL == loadedHBMP)
	{
		GameEngineDebug::MsgBoxError("이미지를 불러오는데 실패했습니다.");
		return false;
	}

	imageHBMP_ = static_cast<HBITMAP>(loadedHBMP);


	imageHDC_ = CreateCompatibleDC(NULL);		//빈 HDC인 imageHDC_에 1x1픽셀짜리 이미지와 연결된 DC 핸들을 준다.
	//이 때 imageHDC는 화면상에 직접 그려지지 않고 메모리상에만 존재하는 메모리DC의 핸들이다.
	//GetDC()는 화면과 직접 연결되어 있는 DC를 반환하므로 여기서 쓸 수 없다고 한다.


	HANDLE tempHandle = SelectObject(
		//SelectObject(): HDC형 매개변수에 HGDIOBJ형 매개변수가 가진 DC의 핸들을 넘기고, HDC형 매개변수가 이전까지 가지고 있던 이미지의 핸들을 반환하는 함수.
		imageHDC_,							//이미지를 넘겨받을 HDC.
		static_cast<HGDIOBJ>(loadedHBMP)	//넘겨줄 이미지를 가지고있는 핸들.
	);										//HGDIOBJ: DC용 공용 HANDLE.

	prevHBMP_ = static_cast<HBITMAP>(tempHandle);
	//imageHDC가 가지고 있던 이미지의 핸들은 위에서 tempHandle이 반환받아 prevHBMP로 전달해서 보관한다. 

	GetImageInfo();

	return true;
}

void GameEngineImage::GetImageInfo()
{
	if (nullptr == imageHDC_)
	{
		GameEngineDebug::MsgBoxError("이미지 HDC가 없습니다.");
		return;
	}

	HBITMAP tempHBMP = static_cast<HBITMAP>(GetCurrentObject(imageHDC_, OBJ_BITMAP));
	if (0 == GetObjectA(tempHBMP, sizeof(BITMAP), &imageInfo_))
	{
		GameEngineDebug::MsgBoxError("GetObjectA 실패.");
		return;
	}
}

